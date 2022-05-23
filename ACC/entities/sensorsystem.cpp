#include "sensorsystem.h"

SensorSystem::SensorSystem(std::string name) :
    Runnable(name),
    sensorDataQueue{    std::priority_queue<
                        SensorData, std::vector<SensorData>, std::function<bool(const SensorData&, const SensorData&)>
                    >(priorityFunctor)}
{
    automobile_sensor_timeout_ch = new Channel<SensorData>(Constants::AUTOMOBILE_SENSOR_CHNAME_FREE,
                                                          Constants::AUTOMOBILE_SENSOR_CHNAME_EMPTY,
                                                          Constants::AUTOMOBILE_SENSOR_CHTIMEOUT_MS);
    termination_timeout_sem = new Semaphore(Constants::SENSOR_TERMINATION_SEMNAME, 0, Constants::TERMINATION_SEMTIMEOUT_MS);

    log(this->name(), "Object (subsystem) created");
}

SensorSystem::~SensorSystem()
{
    delete automobile_sensor_timeout_ch;
    delete termination_timeout_sem;

    log(name(), "Object (subsystem) destroyed");
}

void SensorSystem::run()
{
    // 1. running
    log(name(), "Object is running");
    InitializeConditionVariable(&BufferNotEmpty);
    InitializeConditionVariable(&BufferNotFull);
    InitializeCriticalSection(&BufferLock);

    // 2. consumer thread
    std::thread* SensorControlProcThread = new std::thread(RunSensorControlProc, this);
    log(name(), "SensorControlProc thread started");

    // 3. producer threads
    std::vector<std::thread*> sensorsThreads;
    for (int i = 0; i < Constants::SENSORS_COUNT; i++) {
        sensorsThreads.push_back(new std::thread(RunSingleSensorProc, this));
        log(name(), "SingleSensorProc thread " + std::to_string(current_sensors_count - 1) + " started");
    }

    // 4. waiting stopping
    log(name(), "Waiting system stopping ...");

    bool is_running = true;
    while (is_running) {
        termination_timeout_sem->P(is_running);
    }

    // 5. stopping
    log(name(), "ACC system stopped. SensorSystem stoppign started");
    EnterCriticalSection(&BufferLock);
    StopRequested = TRUE;
    LeaveCriticalSection(&BufferLock);

    WakeAllConditionVariable(&BufferNotFull);
    WakeAllConditionVariable(&BufferNotEmpty);

    SensorControlProcThread->join();
    delete SensorControlProcThread;
    for (std::thread* t : sensorsThreads) {
        t->join();
        delete t;
    }

    log(name(), "All threads completed. Object cycle completed");
}

void SensorSystem::SingleSensorProc(int number)
{
    std::string tag = name() + ":" + "sensor_" + std::to_string(number);
    log(tag, "Object is running (thread)");

    // producion cycle
    while (true) {
        // 1. sleep
        Sleep(rand_in_range(Constants::ROADOBJECT_INTERVAL_RANGE_MS[0], Constants::ROADOBJECT_INTERVAL_RANGE_MS[1]));

        // 2. produce object
        log(tag, "There are road object");
        int chances = rand_in_range(0, 100);
        SensorData data;
        if (chances <= Constants::BARRIER_WEIGHTS[0]) {
            // critical barrier
            data.state = SensorState::CRITICAL_BARRIER;
            data.distance = rand_in_range(30, 50);
            log(tag, "There are critical barrier: " + to_string(data));
        } else if (chances > Constants::BARRIER_WEIGHTS[0] && chances <= Constants::BARRIER_WEIGHTS[1]) {
            // barrier
            data.state = SensorState::BARRIER;
            data.distance = rand_in_range(50, 100);
            log(tag, "There are barrier: " + to_string(data));
        } else {
            data.state = SensorState::NORMAL;
            data.distance = -1;
            log(tag, "Not dangerous object");
        }

        // 3. write data to queue
        EnterCriticalSection(&BufferLock);
        while (sensorDataQueue.size() == Constants::SENSOR_SYSTEM_QUEUE_MAX_SIZE && StopRequested == FALSE) {
            // waiting processing
            SleepConditionVariableCS(&BufferNotFull, &BufferLock, INFINITE);
        }

        // 4. check stop
        if (StopRequested == TRUE) {
            log(tag, "StopRequested received. Stopping object cycle");
            LeaveCriticalSection(&BufferLock);
            break;
        }

        // 5. add data to queue
        sensorDataQueue.push(data);
        log(tag, "Data added to queue (queue size: )" + std::to_string(sensorDataQueue.size()) + ")");
        LeaveCriticalSection(&BufferLock);

        // if consumer wait -> wake up it
        WakeConditionVariable(&BufferNotEmpty);
    }

    log(tag, "Object cycle completed");
}

void SensorSystem::SensorControlProc()
{
    std::string tag = name() + ":" + "SensorControl";
    log(tag, "Object is running (thread)");

    while (true) {
        EnterCriticalSection(&BufferLock);

        // wait data
        while (sensorDataQueue.size() == 0 && StopRequested == FALSE) {
            log(tag, "Waiting sensor data");
            SleepConditionVariableCS(&BufferNotEmpty, &BufferLock, INFINITE);
        }

        // if (StopRequested == TRUE && sensorDataQueue.size() == 0)
        if (StopRequested == TRUE)   {
            log(tag, "StopRequested received. Stopping object cycle");
            LeaveCriticalSection(&BufferLock);
            break;
        }

        // extract data from queue
        SensorData data = sensorDataQueue.top();
        sensorDataQueue.pop();
        LeaveCriticalSection(&BufferLock);
        WakeConditionVariable(&BufferNotFull);

        // process data
        log(tag, "Extracted data from sensor data queue: " + to_string(data));

        if (data.state == SensorState::NORMAL) {
            // normal
            log(name(), "No dangerous barriers");
            automobile_sensor_timeout_ch->put(data);
        }
        else if (data.state == SensorState::BARRIER) {
            // barrier
            log(name(), "Detected barrier. Need speed correction");
            automobile_sensor_timeout_ch->put(data);
        }
        else {
            // critical barrier
            log(name(), "Detected dangerous barrier. Sending info to automobile for braking.");
            automobile_sensor_timeout_ch->put(data);
        }
    }
}

void SensorSystem::RunSensorControlProc(SensorSystem *obj)
{
    obj->SensorControlProc();
}

void SensorSystem::RunSingleSensorProc(SensorSystem *obj)
{
    obj->SingleSensorProc(current_sensors_count++);
}

int SensorSystem::current_sensors_count = 0;
