#-------------------------------------------------
#
# Project created by QtCreator 2015-10-07T14:44:38
#
#-------------------------------------------------

QT       -= gui

TARGET = StreamerLib
TEMPLATE = lib
CONFIG += staticlib

SOURCES += \
    src/serializer.cpp

HEADERS += \
    src/serializer.h
unix {
    target.path = /usr/lib
    INSTALLS += target
}

INCLUDEPATH += include
