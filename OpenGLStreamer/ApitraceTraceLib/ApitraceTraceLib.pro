#-------------------------------------------------
#
# Project created by QtCreator 2015-11-09T13:56:35
#
#-------------------------------------------------

QT       -= gui
QT       += core websockets

CONFIG += C++11

TARGET   = ApitraceTraceLib
TEMPLATE = lib
CONFIG   += shared

QMAKE_CXXFLAGS += -Wno-unused-variable -Wno-unused-parameter -Wno-sign-compare
QMAKE_LFLAGS += -Wl,-Bsymbolic -Wl,-Bsymbolic-functions -Wl,-z,defs

LIBS += -ldl

include($$PWD/../ApitraceCommonLib/ApitraceCommonLib.pri)

unix {
    target.path = /usr/lib
    INSTALLS += target
}

HEADERS += \
    src/trace/trace_writer_local.hpp \
    src/wrappers/config.hpp \
    src/wrappers/gltrace.hpp \
    src/server/openglserver.h \
    src/trace/trace_serializer.h

SOURCES += \
    src/trace/trace_writer_local.cpp \
    src/wrappers/config.cpp \
    src/wrappers/dlsym.cpp \
    src/wrappers/egltrace.cpp \
    src/wrappers/glcaps.cpp \
    src/wrappers/gltrace_state.cpp \
    src/server/openglserver.cpp \
    src/trace/trace_serializer.cpp

unix:!macx: LIBS += -L$$OUT_PWD/../ApitraceCommonLib/ -lApitraceCommonLib

INCLUDEPATH += src/trace
DEPENDPATH += $$PWD/../ApitraceCommonLib/src

unix:!macx: PRE_TARGETDEPS += $$OUT_PWD/../ApitraceCommonLib/libApitraceCommonLib.a
