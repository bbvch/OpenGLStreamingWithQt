TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
#CONFIG -= qt
CONFIG += c++11

#QT      += core
QT      -= gui
QT      += websockets

SOURCES += main.cpp \
    SerializerTests.cpp \
    ArchiveTests.cpp \
    HelpersTests.cpp

LIBS += /usr/lib/libgtest.a

include(../config.pri)
include(deployment.pri)
qtcAddDeployment()



unix:!macx: LIBS += -L$$OUT_PWD/../StreamerLib/ -lStreamerLib

INCLUDEPATH += $$PWD/../StreamerLib/src
DEPENDPATH += $$PWD/../StreamerLib/src

unix:!macx: LIBS += -L$$OUT_PWD/../ApitraceTraceLib/ -lApitraceTraceLib

INCLUDEPATH += $$PWD/../ApitraceTraceLib/src
DEPENDPATH += $$PWD/../ApitraceTraceLib/src
