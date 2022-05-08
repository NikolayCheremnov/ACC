#include <QtTest>

// add necessary includes here
#include "../../../ACC/core/channel.h"
#include <thread>
#include <string>
#include <iostream>

// test thread methods

class TestChannel : public QObject
{
    Q_OBJECT

public:
    TestChannel();
    ~TestChannel();

private slots:
    void test_channel();
    void test_channel_with_timeout();

private:
    struct Message {
        int code;

    };

    static void put_thread();
    static void get_thread();

    static void put_thread_with_timeout();
    static void get_thread_with_timeout();

};

TestChannel::TestChannel()
{

}

TestChannel::~TestChannel()
{

}



void TestChannel::test_channel()
{
//    setbuf(stdout, NULL);
//    std::thread t1(put_thread);
//    std::thread t2(get_thread);

//    t1.join();
//    t2.join();
}

void TestChannel::test_channel_with_timeout()
{
    setbuf(stdout, NULL);
    std::thread t1(put_thread_with_timeout);
    std::thread t2(get_thread_with_timeout);

    t1.join();
    t2.join();
}

void TestChannel::put_thread()
{
    Channel<Message>* ch = new Channel<Message>("testInAA", "testOutBB");

    Message msg{5};

    for (int i = 4; i >= -1; i--) {
        ch->put(msg);
        printf("put> %d\n", msg.code);
        Sleep(500);
        msg.code = i;
    }
    delete ch;
}

void TestChannel::get_thread()
{
    Channel<Message>* ch = new Channel<Message>("testInAA", "testOutBB");

    auto make_get = [=]() {
        bool is_timeout;
        Message msg = ch->get(is_timeout);
        printf("get> %d\n", msg.code);
        return msg.code;
    };

    while (make_get() != 100) {
        printf("get> wait...\n");
    }
    delete ch;
}

void TestChannel::put_thread_with_timeout()
{
    Channel<Message>* ch = new Channel<Message>("testInAA", "testOutBB");

    Message msg{3};

    for (int i = 3; i >= 0; i--) {
        msg.code = i;
        ch->put(msg);
        printf("put> %d\n", msg.code);
        Sleep(1000);

    }
    delete ch;
}

void TestChannel::get_thread_with_timeout()
{
    Channel<Message>* ch = new Channel<Message>("testInAA", "testOutBB", 200);

    auto make_get = [=]() {
        bool is_timeout;
        Message msg = ch->get(is_timeout);
        if (is_timeout)
            printf("get> timeout\n");
        else
            printf("get> %d\n", msg.code);
        return msg.code;
    };

    while (make_get() != 0) {
        //printf("get> wait...\n");
        //Sleep(500);
    }
    delete ch;
}

// QTEST_APPLESS_MAIN(TestChannel)

#include "tst_testchannel.moc"
