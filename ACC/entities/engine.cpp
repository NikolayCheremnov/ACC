#include "engine.h"

Engine::Engine(std::string name) :
    Runnable(name)
{
    automobile_engine_ch = new Channel<ACCStateParams>(Constants::AUTOMOBILE_ENGINE_CHNAME_FREE, Constants::AUTOMOBILE_ENGINE_CHNAME_EMPTY);
    speedometer_engine_ch = new Channel<ACCStateParams>(Constants::SPEEDOMETER_ENGINE_CHNAME_FREE, Constants::SPEEDOMETER_ENGINE_CHNAME_EMPTY);

    log(this->name(), "Object created");
}

Engine::~Engine()
{
    delete automobile_engine_ch;
    delete speedometer_engine_ch;

    log(name(), "Object destroyed");
}

void Engine::run()
{
    // 1. running
    log(name(), "Object is running");

    // 2. working cycle
    while (true) {
        // 1. receive data from automobile
        log(name(), "Waiting data from automobile");
        bool is_timeout;
        ACCStateParams automobile_data = automobile_engine_ch->get(is_timeout);
        if (automobile_data.state == ACCState::OFF) {
            log(name(), "ACC mode turned OFF. Engine system is stopped. Object cycle completed.");
            break;
        }

        // 2. send data to speedometer
        log(name(), "Received data from automobile. Make speed corrections to " + std::to_string(automobile_data.params.speed));
        speedometer_engine_ch->put(automobile_data);
    }
}
