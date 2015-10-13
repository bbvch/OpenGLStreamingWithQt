include(../config.pri)

QT       += core websockets
QT       += core gui widgets

CONFIG += c++11


TARGET  = ServerApp

TEMPLATE = app

SOURCES += \
    src/echoserver.cpp \
    src/GlWidget.cpp \
    src/main.cpp \
    src/geometryengine.cpp

HEADERS += \
    src/echoserver.h \
    src/GlWidget.h \
    src/geometryengine.h


DISTFILES += \
    src/vertexShader.vsh \
    src/fragmentShader.fsh

RESOURCES += \
    src/shaders.qrc \
    src/textures.qrc






