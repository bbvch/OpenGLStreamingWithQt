include(../config.pri)

QT       -= gui

TARGET = StreamerLib
TEMPLATE = lib
CONFIG += staticlib

SOURCES += \
    src/serializer.cpp \
    src/archive.cpp

HEADERS += \
    src/serializer.h \
    src/archive.h
unix {
    target.path = /usr/lib
    INSTALLS += target
}

INCLUDEPATH += include
