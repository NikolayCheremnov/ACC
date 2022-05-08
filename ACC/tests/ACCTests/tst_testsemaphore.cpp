#include <QtTest>

// add necessary includes here
#include "../../../ACC/core/semaphore.h"
#include <thread>

// test thread methods

class TestSemaphore : public QObject
{
    Q_OBJECT

public:
    TestSemaphore();
    ~TestSemaphore();

private slots:
    void test_semaphore();

};

TestSemaphore::TestSemaphore()
{

}

TestSemaphore::~TestSemaphore()
{

}


void foo() {
    Semaphore* sem1 = new Semaphore("s", 0);

    for (int i = 0; i < 1; i++) {
    sem1->P();
    printf("foo started\n");

    printf("foo ended\n");
    sem1->V();
}
    delete sem1;
}

void bar() {
    Semaphore* sem1 = new Semaphore("s", 0);

     for (int i = 0; i < 1; i++) {
    sem1->P();
    sem1->V();
    printf("bar started\n");
    Sleep(1000);
    printf("bar ended\n");
     }

    delete sem1;

}

void TestSemaphore::test_semaphore()
{
    std::thread t1(foo);
    std::thread t2(bar);

    t1.join();
    t2.join();
}

// QTEST_APPLESS_MAIN(TestSemaphore)


#include "tst_testsemaphore.moc"
