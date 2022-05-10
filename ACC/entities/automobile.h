#ifndef AUTOMOBILE_H
#define AUTOMOBILE_H

#include "../core/runnable.h"
#include "../core/channel.h"

#include "../structures/accstate.h"
#include "../structures/constants.h"


class Automobile : public Runnable
{
private:
    // Wheel-automobile channels
    Channel<ACCStateParams>* ACC_state_ch;
    Channel<ACCStateParams>* ACC_state_timeout_ch;

    // Automobile-engine channel
    Channel<ACCStateParams>* engine_ch;

    // Automobile-speedometer channel
    Channel<ACCStateParams>* speedometer_timeout_ch;


public:
    Automobile(std::string name="Automobile");
    ~Automobile() override;

    void run() override;
};

#endif // AUTOMOBILE_H
