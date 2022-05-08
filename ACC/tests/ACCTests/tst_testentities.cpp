#include <QtTest>

// add necessary includes here

// test thread methods

class TestEntities : public QObject
{
    Q_OBJECT

public:
    TestEntities();
    ~TestEntities();

private slots:


};

TestEntities::TestEntities()
{

}

TestEntities::~TestEntities()
{

}


QTEST_APPLESS_MAIN(TestEntities)


#include "tst_testentities.moc"
