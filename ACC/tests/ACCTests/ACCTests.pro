QT += testlib
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES +=  tst_testsemaphore.cpp \
    ../../../ACC/core/semaphore.cpp \
    ../../../ACC/core/channel.cpp \
    tst_testchannel.cpp \
    tst_testentities.cpp


HEADERS += ../../../ACC/core/semaphore.h \
    ../../../ACC/core/channel.h

