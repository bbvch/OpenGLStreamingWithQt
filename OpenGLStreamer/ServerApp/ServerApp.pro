include(../config.pri)

QT       += core websockets
QT       += core gui widgets


TARGET  = ServerApp

TEMPLATE = app

SOURCES += \
    src/echoserver.cpp \
    src/GlWidget.cpp \
    src/main.cpp

HEADERS += \
    src/echoserver.h \
    src/GlWidget.h


DISTFILES += \
    src/vertexShader.vsh \
    src/fragmentShader.fsh

RESOURCES += \
    src/Files.qrc






