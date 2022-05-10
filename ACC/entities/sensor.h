#ifndef SENSOR_H
#define SENSOR_H


#include "../core/runnable.h"


class Sensor : public Runnable
{
public:
    Sensor(std::string name="Sensor");
    ~Sensor() override;

    void run() override;
};

#endif // SENSOR_H
