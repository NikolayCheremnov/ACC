#ifndef AUTOMOBILE_H
#define AUTOMOBILE_H

#include <vector>

#include "../core/runnable.h"
#include "../core/channel.h"

#include "../structures/accstate.h"
#include "../structures/constants.h"
#include "../structures/sensordata.h"


class Automobile : public Runnable
{
private:
    // Wheel-automobile channels
    Channel<ACCStateParams>* ACC_state_ch;
    Channel<ACCStateParams>* ACC_state_timeout_ch;

    // Automobile-engine channel
    Channel<ACCStateParams>* automobile_engine_ch;

    // Automobile-speedometer timeout channel
    Channel<ACCStateParams>* automobile_speedometer_timeout_ch;

    // Automobile-sensor timeout channel
    Channel<SensorData>* automobile_sensor_timeout_ch;

    // Automobile-brake semaphore
    Channel<ACCStateParams>* automobile_brake_ch;

    // System semaphores
    std::vector<Semaphore*> system_termination_semaphores;

    // brake semaphore
    Semaphore* automobile_brake_sem;

public:
    Automobile(std::string name="Automobile");
    ~Automobile() override;

    void run() override;
};

#endif // AUTOMOBILE_H
