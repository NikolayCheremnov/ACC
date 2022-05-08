#ifndef SEMAPHORE_H
#define SEMAPHORE_H

#include <Windows.h>
#include <string>

class Semaphore
{
private:
    HANDLE HSEM;
    int timeout;

public:
    Semaphore(std::string name, int startState, int timeout=INFINITE);
    ~Semaphore();

    // semaphore operations
    DWORD P();
    void V();
};

#endif // SEMAPHORE_H
