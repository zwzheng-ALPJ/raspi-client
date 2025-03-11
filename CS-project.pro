QT       += core gui serialport concurrent bluetooth

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    bluetooth_handler.cpp \
    communi_protocol_handler.cpp \
    config.cpp \
    dht11.cpp \
    ecgppg.cpp \
    logger.cpp \
    main.cpp \
    mainwindow.cpp \
    mm_radar.cpp \
    serial_handler.cpp \
    settings.cpp \
    tcp_cilent.cpp

HEADERS += \
    bluetooth_handler.h \
    communi_protocol_handler.h \
    config.h \
    dht11.h \
    ecgppg.h \
    logger.h \
    mainwindow.h \
    mm_radar.h \
    serial_handler.h \
    settings.h \
    tcp_cilent.h

FORMS += \
    mainwindow.ui \
    settings.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

unix:!macx: LIBS += -lwiringPi
