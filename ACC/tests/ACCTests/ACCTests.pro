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
    ../../structures/accparams.cpp \
    ../../structures/constants.cpp \
    ../../../ACC/utils/utils.cpp \
    tst_testsemaphore.cpp \
    tst_testchannel.cpp \
    tst_testentities.cpp


HEADERS += ../../../ACC/core/semaphore.h \
    ../../../ACC/core/channel.h \
    ../../../ACC/core/runnable.h \
    ../../../ACC/entities/driver.h \
    ../../../ACC/entities/steeringwheel.h \
    ../../structures/accparams.h \
    ../../structures/constants.h \
    ../../utils/utils.h

