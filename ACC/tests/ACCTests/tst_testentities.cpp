#include <QtTest>

// add necessary includes here
#include <thread>
#include <vector>

#include "../../../ACC/entities/driver.h"
#include "../../../ACC/entities/steeringwheel.h"
#include "../../../ACC/entities/automobile.h"
#include "../../../ACC/entities/speedometer.h"
#include "../../../ACC/entities/engine.h"
#include "../../../ACC/entities/brake.h"
#include "../../../ACC/entities/sensor.h"
#include "../../../ACC/entities/roadobject.h"
#include "../../../ACC/entities/sensorsystem.h"
#include "../../../ACC/core/runnable.h"
#include "../../../ACC/structures/constants.h"
#include "../../../ACC/utils/utils.h"


class TestEntities : public QObject
{
    Q_OBJECT

public:
    TestEntities();
    ~TestEntities();

private:
    std::vector<Runnable*> create_full_entity_list();
    std::vector<Runnable*> create_sensor_system_entity_list();

    void run_entities_in_threads(std::vector<Runnable*> entities);

private slots:
    // void test_simple_scenario();
    // void test_brake_scenario();
    void test_sensor_system();
};

TestEntities::TestEntities()
{

}

TestEntities::~TestEntities()
{
    
}

std::vector<Runnable *> TestEntities::create_full_entity_list()
{
    std::vector<Runnable*> entities;
    entities.push_back(new Automobile());
    entities.push_back(new Driver());
    entities.push_back(new SteeringWheel());
    entities.push_back(new Speedometer());
    entities.push_back(new Engine());
    entities.push_back(new Brake());
    entities.push_back(new Sensor());
    entities.push_back(new RoadObject());

    return entities;
}

std::vector<Runnable *> TestEntities::create_sensor_system_entity_list()
{
    std::vector<Runnable*> entities;
    entities.push_back(new Automobile());
    entities.push_back(new Driver());
    entities.push_back(new SteeringWheel());
    entities.push_back(new Speedometer());
    entities.push_back(new Engine());
    entities.push_back(new Brake());
    entities.push_back(new SensorSystem());

    return entities;
}

void TestEntities::run_entities_in_threads(std::vector<Runnable *> entities)
{
    printf("Starting system ...\n");
    std::vector<std::thread*> threads;
    for (auto entity : entities) {
        threads.push_back(new std::thread(run, entity));
    }

    printf("System is started. Waiting system stopping ...\n");

    for (auto thread : threads) {
        thread->join();
        delete thread;
    }

    printf("System is stopped.\n");
}

void TestEntities::test_sensor_system()
{
    // 2. Run system
    std::vector<Runnable*> entities = create_sensor_system_entity_list();
    run_entities_in_threads(entities);

    // 3. Clear objects
    for (auto entity : entities)
        delete entity;

    system("pause");
}

//void TestEntities::test_simple_scenario()
//{
//    // 1. Configure test paramteres
//    // Simple test - no critical barriers; driving period - 5 sec
//    Constants::BARRIER_WEIGHTS[0] = 0;
//    Constants::BARRIER_WEIGHTS[1] = 20;
//    Constants::BARRIER_WEIGHTS[2] = 100;
//    Constants::ACC_MODE_PREWORKING_DURATION_MS = 1000;
//    Constants::ACC_MODE_WORKING_DURATION_MS = 5000;

//    // 2. Run system
//    std::vector<Runnable*> entities = create_full_entity_list();
//    run_entities_in_threads(entities);

//    // 3. Clear objects
//    for (auto entity : entities)
//        delete entity;

//    system("pause");
//}

//void TestEntities::test_brake_scenario()
//{
//    // 1. Configure test paramteres
//    // Simple test - no critical barriers; driving period - 5 sec
//    Constants::BARRIER_WEIGHTS[0] = 30;
//    Constants::BARRIER_WEIGHTS[1] = 50;
//    Constants::BARRIER_WEIGHTS[2] = 100;
//    Constants::ACC_MODE_PREWORKING_DURATION_MS = 1000;
//    Constants::ACC_MODE_WORKING_DURATION_MS = 30000;

//    // 2. Run system
//    std::vector<Runnable*> entities = create_full_entity_list();
//    run_entities_in_threads(entities);

//    // 3. Clear objects
//    for (auto entity : entities)
//        delete entity;

//    system("pause");
//}


QTEST_APPLESS_MAIN(TestEntities)


#include "tst_testentities.moc"
