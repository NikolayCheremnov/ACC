#include "constants.h"


// Driver-wheel channel semaphores names
std::string Constants::ACC_PARAMS_CHNAME_FREE = "ACCParamsFree";
std::string Constants::ACC_PARAMS_CHNAME_EMPTY = "ACCParamsEmpty";


// Driver-wheel semaphores names
std::string Constants::ACC_TURN_ON_SEM = "ACCTurnOn";
std::string Constants::ACC_TURN_OFF_SEM = "ACCTurnOff";


// Wheel-automobile channel names and timeout
std::string Constants::ACC_STATE_CHNAME_FREE = "ACCStateFree";
std::string Constants::ACC_STATE_CHNAME_EMPTY = "ACCStateEmpty";
int Constants::ACC_STATE_CHTIMEOUT_MS = 100;


// Automobile-engine channel names
std::string Constants::AUTOMOBILE_ENGINE_CHNAME_FREE = "AutomobileEngineFree";
std::string Constants::AUTOMOBILE_ENGINE_CHNAME_EMPTY = "AutomobileEngineEmpty";


// Automobile-speedometer channel names and timeout
std::string Constants::AUTOMOBILE_SPEEDOMETER_CHNAME_FREE = "AutomobileSpeedometerFree";
std::string Constants::AUTOMOBILE_SPEEDOMETER_CHNAME_EMPTY = "AutomobileSpeedometerEmpty";
int Constants::AUTOMOBILE_SPEEDOEMETER_CHTIMEOUT_MS = 100;


// Automobile-sensor channel names and timeout
std::string Constants::AUTOMOBILE_SENSOR_CHNAME_FREE = "AutomobileSensorFree";
std::string Constants::AUTOMOBILE_SENSOR_CHNAME_EMPTY = "AutomobileSensorEmpty";
int Constants::AUTOMOBILE_SENSOR_CHTIMEOUT_MS = 100;


// Automobile-brake channel names
std::string Constants::AUTOMOBILE_BRAKE_CHNAME_FREE = "AutomobileBrakeFree";
std::string Constants::AUTOMOBILE_BRAKE_CHNAME_EMPTY = "AutomobileBrakeEmpty";
std::string Constants::AUTOMOBILE_BRAKE_SEMNAME = "AutomobileBrakeSemaphore";


// Speedometer-engine channel names
std::string Constants::SPEEDOMETER_ENGINE_CHNAME_FREE = "SpeedometerEngineFree";
std::string Constants::SPEEDOMETER_ENGINE_CHNAME_EMPTY = "SpeedometerEngineEmpty";
int Constants::SPEEDOMETER_ENGINE_CHTIMEOUT_MS = 100;


// Speedometer-brake channel names and timeout
std::string Constants::SPEEDOMETER_BRAKE_CHNAME_FREE = "SpedometerBrakeFree";
std::string Constants::SPEEDOMETER_BRAKE_CHNAME_EMPTY = "SpeedometerBrakeEmpty";
int Constants::SPEEDOMETER_BRAKE_CHTIMEOUT_MS = 100;

// Sensor-object channel names
std::string Constants::SENSOR_OBJECT_CHNAME_FREE = "SensorObjectFree";
std::string Constants::SENSOR_OBJECT_CHNAME_EMPTY = "SensorObjectEmpty";

// Termination semaphores names and timeout
std::string Constants::DRIVER_TERMINATION_SEMNAME = "DriverTerminationSem";
std::string Constants::STEERINGWHEEL_TERMINATION_SEMNAME = "SteeringwheelTerminationSem";
std::string Constants::ROADOBJECT_TERMINATION_SEMNAME = "RoadobjectTerminationSem";
std::string Constants::SENSOR_TERMINATION_SEMNAME = "SensorTerminationSem";
std::string Constants::BRAKE_TERMINATION_SEMNAME = "BrakeTerminationSem";
std::string Constants::ENGINE_TERMINATION_SEMNAME = "EngineTerminationSem";
std::string Constants::SPEEDOMETER_TERMINATION_SEMNAME = "SpeedometerTerminationSem";
int Constants::TERMINATION_SEMTIMEOUT_MS = 100;

// plug constants
int Constants::ACC_MODE_PREWORKING_DURATION_MS = 3000;
int Constants::ACC_MODE_WORKING_DURATION_MS = 10000;
int Constants::ACC_MODE_SPEED_RANGE_MS[2]{50, 110};

int Constants::BRAKING_INTERVAL_MS = 1000;
double Constants::BRAKING_ACCELERATION = 36;
double Constants::CRITICAL_DISTANCE = 50;
int Constants::BARRIER_WEIGHTS[3]{0, 50, 100};
int Constants::ROADOBJECT_INTERVAL_RANGE_MS[2]{2 * 1000, 5 * 1000};
