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

    // 5. brake semphore
    automobile_brake_ch = new Channel<ACCStateParams>(Constants::AUTOMOBILE_BRAKE_CHNAME_FREE,
                                                      Constants::AUTOMOBILE_BRAKE_CHNAME_EMPTY);


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
    int required_speed = acc_state.params.speed;

    // 3. ACC control - main loop
    log(name(), "Driving has been switched to ACC. Automobile cycle started.");
    bool is_stop = false;
    while (!is_stop) {
        // 1. send info to engine
        automobile_engine_ch->put(acc_state);
        log(name(), "Speed adjusting sended to engine. Speed = " + std::to_string(acc_state.params.speed));

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
        acc_state = ACC_state_timeout_ch->get(is_wheel_timeout);
        if (is_wheel_timeout)
            log(name(), "No steeringwheel data");
        else
            log(name(), "Steeringwheel data received. Start of ACC shutdown.");


        // 5. process results:
        //      - emergency braking - high priority
        //      - ACC turned off - next priority
        //      - next itreration - low priority


        // 5.0. full stop
        if (!is_speedometer_timeout && speedometerData.params.speed == 0) {
            log(name(), "Full stop. Object's work cycle is completed");
            is_stop = true;
        }
        // 5.1. emergency braking - high priority
        else if (!is_sensor_timeout && sensorData.state == SensorState::CRITICAL_BARRIER) {
            log(name(), "Data on a critical barrier has been received (distance = " + std::to_string(sensorData.distance) + "). " +
                "Emergency braking call");
            acc_state.params.speed = speedometerData.params.speed; // to stop
            acc_state.state = ACCState::ABORTED;
            automobile_brake_ch->put(acc_state);
        }
        // 5.2. ACC turned off
        else if (acc_state.state == ACCState::OFF) {
            log(name(), "ACC turned off by driver. Object's work cycle is completed");
            automobile_brake_ch->put(acc_state);
            is_stop = true;
        }
        // 5.3. else next iteration
        else {
            acc_state.state = ACCState::ON;
            acc_state.params.speed = required_speed;
        }
    }
}
