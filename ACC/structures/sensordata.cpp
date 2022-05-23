#include "sensordata.h"


std::string to_string(const SensorData &sensor_data)
{
    switch (sensor_data.state) {
    case SensorState::NORMAL: return "NORMAL";
    case SensorState::STOPPED: return "STOPPED";
    case SensorState::BARRIER: return "BARRIER, distance = " + std::to_string(sensor_data.distance);
    case SensorState::CRITICAL_BARRIER: return "CRITICAL BARRIER, distance = " + std::to_string(sensor_data.distance);
    default: return "ERROR";
    }
}

bool priorityFunctor(const SensorData &o1, const SensorData &o2)
{
    if (o1.state == SensorState::STOPPED)
        return true;    // right
    if (o2.state == SensorState::STOPPED)
        return false;   // left

    if (o1.state != SensorState::NORMAL && o2.state == SensorState::NORMAL)
        return false;   // left
    if (o1.state == SensorState::NORMAL && o2.state != SensorState::NORMAL)
        return true;    // right

    if (o1.state ==  o2.state)
        return o1.distance > o2.distance;   // left or right

    if (o1.state == SensorState::CRITICAL_BARRIER)
        return false;   // left
    if (o2.state == SensorState::CRITICAL_BARRIER)
        return true;    // right

    throw "Bad SensorData comparation";
}
