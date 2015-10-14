include(../config.pri)

QT       += core gui widgets websockets

TARGET  = ClientApp

INCLUDEPATH += $$PWD/../StreamerLib/src
DEPENDPATH += $$PWD/../StreamerLib

TEMPLATE = app

SOURCES += \
    src/main.cpp \
    src/OpenGLClient.cpp \
    src/GlWidget.cpp \
    src/GeometryEngine.cpp

HEADERS += \
    src/OpenGLClient.h \
    src/GlWidget.h \
    src/GeometryEngine.h


DISTFILES += \
    src/vertexShader.vsh \
    src/fragmentShader.fsh

RESOURCES += \
    src/shaders.qrc \
    src/textures.qrc
