#include <QCoreApplication>

#include "../../../ACC/entities/brake.h"

int main(int argc, char *argv[])
{
    //QCoreApplication a(argc, argv);

    printf("Brake application started\n");

    Brake* brake = new Brake();\
    brake->run();
    delete brake;

    printf("Brake application completed\n");
    system("pause");
    return 0;
    //return a.exec();
}
