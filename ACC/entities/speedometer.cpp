#include "speedometer.h"

Speedometer::Speedometer(std::string name) :
    Runnable(name)
{
    speedometer_engine_timeout_ch = new Channel<ACCStateParams>(Constants::SPEEDOMETER_ENGINE_CHNAME_FREE,
                                                               Constants::SPEEDOMETER_ENGINE_CHNAME_EMPTY,
                                                                Constants::SPEEDOMETER_ENGINE_CHTIMEOUT_MS);
    speedometer_brake_timeout_ch = new Channel<ACCStateParams>(Constants::SPEEDOMETER_BRAKE_CHNAME_FREE,
                                                               Constants::SPEEDOMETER_BRAKE_CHNAME_EMPTY,
                                                               Constants::SPEEDOMETER_BRAKE_CHTIMEOUT_MS);
    automobile_speedometer_timeout_ch = new Channel<ACCStateParams>(Constants::AUTOMOBILE_SPEEDOMETER_CHNAME_FREE,
                                                                    Constants::AUTOMOBILE_SPEEDOMETER_CHNAME_EMPTY,
                                                                    Constants::AUTOMOBILE_SPEEDOEMETER_CHTIMEOUT_MS);
    termination_timeout_sem = new Semaphore(Constants::SPEEDOMETER_TERMINATION_SEMNAME, 0, Constants::TERMINATION_SEMTIMEOUT_MS);


    log(this->name(), "Object created");
}

Speedometer::~Speedometer()
{
    delete speedometer_engine_timeout_ch;
    delete speedometer_brake_timeout_ch;
    delete automobile_speedometer_timeout_ch;
    delete termination_timeout_sem;

    log(name(), "Object destroyed");
}

void Speedometer::run()
{
    // 1. running
    log(name(), "Object is running");

    // 2. working cycle
    while (true) {
        // 1. receive data from engine
        log(name(), "Reading engine data");
        bool is_engine_timeout;
        ACCStateParams engine_data = speedometer_engine_timeout_ch->get(is_engine_timeout);
        if (is_engine_timeout) {
            log(name(), "No engine data");
        } else {
            if (rand_in_range(0, 1) == 1)
                engine_data.params.speed += rand_in_range(-10, 10);  // speed deviations
            if (engine_data.state == ACCState::ON)
                log(name(), "Engine data received. Result speed = " + std::to_string(engine_data.params.speed));
        }

        // 2. receive data from brake and 3 - send data to automobile
        log(name(), "Reading brake data");
        bool is_brake_timeout;
        ACCStateParams brake_data = speedometer_brake_timeout_ch->get(is_brake_timeout);
        if (is_brake_timeout)
            log(name(), "No brake data");
        else
            log(name(), "Brake data received. Result speed = " + std::to_string(brake_data.params.speed));

        // 3. check process termination
        bool is_timeout;
        termination_timeout_sem->P(is_timeout);
        if (!is_timeout) {
            log(name(), "ACC system stopped. Speedometer stopped. Object cycle completed.");
            return;
        }

        // 4. then send data to automobile
        if (is_brake_timeout && !is_engine_timeout) {
            log(name(), "Sending engine data to automobile.");
            automobile_speedometer_timeout_ch->put(engine_data);
        } else if (!is_brake_timeout) {
            log(name(), "Brake is activated. Speed = " + std::to_string(brake_data.params.speed) + ". Sending data to automobile.");
             automobile_speedometer_timeout_ch->put(brake_data);
        } else {
            log(name(), "No data for sending");
        }
    }
}
