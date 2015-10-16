include(../config.pri)

QT += gui widgets websockets

TARGET = StreamerLib
TEMPLATE = lib
CONFIG += staticlib

SOURCES += \
    src/Serializer.cpp \
    src/OpenGLServer.cpp \
    src/OpenGLClient.cpp \
    src/OpenGLProxy.cpp

HEADERS += \
    src/Archive.h \
    src/Serializer.h \
    src/OpenGLProxy.h \
    src/OpenGLServer.h \
    src/OpenGLClient.h \

unix {
    target.path = /usr/lib
    INSTALLS += target
}

INCLUDEPATH += include
