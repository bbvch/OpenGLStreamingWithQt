QT       += core websockets
QT       -= gui

TARGET  = ServerApp
CONFIG += console
CONFIG -= app_bundle
CONFIG += C++11

TEMPLATE = app

SOURCES += \
    src/echoserver.cpp \
    src/main.cpp

HEADERS += \
    src/echoserver.h

