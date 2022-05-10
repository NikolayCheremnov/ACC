#ifndef CHANNEL_H
#define CHANNEL_H

#include <Windows.h>
#include <string>

#include "semaphore.h"

template<class T>
class Channel
{
protected:
    Semaphore* free;
    Semaphore* empty;
    HANDLE fileHMem;
    void* buffer;
    int timeout;

public:
    Channel(std::string freeSemName, std::string emptySemName, int timeout=INFINITE);
    ~Channel();

    // put/get
    void put(T data) {
        free->P();
        CopyMemory((PVOID)buffer, &data, sizeof(T));
        empty->V();
    }

    T get(bool& is_timeout) {
        T data;
        DWORD dwWaitResult = empty->P();

        if (dwWaitResult == WAIT_OBJECT_0) {
            is_timeout = false;
            CopyMemory(&data, (PVOID)buffer, sizeof(T));
            free->V();
        } else {
            is_timeout = true;
        }
        return data;
    }
};

template<class T>
inline Channel<T>::Channel(std::string freeSemName, std::string emptySemName, int timeout) :
    timeout {timeout}
{
    // 1. init semaphores
    free = new Semaphore(freeSemName, 1, timeout);
    empty = new Semaphore(emptySemName, 0, timeout);

    // 2. init mapping file
    fileHMem = OpenFileMappingA(FILE_MAP_ALL_ACCESS, false, (emptySemName + "_" + freeSemName).c_str());
    if (!fileHMem) {
        fileHMem = CreateFileMappingA((HANDLE)0xFFFFFFFF, NULL, PAGE_READWRITE, 0, 4096,
                                      (emptySemName + "_" + freeSemName).c_str());
    }

    // 3. make mapping
    if (fileHMem) {
        buffer = MapViewOfFile(fileHMem, FILE_MAP_ALL_ACCESS, 0, 0, 4096);
    }
    else {
        throw "error: FILE_MAP";
    }
}

template<class T>
inline Channel<T>::~Channel()
{
    delete free;
    delete empty;
    // delete buffer;
}

#endif // CHANNEL_H
