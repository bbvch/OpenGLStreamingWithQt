include(../config.pri)

QT       += core websockets
QT       -= gui

TARGET  = ServerApp
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += \
    src/echoserver.cpp \
    src/main.cpp

HEADERS += \
    src/echoserver.h

