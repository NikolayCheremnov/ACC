#ifndef ACCSTATE_H
#define ACCSTATE_H


#include "accparams.h"


enum class ACCState {
    UNDEFINED,
    ON,
    OFF,
    ABORTED
};

struct ACCStateParams {
    ACCState state;
    ACCParams params;
};

#endif // ACCSTATE_H
