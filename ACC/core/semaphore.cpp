#include "semaphore.h"


Semaphore::Semaphore(std::string name, int startState, int timeout) :
    timeout {timeout}
{
    name = "Global" + name;
    HSEM = OpenSemaphoreA(SEMAPHORE_ALL_ACCESS, true, name.c_str());
    int s = (startState > 0);
    if (!HSEM)
        HSEM = CreateSemaphoreA(NULL, s, 1, name.c_str());
}

Semaphore::~Semaphore()
{
    CloseHandle(HSEM);
}

DWORD Semaphore::P()
{
    return WaitForSingleObject(HSEM, timeout);
}

void Semaphore::V()
{
    ReleaseSemaphore(HSEM, 1, NULL);
}
