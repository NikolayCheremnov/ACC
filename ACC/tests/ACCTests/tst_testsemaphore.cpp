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


void foo(Semaphore* sem ) {
    sem->P();
    printf("foo started\n");
    Sleep(5000);
    printf("foo ended\n");
    sem->V();
}

void bar(Semaphore* sem ) {
    sem->P();
    printf("bar started\n");
    printf("bar ended\n");
    sem->V();
}
void TestSemaphore::test_semaphore()
{
    Semaphore* sem = new Semaphore("test", 1);

    //Semaphore* sem = new Semaphore("test", 1);
    std::thread t1(foo, sem);
    std::thread t2(bar, sem);

    t1.join();
    t2.join();
}

QTEST_APPLESS_MAIN(TestSemaphore)

#include "tst_testsemaphore.moc"
