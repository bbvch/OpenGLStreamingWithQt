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
INCLUDEPATH += src/thirdparty/snappy \
               src/guids \
               src/thirdparty/md5 \
               src/thirdparty/libpng \
               src/thirdparty/zlib

SOURCES += \
    src/common/os_backtrace.cpp \
    src/common/os_posix.cpp \
    src/common/trace_file.cpp \
    src/common/trace_file_snappy.cpp \
    src/common/trace_model.cpp \
    src/common/trace_writer.cpp \
    src/common/highlight.cpp \
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
    src/guids/guids.cpp \
    src/image/image_bmp.cpp \
    src/image/image_md5.cpp \
    src/image/image_png.cpp \
    src/image/image_pnm.cpp \
    src/image/image_raw.cpp \
    src/thirdparty/md5/md5.c \
    src/thirdparty/libpng/png.c \
    src/thirdparty/libpng/pngerror.c \
    src/thirdparty/libpng/pngget.c \
    src/thirdparty/libpng/pngmem.c \
    src/thirdparty/libpng/pngpread.c \
    src/thirdparty/libpng/pngread.c \
    src/thirdparty/libpng/pngrio.c \
    src/thirdparty/libpng/pngrtran.c \
    src/thirdparty/libpng/pngrutil.c \
    src/thirdparty/libpng/pngset.c \
    src/thirdparty/libpng/pngtrans.c \
    src/thirdparty/libpng/pngwio.c \
    src/thirdparty/libpng/pngwrite.c \
    src/thirdparty/libpng/pngwtran.c \
    src/thirdparty/libpng/pngwutil.c \
    src/thirdparty/zlib/adler32.c \
    src/thirdparty/zlib/compress.c \
    src/thirdparty/zlib/crc32.c \
    src/thirdparty/zlib/deflate.c \
    src/thirdparty/zlib/gzclose.c \
    src/thirdparty/zlib/gzlib.c \
    src/thirdparty/zlib/gzread.c \
    src/thirdparty/zlib/gzwrite.c \
    src/thirdparty/zlib/infback.c \
    src/thirdparty/zlib/inffast.c \
    src/thirdparty/zlib/inflate.c \
    src/thirdparty/zlib/inftrees.c \
    src/thirdparty/zlib/trees.c \
    src/thirdparty/zlib/uncompr.c \
    src/thirdparty/zlib/zutil.c \
    src/common/trace_callset.cpp \
    src/common/trace_option.cpp \
    src/common/trace_fast_callset.cpp \
    src/common/os_crtdbg.cpp \
    src/common/trace_parser_flags.cpp \
    src/common/trace_file_read.cpp \
    src/common/trace_file_zlib.cpp \
    src/common/trace_parser_loop.cpp

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
    src/common/highlight.hpp \
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
    src/guids/guids.hpp \
    src/guids/guids_defs.hpp \
    src/guids/guids_entries.h \
    src/image/image.hpp \
    src/thirdparty/md5/md5.h \
    src/thirdparty/libpng/png.h \
    src/thirdparty/libpng/pngconf.h \
    src/thirdparty/libpng/pngdebug.h \
    src/thirdparty/libpng/pnginfo.h \
    src/thirdparty/libpng/pnglibconf.h \
    src/thirdparty/libpng/pngpriv.h \
    src/thirdparty/libpng/pngstruct.h \
    src/thirdparty/zlib/crc32.h \
    src/thirdparty/zlib/deflate.h \
    src/thirdparty/zlib/gzguts.h \
    src/thirdparty/zlib/inffast.h \
    src/thirdparty/zlib/inffixed.h \
    src/thirdparty/zlib/inflate.h \
    src/thirdparty/zlib/inftrees.h \
    src/thirdparty/zlib/trees.h \
    src/thirdparty/zlib/zconf.h \
    src/thirdparty/zlib/zlib.h \
    src/thirdparty/zlib/zutil.h \
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
