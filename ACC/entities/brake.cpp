#include "brake.h"

Brake::Brake(std::string name) :
    Runnable(name)
{

    log(this->name(), "Object created");
}

Brake::~Brake()
{

    log(name(), "Object destroyed");
}

void Brake::run()
{

}
