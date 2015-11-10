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

unix:!macx: LIBS += -L$$OUT_PWD/../StreamerLib/ -lStreamerLib

INCLUDEPATH += $$PWD/../StreamerLib/src
DEPENDPATH += $$PWD/../StreamerLib/src

unix:!macx: LIBS += -L$$OUT_PWD/../ApitraceLib/ -lApitraceLib

INCLUDEPATH += $$PWD/../ApitraceLib/src
DEPENDPATH += $$PWD/../ApitraceLib/src
