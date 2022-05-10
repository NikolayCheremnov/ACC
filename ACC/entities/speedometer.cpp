#include "speedometer.h"

Speedometer::Speedometer(std::string name) :
    Runnable(name)
{

    log(this->name(), "Object created");
}

Speedometer::~Speedometer()
{

    log(name(), "Object destroyed");
}

void Speedometer::run()
{

}
