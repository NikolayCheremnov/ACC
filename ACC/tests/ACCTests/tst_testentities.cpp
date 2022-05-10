#include <QtTest>

// add necessary includes here
#include <thread>


#include "../../../ACC/entities/driver.h"
#include "../../../ACC/entities/steeringwheel.h"
#include "../../../ACC/entities/automobile.h"
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
    Automobile* automobile = new Automobile();
    Driver* driver = new Driver();
    SteeringWheel* wheel = new SteeringWheel();


    std::thread t0(run, automobile);
    std::thread t1(run, driver);
    std::thread t2(run, wheel);

    t0.join();
    t1.join();
    t2.join();

    system("pause");
}


QTEST_APPLESS_MAIN(TestEntities)


#include "tst_testentities.moc"
