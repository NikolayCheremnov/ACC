#ifndef RUNNABLE_H
#define RUNNABLE_H

#include <iostream>

#include "semaphore.h"

class Runnable
{
private:
    Semaphore* logSem;
    std::ostream& out;

public:
    Runnable(std::ostream& out = std::cout);

    virtual void run() = 0;

    void log(std::string srs, std::string msg);
};

#endif // RUNNABLE_H
