#-------------------------------------------------
#
# Project created by QtCreator 2019-07-11T07:13:20
#
#-------------------------------------------------

QT       += core gui
QT       += serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = general-purpose-control
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11
QMAKE_CXXFLAGS += -std=c++11

DESTDIR = bin
UI_DIR = build/ui
MOC_DIR = build/moc
RCC_DIR = build/rcc
unix:OBJECTS_DIR = build/o/unix
win32:OBJECTS_DIR = build/o/win32
macx:OBJECTS_DIR = build/o/mac


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    src/devicemanager.h \
    src/devices/dummy.h \
    src/filehandler.h \
    src/scanparameterselection.h \
    src/serialconsole.h \
    src/devices/keithley_2000.h \
    src/devices/keithley_2410.h \
    src/mainwindow.h \
    src/measurementdevice.h \
    src/rs232.h \
    src/settings.h \
    src/measurementparameter.h \
    src/devices/scpidevice.h \
    src/devices/sourcetronic_st2819a.h

SOURCES += \
    src/devicemanager.cpp \
    src/devices/dummy.cpp \
    src/filehandler.cpp \
    src/scanparameterselection.cpp \
    src/serialconsole.cpp \
    src/devices/keithley_2000.cpp \
    src/devices/keithley_2410.cpp \
    src/main.cpp \
    src/mainwindow.cpp \
    src/measurementdevice.cpp \
    src/rs232.cpp \
    src/settings.cpp \
    src/devices/scpidevice.cpp \
    src/devices/sourcetronic_st2819a.cpp

FORMS += \
    src/mainwindow.ui \
    src/measurementdevice.ui \
    src/scanparameterselection.ui \
    src/serialconsole.ui \
    src/settings.ui

RESOURCES += \
    src/resources.qrc
