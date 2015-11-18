include(../config.pri)

QT       += core widgets websockets

TARGET  = ClientApp

TEMPLATE = app

SOURCES += \
    src/main.cpp

HEADERS +=

unix:!macx: LIBS += -L$$OUT_PWD/../ApitraceRetraceLib/ -lApitraceRetraceLib

INCLUDEPATH += $$PWD/../ApitraceRetraceLib/src/client
DEPENDPATH += $$PWD/../ApitraceRetraceLib/src
