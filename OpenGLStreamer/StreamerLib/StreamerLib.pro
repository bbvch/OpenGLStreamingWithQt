include(../config.pri)

QT       -= gui

TARGET = StreamerLib
TEMPLATE = lib
CONFIG += staticlib

SOURCES += \
    src/Serializer.cpp \
    src/Channel.cpp

HEADERS += \
    src/Archive.h \
    src/Serializer.h \
    src/Channel.h
unix {
    target.path = /usr/lib
    INSTALLS += target
}

INCLUDEPATH += include
