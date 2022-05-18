#include <QCoreApplication>

#include "../../../ACC/entities/automobile.h"

int main(int argc, char *argv[])
{
    //QCoreApplication a(argc, argv);

    printf("Automobile application started\n");

    Automobile* automobile = new Automobile();\
    automobile->run();
    delete automobile;

    printf("Automobile application completed\n");
    system("pause");
    return 0;
    //return a.exec();
}
