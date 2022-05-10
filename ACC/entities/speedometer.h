#ifndef SPEEDOMETER_H
#define SPEEDOMETER_H


#include "../core/runnable.h"


class Speedometer : public Runnable
{
public:
    Speedometer(std::string name="Speedometer");
    ~Speedometer() override;

    void run() override;

};

#endif // SPEEDOMETER_H
