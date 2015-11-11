include(../config.pri)
include($$PWD/../ApitraceCommonLib/ApitraceCommonLib.pri)

QT += gui widgets websockets

TARGET   = StreamerLib
TEMPLATE = lib
CONFIG   += shared

SOURCES += \
    src/OpenGLServer.cpp \
    src/OpenGLClient.cpp \
    src/Serializer.cpp \
    src/Helpers.cpp

HEADERS += \
    src/Archive.h \
    src/Serializer.h \
    src/OpenGLProxy.h \
    src/OpenGLServer.h \
    src/OpenGLClient.h \
    src/Events.h \
    src/Helpers.h \
    src/Singleton.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

unix:!macx: LIBS += -L$$OUT_PWD/../ApitraceTraceLib/ -lApitraceTraceLib

INCLUDEPATH += $$PWD/../ApitraceTraceLib/src/trace
DEPENDPATH += $$PWD/../ApitraceTraceLib/src
