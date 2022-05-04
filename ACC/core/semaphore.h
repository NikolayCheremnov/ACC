#ifndef SEMAPHORE_H
#define SEMAPHORE_H

#include <Windows.h>
#include <string>

class Semaphore
{
private:
    HANDLE HSEM;

public:
    Semaphore(std::string name, int startState);
    ~Semaphore();

    // semaphore operations
    void P();
    void V();
};

#endif // SEMAPHORE_H
