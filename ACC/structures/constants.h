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

    // Automobile-brake channel names and semaphore name
    static std::string AUTOMOBILE_BRAKE_CHNAME_FREE;
    static std::string AUTOMOBILE_BRAKE_CHNAME_EMPTY;
    static std::string AUTOMOBILE_BRAKE_SEMNAME;
    static int AUTOMOBILE_BRAKE_SEMTIMEOUT_MS;
    static std::string AUTOMOBILE_BRAKE_STOP_SEM_NAME;
    static int AUTOMOBILE_BRAKE_STOP_SEMTIMEOUT_MS;

    // Speedometer-engine channel names and timeout
    static std::string SPEEDOMETER_ENGINE_CHNAME_FREE;
    static std::string SPEEDOMETER_ENGINE_CHNAME_EMPTY;
    static int SPEEDOMETER_ENGINE_CHTIMEOUT_MS;

    // Speedometer-brake channel names and timeout
    static std::string SPEEDOMETER_BRAKE_CHNAME_FREE;
    static std::string SPEEDOMETER_BRAKE_CHNAME_EMPTY;
    static int SPEEDOMETER_BRAKE_CHTIMEOUT_MS;

    // Sensor-object channel names
    static std::string SENSOR_OBJECT_CHNAME_FREE;
    static std::string SENSOR_OBJECT_CHNAME_EMPTY;

    // Termination semaphores names and timeout
    static std::string DRIVER_TERMINATION_SEMNAME;
    static std::string STEERINGWHEEL_TERMINATION_SEMNAME;
    static std::string ROADOBJECT_TERMINATION_SEMNAME;
    static std::string SENSOR_TERMINATION_SEMNAME;
    static std::string BRAKE_TERMINATION_SEMNAME;
    static std::string ENGINE_TERMINATION_SEMNAME;
    static std::string SPEEDOMETER_TERMINATION_SEMNAME;
    static int TERMINATION_SEMTIMEOUT_MS;

    // plug constants
    static int ACC_MODE_PREWORKING_DURATION_MS;
    static int ACC_MODE_WORKING_DURATION_MS;
    static int ACC_MODE_SPEED_RANGE_MS[2];

    static int BREAKING_DURATION_MS;
    static int BRAKING_INTERVAL_MS;
    static double BRAKING_ACCELERATION_MSS;
    static double CRITICAL_DISTANCE;
    static int BARRIER_WEIGHTS[3];
    static int ROADOBJECT_INTERVAL_RANGE_MS[2];

    static size_t SENSOR_SYSTEM_QUEUE_MAX_SIZE;
    static int SENSORS_COUNT;
};

#endif // CONSTANTS_H
