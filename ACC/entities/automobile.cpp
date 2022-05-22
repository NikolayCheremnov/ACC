#include "automobile.h"

Automobile::Automobile(std::string name) :
    Runnable(name)
{
    // 1. wheel channels
    ACC_state_ch = new Channel<ACCStateParams>(Constants::ACC_STATE_CHNAME_FREE,
                                               Constants::ACC_STATE_CHNAME_EMPTY);
    ACC_state_timeout_ch = new Channel<ACCStateParams>(Constants::ACC_STATE_CHNAME_FREE,
                                                       Constants::ACC_STATE_CHNAME_EMPTY,
                                                       Constants::ACC_STATE_CHTIMEOUT_MS);

    // 2. engine channel
    automobile_engine_ch = new Channel<ACCStateParams>(Constants::AUTOMOBILE_ENGINE_CHNAME_FREE,
                                                       Constants::AUTOMOBILE_ENGINE_CHNAME_EMPTY);

    // 3. speedometer channel
    automobile_speedometer_timeout_ch = new Channel<ACCStateParams>(Constants::AUTOMOBILE_SPEEDOMETER_CHNAME_FREE,
                                                         Constants::AUTOMOBILE_SPEEDOMETER_CHNAME_EMPTY,
                                                         Constants::AUTOMOBILE_SPEEDOEMETER_CHTIMEOUT_MS);

    // 4. sensor channel
    automobile_sensor_timeout_ch = new Channel<SensorData>(Constants::AUTOMOBILE_SENSOR_CHNAME_FREE,
                                                           Constants::AUTOMOBILE_SENSOR_CHNAME_EMPTY,
                                                           Constants::AUTOMOBILE_SENSOR_CHTIMEOUT_MS);

    // 5. brake channel and semaphores
    automobile_brake_ch = new Channel<ACCStateParams>(Constants::AUTOMOBILE_BRAKE_CHNAME_FREE,
                                                      Constants::AUTOMOBILE_BRAKE_CHNAME_EMPTY);
    automobile_brake_timeout_sem = new Semaphore(Constants::AUTOMOBILE_BRAKE_SEMNAME, 1, Constants::AUTOMOBILE_BRAKE_SEMTIMEOUT_MS);
    automobile_brake_stop_timeout_sem = new Semaphore(Constants::AUTOMOBILE_BRAKE_STOP_SEM_NAME, 0, Constants::AUTOMOBILE_BRAKE_STOP_SEMTIMEOUT_MS);

    // 6. termination semaphores
    system_termination_semaphores.push_back(new Semaphore(Constants::DRIVER_TERMINATION_SEMNAME, 0, Constants::TERMINATION_SEMTIMEOUT_MS));
    system_termination_semaphores.push_back(new Semaphore(Constants::STEERINGWHEEL_TERMINATION_SEMNAME, 0, Constants::TERMINATION_SEMTIMEOUT_MS));
    system_termination_semaphores.push_back(new Semaphore(Constants::ROADOBJECT_TERMINATION_SEMNAME, 0, Constants::TERMINATION_SEMTIMEOUT_MS));
    system_termination_semaphores.push_back(new Semaphore(Constants::SENSOR_TERMINATION_SEMNAME, 0, Constants::TERMINATION_SEMTIMEOUT_MS));
    system_termination_semaphores.push_back(new Semaphore(Constants::BRAKE_TERMINATION_SEMNAME, 0, Constants::TERMINATION_SEMTIMEOUT_MS));
    system_termination_semaphores.push_back(new Semaphore(Constants::ENGINE_TERMINATION_SEMNAME, 0, Constants::TERMINATION_SEMTIMEOUT_MS));
    system_termination_semaphores.push_back(new Semaphore(Constants::SPEEDOMETER_TERMINATION_SEMNAME, 0, Constants::TERMINATION_SEMTIMEOUT_MS));


    log(this->name(), "Object created");
}

Automobile::~Automobile()
{
    delete ACC_state_ch;
    delete ACC_state_timeout_ch;
    delete automobile_engine_ch;
    delete automobile_speedometer_timeout_ch;
    delete automobile_sensor_timeout_ch;
    delete automobile_brake_ch;
    delete automobile_brake_timeout_sem;
    delete automobile_brake_stop_timeout_sem;

    for (auto termination_sem : system_termination_semaphores)
        delete termination_sem;

    log(name(), "Object destroyed");
}

