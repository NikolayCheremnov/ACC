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

};

#endif // CONSTANTS_H
