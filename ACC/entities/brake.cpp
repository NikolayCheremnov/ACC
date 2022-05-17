#include "brake.h"

Brake::Brake(std::string name) :
    Runnable(name)
{
    automobile_brake_ch = new Channel<ACCStateParams>(Constants::AUTOMOBILE_BRAKE_CHNAME_FREE, Constants::AUTOMOBILE_BRAKE_CHNAME_EMPTY);
    speedometer_brake_timeout_ch = new Channel<ACCStateParams>(Constants::SPEEDOMETER_BRAKE_CHNAME_FREE, Constants::SPEEDOMETER_BRAKE_CHNAME_EMPTY,
                                                               Constants::SPEEDOMETER_BRAKE_CHTIMEOUT_MS);
    automobile_brake_sem = new Semaphore(Constants::AUTOMOBILE_BRAKE_SEMNAME, 1);

    log(this->name(), "Object created");
}

Brake::~Brake()
{
    delete automobile_brake_ch;
    delete speedometer_brake_timeout_ch;
    delete automobile_brake_sem;

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
        signal.params.speed -= Constants::BRAKING_ACCELERATION;  // braking result
        if (signal.params.speed < 0)
            signal.params.speed = 0;

        log(name(), std::to_string(Constants::BRAKING_INTERVAL_MS) + " ms. of braking has passed. "
                                                                     "Speed = " + std::to_string(signal.params.speed));

        // 3. send data to speedometer
        speedometer_brake_timeout_ch->put(signal);  // send data to speedometer
        automobile_brake_sem->V();
    }
}
