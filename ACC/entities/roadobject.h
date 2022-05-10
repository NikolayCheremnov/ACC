#ifndef ROADOBJECT_H
#define ROADOBJECT_H


#include "../core/runnable.h"


class RoadObject : public Runnable
{
public:
    RoadObject(std::string name="RoadObject");
    ~RoadObject() override;

    void run() override;
};

#endif // ROADOBJECT_H
