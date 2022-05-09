#include "steeringwheel.h"

SteeringWheel::SteeringWheel(std::string name) :
    Runnable(name)
{
    params_ch = new Channel<ACCParams>(Constants::ACC_PARAMS_CHNAME_FREE, Constants::ACC_PARAMS_CHNAME_EMPTY);
    turn_on_sem = new Semaphore(Constants::ACC_TURN_ON_SEM, 0);
    turn_off_sem = new Semaphore(Constants::ACC_TURN_OFF_SEM, 0);

    log(this->name(), "Object created");
}

SteeringWheel::~SteeringWheel()
{
    delete params_ch;
    delete turn_on_sem;
    delete turn_off_sem;
}

void SteeringWheel::run()
{
    bool is_timeout;

    // 1. running
    log(name(), "Object is running: wait ACC params");
    ACCParams params = params_ch->get(is_timeout);

    // 2. params received
    log(name(), "Params received (speed = " + std::to_string(params.speed) + "). Waiting for activation ACC mode.");
    turn_on_sem->P();

    // 3. ACC activated
    log(name(), "ACC mode is active. On-board computer is being initialized");

    // TODO: write automobile code here

    // 4. waiting an ACC was stopped
    turn_off_sem->P();
    log(name(), "ACC mode is deactivated. Notification of the on-board computer.");

    // TODO: write automobile code here

    // 5. exit
    log(name(), "Object's work cycle is completed");
}
