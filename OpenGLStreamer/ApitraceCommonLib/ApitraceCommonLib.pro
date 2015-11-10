#-------------------------------------------------
#
# Project created by QtCreator 2015-11-10T15:10:50
#
#-------------------------------------------------

QT       -= core gui

TARGET = ApitraceCommonLib
TEMPLATE = lib
CONFIG += staticlib

SOURCES +=

HEADERS +=
unix {
    target.path = /usr/lib
    INSTALLS += target
}
