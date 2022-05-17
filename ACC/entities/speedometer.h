#ifndef SPEEDOMETER_H
#define SPEEDOMETER_H


#include "../core/runnable.h"
#include "../core/channel.h"
#include "../core/semaphore.h"

#include "../structures/accstate.h"
#include "../structures/constants.h"

#include "../utils/utils.h"


class Speedometer : public Runnable
{
private:
    Channel<ACCStateParams>* speedometer_engine_timeout_ch;
    Channel<ACCStateParams>* speedometer_brake_timeout_ch;
    Channel<ACCStateParams>* automobile_speedometer_timeout_ch;
    Semaphore* termination_timeout_sem;

public:
    Speedometer(std::string name="Speedometer");
    ~Speedometer() override;

    void run() override;

};

#endif // SPEEDOMETER_H
