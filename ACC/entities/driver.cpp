#include "driver.h"

Driver::Driver()
{
    params_ch = new Channel<ACCParams>(Constants::ACC_PARAMS_CHNAME_FREE, Constants::ACC_PARAMS_CHNAME_EMPTY);
    turn_on_sem = new Semaphore(Constants::ACC_TURN_ON_SEM, 0);
    turn_off_sem = new Semaphore(Constants::ACC_TURN_OFF_SEM, 0);

    log("Driver", "Object created");
}

Driver::~Driver()
{
    delete params_ch;
    delete turn_on_sem;
    delete turn_off_sem;
}

void Driver::run()
{
    // 1. running
    log("Driver", "Object is running");
    Sleep(1000);

    // 2. send params
    log("Driver", "Object is about to switch to ACC mode");
    ACCParams params{rand_in_range(50, 110)};
    params.speed -= params.speed % 5;
    params_ch->put(params);


    // 3. start ACC
    turn_on_sem->V();
    log("Driver", "Object turned on ACC mode");
    Sleep(30000);       // wait

    // 4. stop ACC
    log("Driver", "Object is about to switch from ACC mode");
    turn_off_sem->V();
    log("Driver", "Object turned on ACC mode");

    // 5. exit
    log("Driver", "Object's work cycle is completed");
}
