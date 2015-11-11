#-------------------------------------------------
#
# Project created by QtCreator 2015-11-11T10:40:31
#
#-------------------------------------------------

QT       -= core gui

TARGET = ApitraceRetraceLib
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
    src/retrace/glstate.hpp \
    src/retrace/glstate_internal.hpp \
    src/retrace/glws.hpp \
    src/retrace/retrace.hpp \
    src/retrace/retrace_swizzle.hpp \
    src/retrace/scoped_allocator.hpp \
    src/retrace/state_writer.hpp \
    src/retrace/ws.hpp \
    src/retrace/glws_xlib.hpp \
    src/retrace/json.hpp

SOURCES += \
    src/retrace/glretrace_cgl.cpp \
    src/retrace/glretrace_egl.cpp \
    src/retrace/glretrace_gl.cpp \
    src/retrace/glretrace_glx.cpp \
    src/retrace/glretrace_main.cpp \
    src/retrace/glretrace_wgl.cpp \
    src/retrace/glretrace_ws.cpp \
    src/retrace/glstate.cpp \
    src/retrace/glws.cpp \
    src/retrace/retrace.cpp \
    src/retrace/retrace_swizzle.cpp \
    src/retrace/state_writer.cpp \
    src/retrace/retrace_main.cpp \
    src/retrace/ws.cpp \
    src/retrace/glstate_params.cpp \
    src/retrace/glstate_images.cpp \
    src/retrace/glstate_shaders.cpp \
    src/retrace/glws_egl_xlib.cpp \
    src/retrace/glws_xlib.cpp \
    src/retrace/state_writer_json.cpp \
    src/retrace/json.cpp \
    src/retrace/glstate_formats.cpp \
    src/retrace/state_writer_ubjson.cpp \
    src/retrace/retrace_stdc.cpp

unix:!macx: LIBS += -L$$OUT_PWD/../ApitraceCommonLib/ -lApitraceCommonLib

DEPENDPATH += $$PWD/../ApitraceCommonLib

unix:!macx: PRE_TARGETDEPS += $$OUT_PWD/../ApitraceCommonLib/libApitraceCommonLib.a
