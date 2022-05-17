#include "steeringwheel.h"

SteeringWheel::SteeringWheel(std::string name) :
    Runnable(name)
{
    // Driver-wheel channel and semaphores
    params_ch = new Channel<ACCParams>(Constants::ACC_PARAMS_CHNAME_FREE, Constants::ACC_PARAMS_CHNAME_EMPTY);
    turn_on_sem = new Semaphore(Constants::ACC_TURN_ON_SEM, 0);
    turn_off_sem = new Semaphore(Constants::ACC_TURN_OFF_SEM, 0);

    // Automobile-wheel channel
    ACC_state_ch = new Channel<ACCStateParams>(Constants::ACC_STATE_CHNAME_FREE, Constants::ACC_STATE_CHNAME_EMPTY);

    // termination sem
    termination_timeout_sem = new Semaphore(Constants::STEERINGWHEEL_TERMINATION_SEMNAME, 0, Constants::TERMINATION_SEMTIMEOUT_MS);

    log(this->name(), "Object created");
}

SteeringWheel::~SteeringWheel()
{
    delete params_ch;
    delete turn_on_sem;
    delete turn_off_sem;
    delete ACC_state_ch;
    delete termination_timeout_sem;

    log(name(), "Object destroyed");
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

    // 3. ACC activated, automobile notifications
    log(name(), "ACC mode is active. On-board computer is being initialized");
    ACCStateParams state{ACCState::ON, params};
    ACC_state_ch->put(state);
    log(name(), "ACC state sended to automobile (on-board computer). Waiting ACC mode deactivation.");

    // 4. waiting an ACC was stopped
    turn_off_sem->P();

    // check system termination
    termination_timeout_sem->P(is_timeout);
    if (!is_timeout) {
        // system was terminated
        log(name(), "ACC system stopped. Control deactivated. Object cycle completed.");
        return;
    } else {
        // system was stopped normal
        log(name(), "ACC mode is deactivated. Notification of the on-board computer.");
        ACCStateParams terminate_state{ACCState::OFF, ACCParams{0}};
        ACC_state_ch->put(terminate_state);
        log(name(), "ACC state sended to automobile (on-board computer)");

        // 5. exit
        log(name(), "Object's work cycle is completed");
    }
}
