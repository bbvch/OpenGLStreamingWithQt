#-------------------------------------------------
#
# Project created by QtCreator 2015-11-09T13:56:35
#
#-------------------------------------------------

QT       -= core gui

CONFIG += C++11

TARGET = ApitraceLib
TEMPLATE = lib

QMAKE_CXXFLAGS += -Wno-unused-variable -Wno-unused-parameter -Wno-sign-compare
QMAKE_LFLAGS += -Wl,-Bsymbolic -Wl,-Bsymbolic-functions -Wl,-z,defs

LIBS += -ldl

DEFINES += APITRACELIB_LIBRARY\
           HAVE_X11 \
           HAVE_CXX11_THREADS

INCLUDEPATH += src/khronos/
INCLUDEPATH += src/snappy/


SOURCES += \
    src/config.cpp \
    src/dlsym.cpp \
    src/glcaps.cpp \
    src/gltrace_state.cpp \
    src/egltrace.cpp \
    src/trace_writer.cpp \
    src/trace_model.cpp \
    src/trace_writer_local.cpp \
    src/os_backtrace.cpp \
    src/trace_file.cpp \
    src/eglsize.cpp \
    src/glproc.cpp \
    src/glproc_egl.cpp \
    src/os_posix.cpp \
    src/glprofile.cpp \
    src/trace_file_snappy.cpp \
    src/snappy/snappy.cc \
    src/snappy/snappy-c.cc \
    src/snappy/snappy-sinksource.cc \
    src/snappy/snappy-stubs-internal.cc

HEADERS += \
    src/config.hpp \
    src/os.hpp \
    src/os_string.hpp \
    src/glimports.hpp \
    src/eglimports.hpp \
    src/dlopen.hpp \
    src/eglsize.hpp \
    src/glsize.hpp \
    src/glproc.hpp \
    src/trace_writer_local.hpp \
    src/os_process.hpp \
    src/os_thread.hpp \
    src/trace_writer.hpp \
    src/trace_model.hpp \
    src/glprofile.hpp \
    src/gltrace.hpp \
    src/os_backtrace.hpp \
    src/os_version.hpp \
    src/trace_file.hpp \
    src/trace_format.hpp \
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
    src/snappy/snappy.h \
    src/snappy/snappy-c.h \
    src/snappy/snappy-internal.h \
    src/snappy/snappy-sinksource.h \
    src/snappy/snappy-stubs-internal.h \
    src/snappy/snappy-stubs-public.h \
    src/snappy/snappy-stubs-public.h.in \
    src/snappy/snappy-test.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
