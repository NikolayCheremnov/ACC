#include <QCoreApplication>

#include "../../../ACC/entities/steeringwheel.h"

int main(int argc, char *argv[])
{
    //QCoreApplication a(argc, argv);

    printf("Steering wheel application started\n");

    SteeringWheel* steering_wheel = new SteeringWheel();\
    steering_wheel->run();
    delete steering_wheel;

    printf("Steering wheel application completed\n");
    system("pause");
    return 0;
    //return a.exec();
}
