#include <QCoreApplication>

#include "../../../ACC/entities/driver.h"

int main(int argc, char *argv[])
{
    //QCoreApplication a(argc, argv);

    printf("Driver application started\n");

    Driver* driver = new Driver();\
    driver->run();
    delete driver;

    printf("Driver application completed\n");
    system("pause");
    return 0;
    //return a.exec();
}
