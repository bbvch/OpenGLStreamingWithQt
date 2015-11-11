#-------------------------------------------------
#
# Project created by QtCreator 2015-11-10T15:10:50
#
#-------------------------------------------------
QT       -= core gui

TARGET = ApitraceCommonLib
TEMPLATE = lib
CONFIG += staticlib

CONFIG += C++11

QMAKE_CXXFLAGS += -Wno-unused-variable -Wno-unused-parameter -Wno-sign-compare

include(ApitraceCommonLib.pri)
INCLUDEPATH += src/snappy

SOURCES += \
    src/common/os_backtrace.cpp \
    src/common/os_posix.cpp \
    src/common/trace_file.cpp \
    src/common/trace_file_snappy.cpp \
    src/common/trace_model.cpp \
    src/common/trace_writer.cpp \
    src/dispatch/glproc.cpp \
    src/dispatch/glproc_egl.cpp \
    src/helpers/eglsize.cpp \
    src/helpers/glprofile.cpp \
    src/snappy/snappy-c.cc \
    src/snappy/snappy-sinksource.cc \
    src/snappy/snappy-stubs-internal.cc \
    src/snappy/snappy.cc

HEADERS += \
    src/common/os.hpp \
    src/common/os_backtrace.hpp \
    src/common/os_process.hpp \
    src/common/os_string.hpp \
    src/common/os_thread.hpp \
    src/common/os_version.hpp \
    src/common/trace_file.hpp \
    src/common/trace_format.hpp \
    src/common/trace_model.hpp \
    src/common/trace_writer.hpp \
    src/dispatch/dlopen.hpp \
    src/dispatch/eglimports.hpp \
    src/dispatch/glimports.hpp \
    src/dispatch/glproc.hpp \
    src/helpers/eglsize.hpp \
    src/helpers/glprofile.hpp \
    src/helpers/glsize.hpp \
    src/khronos/EGL/egl.h \
    src/khronos/EGL/eglext.h \
    src/khronos/EGL/eglplatform.h \
    src/khronos/GL/gl.h \
    src/khronos/GL/glext.h \
    src/khronos/GL/glx.h \
    src/khronos/GL/glxext.h \
    src/khronos/GL/wglext.h \
    src/khronos/GLES/gl.h \
    src/khronos/GLES/glext.h \
    src/khronos/GLES/glplatform.h \
    src/khronos/GLES2/gl2.h \
    src/khronos/GLES2/gl2ext.h \
    src/khronos/GLES2/gl2platform.h \
    src/khronos/KHR/khrplatform.h \
    src/snappy/snappy-c.h \
    src/snappy/snappy-internal.h \
    src/snappy/snappy-sinksource.h \
    src/snappy/snappy-stubs-internal.h \
    src/snappy/snappy-stubs-public.h \
    src/snappy/snappy-test.h \
    src/snappy/snappy.h
unix {
    target.path = /usr/lib
    INSTALLS += target
}
