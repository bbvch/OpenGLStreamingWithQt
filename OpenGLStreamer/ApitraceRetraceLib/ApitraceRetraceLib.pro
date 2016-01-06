#-------------------------------------------------
#
# Project created by QtCreator 2015-11-11T10:40:31
#
#-------------------------------------------------

QT       -= gui
QT       += core websockets

TARGET   = ApitraceRetraceLib
TEMPLATE = lib
CONFIG   += C++11
CONFIG   += shared

DEFINES += RETRACE

QMAKE_CXXFLAGS += -Wno-unused-variable -Wno-unused-parameter -Wno-sign-compare
QMAKE_LFLAGS += -Wl,-z,defs

include($$PWD/../ApitraceCommonLib/ApitraceCommonLib.pri)

LIBS += -ldl -lX11

unix {
    target.path = /usr/lib
    INSTALLS += target
}

HEADERS += \
    src/retrace/glretrace.hpp \
    src/retrace/glws.hpp \
    src/retrace/retrace.hpp \
    src/retrace/retrace_swizzle.hpp \
    src/retrace/scoped_allocator.hpp \
    src/retrace/glws_xlib.hpp \
    src/client/openglclient.h \
    src/retrace/retrace_main.hpp

SOURCES += \
    src/retrace/glretrace_egl.cpp \
    src/retrace/glretrace_gl.cpp \
    src/retrace/glretrace_glx.cpp \
    src/retrace/glretrace_main.cpp \
    src/retrace/glretrace_ws.cpp \
    src/retrace/glws.cpp \
    src/retrace/retrace.cpp \
    src/retrace/retrace_swizzle.cpp \
    src/retrace/retrace_main.cpp \
    src/retrace/glws_egl_xlib.cpp \
    src/retrace/glws_xlib.cpp \
    src/retrace/retrace_stdc.cpp \
    src/client/openglclient.cpp \
    src/retrace/glretrace_gles2.cpp

unix:!macx: LIBS += -L$$OUT_PWD/../ApitraceCommonLib/ -lApitraceCommonLib

INCLUDEPATH += src/retrace
DEPENDPATH += $$PWD/../ApitraceCommonLib

unix:!macx: PRE_TARGETDEPS += $$OUT_PWD/../ApitraceCommonLib/libApitraceCommonLib.a
