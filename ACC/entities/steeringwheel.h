#ifndef STEERINGWHEEL_H
#define STEERINGWHEEL_H


#include "../core/runnable.h"
#include "../core/channel.h"

#include "../structures/constants.h"
#include "../structures/accparams.h"
#include "../structures/accstate.h"


class SteeringWheel : public Runnable
{
    // Driver-wheel channel and semaphores
    Channel<ACCParams>* params_ch;
    Semaphore* turn_on_sem;
    Semaphore* turn_off_sem;

    // Automobile-wheel channel
    Channel<ACCStateParams>* ACC_state_ch;


public:
    SteeringWheel(std::string name="SteeringWheel");
    ~SteeringWheel() override;

    void run() override;
};

#endif // STEERINGWHEEL_H
