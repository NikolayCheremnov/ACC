#ifndef TESTSEMAPHORE2_H
#define TESTSEMAPHORE2_H


#include <QtTest>

// add necessary includes here


// test thread methods

class TestSemaphore2 : public QObject
{
    Q_OBJECT

public:
    TestSemaphore2();
    ~TestSemaphore2();

private slots:
    void test_semaphore();

};

#endif // TESTSEMAPHORE2_H
