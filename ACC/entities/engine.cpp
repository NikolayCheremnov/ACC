#include "engine.h"

Engine::Engine(std::string name) :
    Runnable(name)
{
    automobile_ch = new Channel<ACCState>(Constants::AUTOMOBILE_ENGINE_CHNAME_EMPTY, Constants::AUTOMOBILE_ENGINE_CHNAME_FREE);

    log(this->name(), "Object created");
}

Engine::~Engine()
{
    delete automobile_ch;

    log(name(), "Object destroyed");
}

void Engine::run()
{

}
