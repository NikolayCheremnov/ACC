#include "utils.h"


int rand_in_range(int min, int max)
{
    std::random_device rd;     // only used once to initialise (seed) engine
    std::mt19937 rng(rd());    // random-number engine used (Mersenne-Twister in this case)
    std::uniform_int_distribution<int> uni(min,max); // guaranteed unbiased

    return uni(rng);
}


bool get_console_text_color(short &ret){
        CONSOLE_SCREEN_BUFFER_INFO info;
        if (!GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info))
            return false;
        ret = info.wAttributes;
        return true;
}
