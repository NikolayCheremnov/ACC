#ifndef RUNNABLE_H
#define RUNNABLE_H

#include <iostream>

#include "semaphore.h"
#include "../utils/utils.h"

class Runnable
{
private:
    // log color params (may be deprecated)
    static int nextColor;
    int color;
    const HANDLE hO = GetStdHandle(STD_OUTPUT_HANDLE);

private:
    std::string objectName;
    Semaphore* logSem;
    std::ostream& out;

public:
    Runnable(std::string objectName, std::ostream& out = std::cout);
    virtual ~Runnable() {}

    virtual void run() = 0;

    void log(std::string srs, std::string msg);
    std::string& name();
    friend void run(Runnable* entity);
};

void run(Runnable* entity);

#endif // RUNNABLE_H
