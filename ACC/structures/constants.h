#ifndef CONSTANTS_H
#define CONSTANTS_H


#include <string>


class Constants
{
public:

    // Driver-wheel channel semaphores names
    static std::string ACC_PARAMS_CHNAME_FREE;
    static std::string ACC_PARAMS_CHNAME_EMPTY;

    // Driver-wheel semaphores names
    static std::string ACC_TURN_ON_SEM;
    static std::string ACC_TURN_OFF_SEM;

    // Wheel-automobile channel names and timeout
    static std::string ACC_STATE_CHNAME_FREE;
    static std::string ACC_STATE_CHNAME_EMPTY;
    static int ACC_STATE_CHTIMEOUT_MS;

    // Automobile-engine channel names
    static std::string AUTOMOBILE_ENGINE_CHNAME_FREE;
    static std::string AUTOMOBILE_ENGINE_CHNAME_EMPTY;

    // Automobile-speedometer channel names and timeout
    static std::string AUTOMOBILE_SPEEDOMETER_CHNAME_FREE;
    static std::string AUTOMOBILE_SPEEDOMETER_CHNAME_EMPTY;
    static int AUTOMOBILE_SPEEDOEMETER_CHTIMEOUT_MS;

    // Automobile-sensor channel names and timeout
    static std::string AUTOMOBILE_SENSOR_CHNAME_FREE;
    static std::string AUTOMOBILE_SENSOR_CHNAME_EMPTY;
    static int AUTOMOBILE_SENSOR_CHTIMEOUT_MS;

    // Automobile-brake channel names
    static std::string AUTOMOBILE_BRAKE_CHNAME_FREE;
    static std::string AUTOMOBILE_BRAKE_CHNAME_EMPTY;

};

#endif // CONSTANTS_H
