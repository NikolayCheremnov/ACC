#ifndef ENGINE_H
#define ENGINE_H


#include "../core/runnable.h"
#include "../core/channel.h"

#include "../structures/accstate.h"
#include "../structures/constants.h"


class Engine : public Runnable
{
private:
    // Automobile - engine channel
    Channel<ACCState>* automobile_ch;

public:
    Engine(std::string name="Engine");
    ~Engine() override;

    void run() override;
};

#endif // ENGINE_H
