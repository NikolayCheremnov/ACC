#include "sensor.h"

Sensor::Sensor(std::string name) :
    Runnable(name)
{

    log(this->name(), "Object created");
}

Sensor::~Sensor()
{

    log(name(), "Object destroyed");
}

void Sensor::run()
{

}
