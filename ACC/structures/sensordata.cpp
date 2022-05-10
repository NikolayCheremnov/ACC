#include "sensordata.h"


std::string to_string(SensorData &sensor_data)
{
    switch (sensor_data.state) {
    case SensorState::NORMAL: return "NORMAL";
    case SensorState::BARRIER: return "BARRIER, distantce = " + std::to_string(sensor_data.distance);
    case SensorState::CRITICAL_BARRIER: return "CRITICAL BARRIER, distance = " + std::to_string(sensor_data.distance);
    default: return "ERROR";
    }
}
