#include "runnable.h"

Runnable::Runnable(std::string name, std::ostream& out) : objectName{name}, out {out}
{
    logSem = new Semaphore("logger", 1);
    color = nextColor;
    nextColor = (nextColor + 1) % 16;

    // random generator
    std::random_device rd;
    generator = new std::mt19937(rd());
    //srand(time(0));

}

Runnable::~Runnable()
{
    delete generator;
}

void Runnable::log(std::string srs, std::string msg)
{
    // lock out
    logSem->P();

    // store old console text color
    short old_text_color;
    bool res = get_console_text_color(old_text_color);
    if (!res)
        old_text_color = 8;

    // set console text color
    SetConsoleTextAttribute(hO, color);

    // output
    out << srs << "> " << msg << std::endl;

    // set old console text color
    SetConsoleTextAttribute(hO, old_text_color);

    // unlock out
    logSem->V();
}

std::string &Runnable::name()
{
    return objectName;
}

int Runnable::rand_in_range(int min, int max)
{
    return (*generator)() % (max + 1 - min) + min;
}

void run(Runnable *entity)
{
    entity->run();
}

int Runnable::nextColor = 2;
