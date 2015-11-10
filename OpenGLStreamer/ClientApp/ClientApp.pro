include(../config.pri)

QT       += core gui widgets websockets

TARGET  = ClientApp

TEMPLATE = app

SOURCES += \
    src/main.cpp \
    src/GlWidget.cpp

HEADERS += \
    src/GlWidget.h


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
