include(../config.pri)

QT += gui widgets websockets

TARGET = StreamerLib
TEMPLATE = lib
CONFIG += staticlib

SOURCES += \
    src/Serializer.cpp \
    src/OpenGLServer.cpp \
    src/OpenGLProxy.cpp

HEADERS += \
    src/Archive.h \
    src/Serializer.h \
    src/OpenGLProxy.h \
    src/OpenGLServer.h
unix {
    target.path = /usr/lib
    INSTALLS += target
}

INCLUDEPATH += include
