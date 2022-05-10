#ifndef BRAKE_H
#define BRAKE_H


#include "../core/runnable.h"


class Brake : public Runnable
{
public:
    Brake(std::string name="Brake");
    ~Brake() override;

    void run() override;
};

#endif // BRAKE_H
