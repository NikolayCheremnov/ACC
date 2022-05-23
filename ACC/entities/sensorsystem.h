#ifndef SENSORSYSTEM_H
#define SENSORSYSTEM_H


#include <queue>
#include <vector>
#include <functional>
#include <windows.h>
#include <thread>

#include "../core/runnable.h"
#include "../core/channel.h"
#include "../core/semaphore.h"

#include "../structures/sensordata.h"
#include "../structures/constants.h"


class SensorSystem : public Runnable
{
private:
    std::priority_queue<
        SensorData, std::vector<SensorData>, std::function<bool(const SensorData&, const SensorData&)>
    > sensorDataQueue;

    // condition variables
    CONDITION_VARIABLE BufferNotEmpty;
    CONDITION_VARIABLE BufferNotFull;
    CRITICAL_SECTION BufferLock;
    BOOL StopRequested = FALSE;

    // bridge for other system part
    Channel<SensorData>* automobile_sensor_timeout_ch;
    Semaphore* termination_timeout_sem;

public:
    SensorSystem(std::string name="SensorSystem");
    ~SensorSystem() override;

    void run() override;

    // threads processors
    void SingleSensorProc(int number);
    void SensorControlProc();

    // run methods
    static void RunSensorControlProc(SensorSystem* obj);
    static void RunSingleSensorProc(SensorSystem* obj);

    static int current_sensors_count;

};

#endif // SENSORSYSTEM_H
