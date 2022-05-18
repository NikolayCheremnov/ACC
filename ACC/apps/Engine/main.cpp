#include <QCoreApplication>

#include "../../../ACC/entities/engine.h"

int main(int argc, char *argv[])
{
    //QCoreApplication a(argc, argv);

    printf("Engine application started\n");

    Engine* engine = new Engine();\
    engine->run();
    delete engine;

    printf("Engine application completed\n");
    system("pause");
    return 0;
    //return a.exec();
}
