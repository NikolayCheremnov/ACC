#ifndef SENSORDATA_H
#define SENSORDATA_H


#include <string>


enum class SensorState {
    NORMAL,
    BARRIER,
    CRITICAL_BARRIER,
    STOPPED
};

struct SensorData {
    SensorState state;
    double distance;
};


std::string to_string(const SensorData& sensor_data);
bool priorityFunctor(const SensorData& o1, const SensorData& o2);

#endif // SENSORDATA_H
