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
