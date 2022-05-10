#include "roadobject.h"

RoadObject::RoadObject(std::string name) :
    Runnable(name)
{

    log(this->name(), "Object created");
}

RoadObject::~RoadObject()
{

    log(name(), "Object destroyed");
}

void RoadObject::run()
{

}
