#ifndef ROADOBJECT_H
#define ROADOBJECT_H


#include "../core/runnable.h"
#include "../core/channel.h"
#include "../core/semaphore.h"

#include "../structures/constants.h"
#include "../structures/sensordata.h"

#include "../utils/utils.h"


class RoadObject : public Runnable
{
private:
    Channel<SensorData>* sensor_object_ch;
    Semaphore* termination_timeout_sem;

public:
    RoadObject(std::string name="RoadObject");
    ~RoadObject() override;

    void run() override;
};

#endif // ROADOBJECT_H
