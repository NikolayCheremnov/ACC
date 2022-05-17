#include "roadobject.h"

RoadObject::RoadObject(std::string name) :
    Runnable(name)
{
    sensor_object_ch = new Channel<SensorData>(Constants::SENSOR_OBJECT_CHNAME_FREE, Constants::SENSOR_OBJECT_CHNAME_EMPTY);
    termination_timeout_sem = new Semaphore(Constants::ROADOBJECT_TERMINATION_SEMNAME, 0, Constants::TERMINATION_SEMTIMEOUT_MS);

    log(this->name(), "Object created");
}

RoadObject::~RoadObject()
{
    delete sensor_object_ch;
    delete termination_timeout_sem;

    log(name(), "Object destroyed");
}

void RoadObject::run()
{
    // 1. running
    log(name(), "Object is running");

    // 2. working cycle
    while (true) {
        Sleep(rand_in_range(Constants::ROADOBJECT_INTERVAL_RANGE_MS[0], Constants::ROADOBJECT_INTERVAL_RANGE_MS[1]));
        log(name(), "There are road object");
        int chances = rand_in_range(0, 100);
        SensorData data;
        if (chances <= Constants::BARRIER_WEIGHTS[0]) {
            // critical barrier
            data.state = SensorState::CRITICAL_BARRIER;
            data.distance = rand_in_range(30, 50);
            log(name(), "There are critical barrier: " + to_string(data));
        } else if (chances > Constants::BARRIER_WEIGHTS[0] && chances <= Constants::BARRIER_WEIGHTS[1]) {
            // barrier
            data.state = SensorState::BARRIER;
            data.distance = rand_in_range(50, 100);
            log(name(), "There are barrier: " + to_string(data));
        } else {
            data.state = SensorState::NORMAL;
            data.distance = -1;
            log(name(), "Not dangerous object");
        }

        log(name(), "Sending data to sensor controller");
        sensor_object_ch->put(data);

        // check process termination
        bool is_timeout;
        termination_timeout_sem->P(is_timeout);
        if (!is_timeout) {
            log(name(), "ACC system stopped. Object generation stopped. Object cycle completed.");
            data.state = SensorState::STOPPED;
            data.distance = -1;
            sensor_object_ch->put(data);
            return;
        }
    }
}
