#include "sensor.h"

Sensor::Sensor(std::string name) :
    Runnable(name)
{
    sensor_object_ch = new Channel<SensorData>(Constants::SENSOR_OBJECT_CHNAME_FREE, Constants::SENSOR_OBJECT_CHNAME_EMPTY);
    automobile_sensor_timeout_ch = new Channel<SensorData>(Constants::AUTOMOBILE_SENSOR_CHNAME_FREE,
                                                          Constants::AUTOMOBILE_SENSOR_CHNAME_EMPTY,
                                                          Constants::AUTOMOBILE_SENSOR_CHTIMEOUT_MS);
    termination_timeout_sem = new Semaphore(Constants::SENSOR_TERMINATION_SEMNAME, 0, Constants::TERMINATION_SEMTIMEOUT_MS);

    log(this->name(), "Object created");
}

Sensor::~Sensor()
{
    delete sensor_object_ch;
    delete automobile_sensor_timeout_ch;
    delete termination_timeout_sem;

    log(name(), "Object destroyed");
}

void Sensor::run()
{
    // 1. running
    log(name(), "Object is running");

    // 2. working cycle
    while (true) {
        log(name(), "Detecting objects.");
        bool is_timeout;
        SensorData data = sensor_object_ch->get(is_timeout);

        if (data.state == SensorState::STOPPED) {
            // stopped
            log(name(), "Sensor object stopped. Object cycle completed.");
            return;
        }
        else if (data.state == SensorState::NORMAL) {
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

        // check process termination
        termination_timeout_sem->P(is_timeout);
        if (!is_timeout) {
            log(name(), "ACC system stopped. Sensor working stopped. Object cycle completed.");
            return;
        }
    }
}
