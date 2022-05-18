#include <QCoreApplication>

#include "../../../ACC/entities/sensor.h"

int main(int argc, char *argv[])
{
    //QCoreApplication a(argc, argv);

    printf("Sensor application started\n");

    Sensor* sensor = new Sensor();\
    sensor->run();
    delete sensor;

    printf("Sensor application completed\n");
    system("pause");
    return 0;
    //return a.exec();
}
