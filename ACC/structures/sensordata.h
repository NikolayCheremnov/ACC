#ifndef SENSORDATA_H
#define SENSORDATA_H


#include <string>


enum class SensorState {
    NORMAL,
    BARRIER,
    CRITICAL_BARRIER
};

struct SensorData {
    SensorState state;
    double distance;
};


std::string to_string(SensorData& sensor_data);

#endif // SENSORDATA_H
