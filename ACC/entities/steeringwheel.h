#ifndef STEERINGWHEEL_H
#define STEERINGWHEEL_H


#include "../core/runnable.h"
#include "../core/channel.h"

#include "../structures/constants.h"
#include "../structures/accparams.h"


class SteeringWheel : public Runnable
{
    Channel<ACCParams>* params_ch;
    Semaphore* turn_on_sem;
    Semaphore* turn_off_sem;
public:
    SteeringWheel(std::string name="SteeringWheel");
    ~SteeringWheel();

    void run() override;
};

#endif // STEERINGWHEEL_H
