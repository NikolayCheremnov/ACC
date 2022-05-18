#include <QCoreApplication>

#include "../../../ACC/entities/speedometer.h"

int main(int argc, char *argv[])
{
    //QCoreApplication a(argc, argv);

    printf("Speedometer application started\n");

    Speedometer* speedometer = new Speedometer();\
    speedometer->run();
    delete speedometer;

    printf("Speedometer application completed\n");
    system("pause");
    return 0;
    //return a.exec();
}
