include(../config.pri)

QT       -= gui

TARGET = StreamerLib
TEMPLATE = lib
CONFIG += staticlib

SOURCES += \
    src/Serializer.cpp

HEADERS += \
    src/ChannelInterface.h \
    src/Archive.h \
    src/Serializer.h
unix {
    target.path = /usr/lib
    INSTALLS += target
}

INCLUDEPATH += include
