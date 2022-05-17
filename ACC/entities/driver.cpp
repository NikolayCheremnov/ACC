#include "driver.h"


Driver::Driver(std::string name) :
    Runnable(name)
{
    srand(time(0));

    params_ch = new Channel<ACCParams>(Constants::ACC_PARAMS_CHNAME_FREE, Constants::ACC_PARAMS_CHNAME_EMPTY);
    turn_on_sem = new Semaphore(Constants::ACC_TURN_ON_SEM, 0);
    turn_off_sem = new Semaphore(Constants::ACC_TURN_OFF_SEM, 0);
    termination_timeout_sem = new Semaphore(Constants::DRIVER_TERMINATION_SEMNAME, 0, Constants::TERMINATION_SEMTIMEOUT_MS);

    log(this->name(), "Object created");
}

Driver::~Driver()
{
    delete params_ch;
    delete turn_on_sem;
    delete turn_off_sem;
    delete termination_timeout_sem;

    log(name(), "Object destroyed");
}

void Driver::run()
{
    // 1. running
    log(name(), "Object is running");
    Sleep(Constants::ACC_MODE_PREWORKING_DURATION_MS);

    // 2. send params
    log(name(), "Object is about to switch to ACC mode");
    ACCParams params{ rand_in_range(Constants::ACC_MODE_SPEED_RANGE_MS[0], Constants::ACC_MODE_SPEED_RANGE_MS[1])};
    params.speed -= params.speed % 5;
    params_ch->put(params);

    // 3. start ACC
    turn_on_sem->V();
    log(name(), "Object turned on ACC mode");

    for (int i = 0; i < Constants::ACC_MODE_WORKING_DURATION_MS; i += 1000) {
        // check process termination
        bool is_timeout;
        termination_timeout_sem->P(is_timeout);
        if (!is_timeout) {
            log(name(), "ACC system stopped. Driver control stopped. Object cycle completed.");
            turn_off_sem->V();  // release semaphore
            return;
        }
        log(name(), "Is driving with ACC");
        Sleep(i);
    }

    // 4. stop ACC
    log(name(), "Object is about to switch from ACC mode");
    turn_off_sem->V();
    log(name(), "Object turned off ACC mode");

    // 5. exit
    log(name(), "Object's work cycle is completed");
}
