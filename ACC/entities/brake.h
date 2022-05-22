#ifndef BRAKE_H
#define BRAKE_H


#include "../core/runnable.h"
#include "../core/channel.h"

#include "../structures/accstate.h"
#include "../structures/constants.h"


class Brake : public Runnable
{
private:
    Channel<ACCStateParams>* automobile_brake_ch;
    Channel<ACCStateParams>* speedometer_brake_timeout_ch;
    Semaphore* automobile_brake_timeout_sem;
    Semaphore* automobile_brake_stop_timeout_sem;

public:
    Brake(std::string name="Brake");
    ~Brake() override;

    void run() override;
};

#endif // BRAKE_H
