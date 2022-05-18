#include <QCoreApplication>

#include "../../../ACC/entities/roadobject.h"

int main(int argc, char *argv[])
{
    //QCoreApplication a(argc, argv);

    printf("Road object application started\n");

    RoadObject* road_object = new RoadObject();\
    road_object->run();
    delete road_object;

    printf("Road object application completed\n");
    system("pause");
    return 0;
    //return a.exec();
}
