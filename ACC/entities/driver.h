#ifndef DRIVER_H
#define DRIVER_H


#include "../core/runnable.h"
#include "../core/channel.h"
#include "../core/semaphore.h"

#include "../structures/constants.h"
#include "../structures/accparams.h"

#include "../utils/utils.h"



class Driver : public Runnable
{
private:
    Channel<ACCParams>* params_ch;
    Semaphore* turn_on_sem;
    Semaphore* turn_off_sem;
    Semaphore* termination_timeout_sem;

public:
    Driver(std::string name="Driver");
    ~Driver() override;

    void run() override;

};

#endif // DRIVER_H
