#ifndef SENSOR_H
#define SENSOR_H


#include "../core/runnable.h"
#include "../core/channel.h"
#include "../core/semaphore.h"

#include "../structures/sensordata.h"
#include "../structures/constants.h"


class Sensor : public Runnable
{
private:
    Channel<SensorData>* sensor_object_ch;
    Channel<SensorData>* automobile_sensor_timeout_ch;
    Semaphore* termination_timeout_sem;

public:
    Sensor(std::string name="Sensor");
    ~Sensor() override;

    void run() override;
};

#endif // SENSOR_H
