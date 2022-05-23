#include <QCoreApplication>

#include "entities/sensorsystem.h"

int main(int argc, char *argv[])
{

    //QCoreApplication a(argc, argv);
    SensorSystem s;
    s.run();

    //return a.exec();
}
