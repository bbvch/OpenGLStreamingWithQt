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

QMAKE_CXXFLAGS += -Wno-unused-variable -Wno-unused-parameter -Wno-sign-compare -Wno-unused-function

include(ApitraceCommonLib.pri)
INCLUDEPATH += src/thirdparty/snappy

SOURCES += \
    src/common/os_backtrace.cpp \
    src/common/os_posix.cpp \
    src/common/trace_file.cpp \
    src/common/trace_file_snappy.cpp \
    src/common/trace_model.cpp \
    src/common/trace_writer.cpp \
    src/common/trace_dump.cpp \
    src/common/trace_parser.cpp \
    src/common/trace_profiler.cpp \
    src/dispatch/glproc.cpp \
    src/dispatch/glproc_egl.cpp \
    src/helpers/eglsize.cpp \
    src/helpers/glprofile.cpp \
    src/thirdparty/snappy/snappy-c.cc \
    src/thirdparty/snappy/snappy-sinksource.cc \
    src/thirdparty/snappy/snappy-stubs-internal.cc \
    src/thirdparty/snappy/snappy.cc \
    src/common/trace_callset.cpp \
    src/common/trace_option.cpp \
    src/common/trace_fast_callset.cpp \
    src/common/os_crtdbg.cpp \
    src/common/trace_parser_flags.cpp \
    src/common/trace_file_read.cpp \
    src/common/trace_file_zlib.cpp \
    src/common/trace_parser_loop.cpp \
    src/common/trace_file_buffer.cpp

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
    src/common/os_memory.hpp \
    src/common/os_time.hpp \
    src/common/trace_api.hpp \
    src/common/trace_dump.hpp \
    src/common/trace_parser.hpp \
    src/common/trace_profiler.hpp \
    src/dispatch/dlopen.hpp \
    src/dispatch/eglimports.hpp \
    src/dispatch/glimports.hpp \
    src/dispatch/glproc.hpp \
    src/helpers/eglsize.hpp \
    src/helpers/glprofile.hpp \
    src/helpers/glsize.hpp \
    src/thirdparty/khronos/EGL/egl.h \
    src/thirdparty/khronos/EGL/eglext.h \
    src/thirdparty/khronos/EGL/eglplatform.h \
    src/thirdparty/khronos/GL/gl.h \
    src/thirdparty/khronos/GL/glext.h \
    src/thirdparty/khronos/GL/glx.h \
    src/thirdparty/khronos/GL/glxext.h \
    src/thirdparty/khronos/GL/wglext.h \
    src/thirdparty/khronos/GLES/gl.h \
    src/thirdparty/khronos/GLES/glext.h \
    src/thirdparty/khronos/GLES/glplatform.h \
    src/thirdparty/khronos/GLES2/gl2.h \
    src/thirdparty/khronos/GLES2/gl2ext.h \
    src/thirdparty/khronos/GLES2/gl2platform.h \
    src/thirdparty/khronos/KHR/khrplatform.h \
    src/thirdparty/snappy/snappy-c.h \
    src/thirdparty/snappy/snappy-internal.h \
    src/thirdparty/snappy/snappy-sinksource.h \
    src/thirdparty/snappy/snappy-stubs-internal.h \
    src/thirdparty/snappy/snappy-stubs-public.h \
    src/thirdparty/snappy/snappy-test.h \
    src/thirdparty/snappy/snappy.h \
    src/common/trace_dump.hpp \
    src/common/trace_parser.hpp \
    src/common/trace_profiler.hpp \
    src/common/trace_api.hpp \
    src/common/os_binary.hpp \
    src/common/os_crtdbg.hpp \
    src/common/trace_callset.hpp \
    src/common/trace_option.hpp \
    src/common/trace_fast_callset.hpp \
    src/common/trace_lookup.hpp \
    src/common/ubjson.hpp
unix {
    target.path = /usr/lib
    INSTALLS += target
}
