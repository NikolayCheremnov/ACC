#include "brake.h"

Brake::Brake(std::string name) :
    Runnable(name)
{
    automobile_brake_ch = new Channel<ACCStateParams>(Constants::AUTOMOBILE_BRAKE_CHNAME_FREE, Constants::AUTOMOBILE_BRAKE_CHNAME_EMPTY);
    speedometer_brake_timeout_ch = new Channel<ACCStateParams>(Constants::SPEEDOMETER_BRAKE_CHNAME_FREE, Constants::SPEEDOMETER_BRAKE_CHNAME_EMPTY,
                                                               Constants::SPEEDOMETER_BRAKE_CHTIMEOUT_MS);
    automobile_brake_timeout_sem = new Semaphore(Constants::AUTOMOBILE_BRAKE_SEMNAME, 0, Constants::AUTOMOBILE_BRAKE_SEMTIMEOUT_MS);
    automobile_brake_stop_timeout_sem = new Semaphore(Constants::AUTOMOBILE_BRAKE_STOP_SEM_NAME, 0, Constants::AUTOMOBILE_BRAKE_STOP_SEMTIMEOUT_MS);

    log(this->name(), "Object created");
}

Brake::~Brake()
{
    delete automobile_brake_ch;
    delete speedometer_brake_timeout_ch;
    delete automobile_brake_timeout_sem;
    delete automobile_brake_stop_timeout_sem;

    log(name(), "Object destroyed");
}

void Brake::run()
{
    // 1. running
    log(name(), "Object is running");

    // 2. working cycle
    while (true) {
        // 1. receive data from automobile
        log(name(), "Object waiting signal from automobile");
        bool is_timeout;
        ACCStateParams signal = automobile_brake_ch->get(is_timeout);

        // stop ig ACC turned off
        if (signal.state == ACCState::OFF) {
            log(name(), "ACC mode turned OFF. Brake system is stopped. Object cycle completed.");
            return;
        }

        // 2. making braking
        log(name(), "Making breaking");
        Sleep(Constants::BRAKING_INTERVAL_MS);      // braking delay
        bool is_stop = false;
        for (int braking_time = 0; braking_time < Constants::BREAKING_DURATION_MS && !is_stop; braking_time += Constants::BRAKING_INTERVAL_MS) {
            signal.params.speed -= Constants::BRAKING_ACCELERATION_MSS * Constants::BRAKING_INTERVAL_MS / 1000.0;  // braking result
            if (signal.params.speed <= 0) {
                signal.params.speed = 0;
                log(name(), "Full stop");
                is_stop = true;        // register full stop
            }

            log(name(), std::to_string(braking_time) + " ms. of braking has passed. "
                                                       "Speed = " + std::to_string(signal.params.speed));

            speedometer_brake_timeout_ch->put(signal);  // send data to speedometer

            // check braking cycle termination
            automobile_brake_stop_timeout_sem->P(is_timeout);
            if (!is_timeout && !is_stop) {
                // received braking termination from automobile
                log(name(), "Brake cycle was terminated by automobile");
                is_stop = true;
            }
        }

        automobile_brake_timeout_sem->V();          // release brake semaphore
    }
}
