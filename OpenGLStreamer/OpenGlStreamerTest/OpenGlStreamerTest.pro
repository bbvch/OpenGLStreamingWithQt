#-------------------------------------------------
#
# Project created by QtCreator 2015-10-08T10:43:45
#
#-------------------------------------------------
include(../config.pri)

QT       += testlib

QT       -= gui

TARGET = tst_serializertest
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += tst_serializertest.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../StreamerLib/release/ -lStreamerLib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../StreamerLib/debug/ -lStreamerLib
else:unix: LIBS += -L$$OUT_PWD/../StreamerLib/ -lStreamerLib

#INCLUDEPATH += $$PWD/../StreamerLib
INCLUDEPATH += $$PWD/../StreamerLib/src
DEPENDPATH += $$PWD/../StreamerLib

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../StreamerLib/release/libStreamerLib.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../StreamerLib/debug/libStreamerLib.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../StreamerLib/release/StreamerLib.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../StreamerLib/debug/StreamerLib.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../StreamerLib/libStreamerLib.a
