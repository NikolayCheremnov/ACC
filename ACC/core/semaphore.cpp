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

DWORD Semaphore::P(bool &is_timeout)
{
    DWORD dwWaitResult = P();

    if (dwWaitResult == WAIT_OBJECT_0) {
        is_timeout = false;
    } else {
        is_timeout = true;
    }
    return dwWaitResult;
}

void Semaphore::V()
{
    ReleaseSemaphore(HSEM, 1, NULL);
}
