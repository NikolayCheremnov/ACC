#include <QtTest>

// add necessary includes here
#include <thread>


#include "../../../ACC/entities/driver.h"
#include "../../../ACC/entities/steeringwheel.h"
#include "../../../ACC/core/runnable.h"


class TestEntities : public QObject
{
    Q_OBJECT

public:
    TestEntities();
    ~TestEntities();

private slots:
    void test_driver();

};

TestEntities::TestEntities()
{

}

TestEntities::~TestEntities()
{

}

void TestEntities::test_driver()
{
    //Get std handles
        HANDLE hE = GetStdHandle(STD_ERROR_HANDLE);
        HANDLE hO = GetStdHandle(STD_OUTPUT_HANDLE);

        //Open streams
        QTextStream out(stdout);
        QTextStream err(stderr);

        //Set color
        //Standard output --> BLUE
        SetConsoleTextAttribute(hO, 0x09);
        //Error output --> RED
        // SetConsoleTextAttribute(hE, 0x0C);

    Driver* driver = new Driver();
    SteeringWheel* wheel = new SteeringWheel();

    std::thread t1(run, driver);
    std::thread t2(run, wheel);

    t1.join();
    t2.join();

    system("pause");
}


QTEST_APPLESS_MAIN(TestEntities)


#include "tst_testentities.moc"