void Automobile::run()
{
    // 1. running
    log(name(), "Object is running");

    // 2. waiting going to ACC
    bool is_timeout;
    log(name(), "Object is waiting to receive ACC control");
    ACCStateParams acc_state = ACC_state_ch->get(is_timeout);

    // help variables
    int required_speed = acc_state.params.speed;
    SensorState prev_sensor_state = SensorState::NORMAL;

    // 3. ACC control - main loop
    log(name(), "Driving has been switched to ACC. Automobile cycle started.");

    while (acc_state.state != ACCState::OFF) {

        // 1. send info to engine
        if (prev_sensor_state != SensorState::CRITICAL_BARRIER) {
            automobile_engine_ch->put(acc_state);
            log(name(), "Speed adjusting sended to engine. Required speed = " + std::to_string(acc_state.params.speed));
        }

        // 2. receive data from speedometer
        log(name(), "Reading speedometer data");
        bool is_speedometer_timeout;
        ACCStateParams speedometerData = automobile_speedometer_timeout_ch->get(is_speedometer_timeout);
        if (is_speedometer_timeout)
            log(name(), "No speedometer data");
        else
            log(name(), "Speedometer data received. Speed = " + std::to_string(speedometerData.params.speed));

        // 3. receive data from sensor
        log(name(), "Reading sensor data");
        bool is_sensor_timeout;
        SensorData sensorData = automobile_sensor_timeout_ch->get(is_sensor_timeout);
        if (is_sensor_timeout)
            log(name(), "No sensor data");
        else
            log(name(), "Sensor data received. Data: " + to_string(sensorData));

        // 4. receive data from wheel
        log(name(), "Reading steeringwheel data");
        bool is_wheel_timeout;
        ACCStateParams wheelData = ACC_state_timeout_ch->get(is_wheel_timeout);
        if (is_wheel_timeout)
            log(name(), "No steeringwheel data");
        else
            log(name(), "Steeringwheel data received. Start of ACC shutdown.");


        // 5. process results:
        //      - braking - high priority
        //      - ACC turned off - next priority
        //      - next itreration - low priority


        if (!is_speedometer_timeout && speedometerData.params.speed == 0) {
            // 0) - full stop
            log(name(), "Full stop (speed == 0). Object's work cycle is completed");
            acc_state.state = ACCState::OFF;
        }
        else if (!is_sensor_timeout && sensorData.state == SensorState::BARRIER) {
            // 1) - barrier
            log(name(), "Data on a barrier has been received (distance = " + std::to_string(sensorData.distance) + "). " +
                "Reduction in speed is requested");
            acc_state.params.speed = required_speed * 0.8;  // to reduce speed
        }
        else if ((!is_sensor_timeout && sensorData.state == SensorState::CRITICAL_BARRIER) ||
                 (is_sensor_timeout && prev_sensor_state == SensorState::CRITICAL_BARRIER)) {
            // 2) - critical barrier
            log(name(), "Data on a critical barrier has been received (distance = " + std::to_string(sensorData.distance) + "). " +
                "Braking is requested");
            prev_sensor_state = SensorState::CRITICAL_BARRIER;
            speedometerData = automobile_speedometer_timeout_ch->get(is_speedometer_timeout);   // read last actual speed
            if (speedometerData.params.speed == 0) {
                // full stop
                log(name(), "Full stop (speed == 0). Object's work cycle is completed");
                acc_state.state = ACCState::OFF;
            } else {
                acc_state.params.speed = speedometerData.params.speed;  // real speed
                bool is_brake_sem_timeout;
                automobile_brake_timeout_sem->P(is_brake_sem_timeout);  // wait braking
                if (is_brake_sem_timeout) {
                    log(name(), "Brake already start braking cycle. Braking passed");
                } else {
                    automobile_brake_ch->put(acc_state);    // braking
                    log(name(), "Brake request sended");
                }
            }
        } else if (!is_sensor_timeout && sensorData.state == SensorState::NORMAL && prev_sensor_state == SensorState::CRITICAL_BARRIER) {
            // 3) - critical barrier has been overcome
            log(name(), "Сritical barrier has been overcome. Working next.");
            acc_state.params.speed = required_speed;
            prev_sensor_state = SensorState::NORMAL;
            automobile_brake_stop_timeout_sem->V();
        }
        else if (wheelData.state == ACCState::OFF) {
            // 4) - acc turned off
            log(name(), "ACC turned off by driver. Object's work cycle is completed");
            acc_state.state = ACCState::OFF;
        } 
        else {
            // 5) next iteration
            log(name(), "Maintaining standard speed = " + std::to_string(required_speed));
            acc_state.params.speed = required_speed;
        }
    }

    // shut down components
    // 1 - shut diwn waiting compnents
    automobile_brake_ch->put(acc_state);
    automobile_engine_ch->put(acc_state);

    // 2 - end of cycle - send termination signals
    for (auto termination_sem : system_termination_semaphores)
        termination_sem->V();
}
