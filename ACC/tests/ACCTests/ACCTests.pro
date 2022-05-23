QT += testlib
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES +=  ../../../ACC/core/semaphore.cpp \
    ../../../ACC/core/channel.cpp \
    ../../../ACC/core/runnable.cpp \
    ../../../ACC/entities/driver.cpp \
    ../../../ACC/entities/steeringwheel.cpp \
    ../../../ACC/entities/automobile.cpp \
    ../../../ACC/entities/speedometer.cpp \
    ../../../ACC/entities/engine.cpp \
    ../../../ACC/entities/brake.cpp \
    ../../../ACC/entities/sensor.cpp \
    ../../../ACC/entities/roadobject.cpp \
    ../../../ACC/entities/sensorsystem.cpp \
    ../../structures/accparams.cpp \
    ../../structures/constants.cpp \
    ../../structures/sensordata.cpp \
    ../../../ACC/utils/utils.cpp \
    tst_testsemaphore.cpp \
    tst_testchannel.cpp \
    tst_testentities.cpp


HEADERS += ../../../ACC/core/semaphore.h \
    ../../../ACC/core/channel.h \
    ../../../ACC/core/runnable.h \
    ../../../ACC/entities/driver.h \
    ../../../ACC/entities/steeringwheel.h \
    ../../../ACC/entities/automobile.h \
    ../../../ACC/entities/speedometer.h \
    ../../../ACC/entities/engine.h \
    ../../../ACC/entities/brake.h \
    ../../../ACC/entities/sensor.h \
    ../../../ACC/entities/roadobject.h \
    ../../../ACC/entities/sensorsystem.h \
    ../../structures/accparams.h \
    ../../structures/constants.h \
    ../../structures/sensordata.h \
    ../../utils/utils.h

