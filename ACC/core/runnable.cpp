#include "runnable.h"

Runnable::Runnable(std::ostream& out) : out {out}
{
    logSem = new Semaphore("logger", 1);
}

void Runnable::log(std::string srs, std::string msg)
{
    logSem->P();
    out << srs << "> " << msg << std::endl;
    logSem->V();
}
