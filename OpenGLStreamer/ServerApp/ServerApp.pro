include(../config.pri)

QT       += core gui widgets websockets

TARGET  = ServerApp

TEMPLATE = app

SOURCES += \
    src/GlWidget.cpp \
    src/main.cpp \
    src/GeometryEngine.cpp

HEADERS += \
    src/GlWidget.h \
    src/GeometryEngine.h

DISTFILES += \
    src/vertexShader.vsh \
    src/fragmentShader.fsh

RESOURCES += \
    src/shaders.qrc \
    src/textures.qrc

unix:!macx: LIBS += -L$$OUT_PWD/../ApitraceTraceLib/ -lApitraceTraceLib

INCLUDEPATH += $$PWD/../ApitraceTraceLib/src/server
DEPENDPATH += $$PWD/../ApitraceTraceLib/src
