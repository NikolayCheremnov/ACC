QT -= gui

CONFIG += c++11 console
CONFIG -= app_bundle

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        ../../core/channel.cpp \
        ../../core/runnable.cpp \
        ../../core/semaphore.cpp \
        ../../entities/engine.cpp \
        ../../structures/accparams.cpp \
        ../../structures/accstate.cpp \
        ../../structures/constants.cpp \
        ../../structures/sensordata.cpp \
        ../../utils/utils.cpp \
        main.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    ../../core/channel.h \
    ../../core/runnable.h \
    ../../core/semaphore.h \
    ../../entities/engine.h \
    ../../structures/accparams.h \
    ../../structures/accstate.h \
    ../../structures/constants.h \
    ../../structures/sensordata.h \
    ../../utils/utils.h
