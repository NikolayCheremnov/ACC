#include "automobile.h"

Automobile::Automobile(std::string name) :
    Runnable(name)
{
    // 1. wheel channels
    ACC_state_ch = new Channel<ACCStateParams>(Constants::ACC_STATE_CHNAME_FREE, Constants::ACC_STATE_CHNAME_EMPTY);
    ACC_state_timeout_ch = new Channel<ACCStateParams>(Constants::ACC_STATE_CHNAME_FREE, Constants::ACC_STATE_CHNAME_EMPTY,
                                         Constants::ACC_STATE_CHTIMEOUT_MS);

    // 2. engine channel
    engine_ch = new Channel<ACCStateParams>(Constants::AUTOMOBILE_ENGINE_CHNAME_FREE, Constants::AUTOMOBILE_ENGINE_CHNAME_EMPTY);

    // 3. speedometer channel
    speedometer_timeout_ch = new Channel<ACCStateParams>(Constants::AUTOMOBILE_SPEEDOMETER_CHNAME_FREE,
                                                         Constants::AUTOMOBILE_SPEEDOMETER_CHNAME_EMPTY,
                                                         Constants::AUTOMOBILE_SPEEDOEMETER_CHTIMEOUT_MS);


    log(this->name(), "Object created");
}

Automobile::~Automobile()
{
    delete ACC_state_ch;
    delete ACC_state_timeout_ch;
    delete engine_ch;

    log(name(), "Object destroyed");
}

void Automobile::run()
{
    // 1. running
    log(name(), "Object is running");

    // 2. waiting going to ACC
    bool is_timeout;
    log(name(), "Object is waiting to receive ACC control");
    ACCStateParams acc_state = ACC_state_ch->get(is_timeout);

    // 3. ACC control - main loop
    log(name(), "Driving has been switched to ACC. Automobile cycle started.");
    bool stop;
    while (!stop) {
        // 1. send info to engine
        engine_ch->put(acc_state);
        log(name(), "Speed adjusting sended to engine. Speed = " + std::to_string(acc_state.params.speed));

        // 2. receive data from speedometer
        log(name(), "Reading speedometer data");
        bool is_speedometer_timeout;
        ACCStateParams speedometerInfo = speedometer_timeout_ch->get(is_speedometer_timeout);
        if (is_speedometer_timeout)
            log(name(), "No speedometer data");
        else
            log(name(), "Speedometer data received. Speed = " + std::to_string(speedometerInfo.params.speed));

        // 3. receive data from sensor



    }

}
