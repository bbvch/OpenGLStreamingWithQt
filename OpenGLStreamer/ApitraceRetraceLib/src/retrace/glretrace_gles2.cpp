#include <string.h>

#include "glproc.hpp"
#include "glretrace.hpp"
//#include "glstate.hpp"


static bool _pipelineHasBeenBound = false;


static GLint
_getActiveProgram(void);

static void
_validateActiveProgram(trace::Call &call);


#include "os_time.hpp"
#include "trace_parser.hpp"
#include "retrace.hpp"
#include "retrace_swizzle.hpp"

static retrace::map<GLuint> _texture_map;
static retrace::map<GLuint> _buffer_map;
static retrace::map<GLuint> _program_map;
static retrace::map<GLuint> _shader_map;
static std::map<GLhandleARB, retrace::map<GLint> > _location_map;
static retrace::map<GLuint> _renderbuffer_map;
static retrace::map<GLuint> _framebuffer_map;
static retrace::map<GLhandleARB> _handleARB_map;

static void retrace_glCullFace(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    GLenum mode;
    mode = static_cast<GLenum>((call.arg(0)).toSInt());

    glretrace::Context *currentContext = glretrace::getCurrentContext();
    if (!currentContext) {
        if (retrace::debug) {
            retrace::warning(call) << "no current context\n";
        }
#ifndef _WIN32
        return;
#endif
    }
    if (currentContext && !currentContext->insideList && !currentContext->insideBeginEnd && retrace::profiling) {
        glretrace::beginProfile(call, false);
    }
    glCullFace(mode);
    if (currentContext && !currentContext->insideList && !currentContext->insideBeginEnd && retrace::profiling) {
        glretrace::endProfile(call, false);
    }
    if (retrace::debug && currentContext && !currentContext->insideBeginEnd) {
        glretrace::checkGlError(call);
    }
}

static void retrace_glFrontFace(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    GLenum mode;
    mode = static_cast<GLenum>((call.arg(0)).toSInt());

    glretrace::Context *currentContext = glretrace::getCurrentContext();
    if (!currentContext) {
        if (retrace::debug) {
            retrace::warning(call) << "no current context\n";
        }
#ifndef _WIN32
        return;
#endif
    }
    if (currentContext && !currentContext->insideList && !currentContext->insideBeginEnd && retrace::profiling) {
        glretrace::beginProfile(call, false);
    }
    glFrontFace(mode);
    if (currentContext && !currentContext->insideList && !currentContext->insideBeginEnd && retrace::profiling) {
        glretrace::endProfile(call, false);
    }
    if (retrace::debug && currentContext && !currentContext->insideBeginEnd) {
        glretrace::checkGlError(call);
    }
}

static void retrace_glHint(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    GLenum target;
    target = static_cast<GLenum>((call.arg(0)).toSInt());

    GLenum mode;
    mode = static_cast<GLenum>((call.arg(1)).toSInt());

    glretrace::Context *currentContext = glretrace::getCurrentContext();
    if (!currentContext) {
        if (retrace::debug) {
            retrace::warning(call) << "no current context\n";
        }
#ifndef _WIN32
        return;
#endif
    }
    if (currentContext && !currentContext->insideList && !currentContext->insideBeginEnd && retrace::profiling) {
        glretrace::beginProfile(call, false);
    }
    glHint(target, mode);
    if (currentContext && !currentContext->insideList && !currentContext->insideBeginEnd && retrace::profiling) {
        glretrace::endProfile(call, false);
    }
    if (retrace::debug && currentContext && !currentContext->insideBeginEnd) {
        glretrace::checkGlError(call);
    }
}

static void retrace_glLineWidth(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    GLfloat width;
    width = (call.arg(0)).toFloat();

    glretrace::Context *currentContext = glretrace::getCurrentContext();
    if (!currentContext) {
        if (retrace::debug) {
            retrace::warning(call) << "no current context\n";
        }
#ifndef _WIN32
        return;
#endif
    }
    if (currentContext && !currentContext->insideList && !currentContext->insideBeginEnd && retrace::profiling) {
        glretrace::beginProfile(call, false);
    }
    glLineWidth(width);
    if (currentContext && !currentContext->insideList && !currentContext->insideBeginEnd && retrace::profiling) {
        glretrace::endProfile(call, false);
    }
    if (retrace::debug && currentContext && !currentContext->insideBeginEnd) {
        glretrace::checkGlError(call);
    }
}

static void retrace_glScissor(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    GLint x;
    x = (call.arg(0)).toSInt();

    GLint y;
    y = (call.arg(1)).toSInt();

    GLsizei width;
    width = (call.arg(2)).toSInt();

    GLsizei height;
    height = (call.arg(3)).toSInt();

    glretrace::Context *currentContext = glretrace::getCurrentContext();
    if (!currentContext) {
        if (retrace::debug) {
            retrace::warning(call) << "no current context\n";
        }
#ifndef _WIN32
        return;
#endif
    }
    if (currentContext && !currentContext->insideList && !currentContext->insideBeginEnd && retrace::profiling) {
        glretrace::beginProfile(call, false);
    }
    glScissor(x, y, width, height);
    if (currentContext && !currentContext->insideList && !currentContext->insideBeginEnd && retrace::profiling) {
        glretrace::endProfile(call, false);
    }
    if (retrace::debug && currentContext && !currentContext->insideBeginEnd) {
        glretrace::checkGlError(call);
    }
}

static void retrace_glTexParameterf(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    GLenum target;
    target = static_cast<GLenum>((call.arg(0)).toSInt());

    GLenum pname;
    pname = static_cast<GLenum>((call.arg(1)).toSInt());

    GLfloat param;
    param = (call.arg(2)).toFloat();

    glretrace::Context *currentContext = glretrace::getCurrentContext();
    if (!currentContext) {
        if (retrace::debug) {
            retrace::warning(call) << "no current context\n";
        }
#ifndef _WIN32
        return;
#endif
    }
    if (currentContext && !currentContext->insideList && !currentContext->insideBeginEnd && retrace::profiling) {
        glretrace::beginProfile(call, false);
    }
    glTexParameterf(target, pname, param);
    if (currentContext && !currentContext->insideList && !currentContext->insideBeginEnd && retrace::profiling) {
        glretrace::endProfile(call, false);
    }
    if (retrace::debug && currentContext && !currentContext->insideBeginEnd) {
        glretrace::checkGlError(call);
    }
}

static void retrace_glTexParameterfv(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    GLenum target;
    target = static_cast<GLenum>((call.arg(0)).toSInt());

    GLenum pname;
    pname = static_cast<GLenum>((call.arg(1)).toSInt());

    GLfloat * params;
    params = _allocator.allocArray<GLfloat>(&call.arg(2));
    const trace::Array *_a_GLfloat5_0 = (call.arg(2)).toArray();
    if (_a_GLfloat5_0) {
        for (size_t _jGLfloat5 = 0; _jGLfloat5 < _a_GLfloat5_0->values.size(); ++_jGLfloat5) {
    params[_jGLfloat5] = (*_a_GLfloat5_0->values[_jGLfloat5]).toFloat();
        }
    }

    glretrace::Context *currentContext = glretrace::getCurrentContext();
    if (!currentContext) {
        if (retrace::debug) {
            retrace::warning(call) << "no current context\n";
        }
#ifndef _WIN32
        return;
#endif
    }
    if (currentContext && !currentContext->insideList && !currentContext->insideBeginEnd && retrace::profiling) {
        glretrace::beginProfile(call, false);
    }
    glTexParameterfv(target, pname, params);
    if (currentContext && !currentContext->insideList && !currentContext->insideBeginEnd && retrace::profiling) {
        glretrace::endProfile(call, false);
    }
    if (retrace::debug && currentContext && !currentContext->insideBeginEnd) {
        glretrace::checkGlError(call);
    }
}

static void retrace_glTexParameteri(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    GLenum target;
    target = static_cast<GLenum>((call.arg(0)).toSInt());

    GLenum pname;
    pname = static_cast<GLenum>((call.arg(1)).toSInt());

    GLint param;
    param = (call.arg(2)).toSInt();

    glretrace::Context *currentContext = glretrace::getCurrentContext();
    if (!currentContext) {
        if (retrace::debug) {
            retrace::warning(call) << "no current context\n";
        }
#ifndef _WIN32
        return;
#endif
    }
    if (currentContext && !currentContext->insideList && !currentContext->insideBeginEnd && retrace::profiling) {
        glretrace::beginProfile(call, false);
    }
    glTexParameteri(target, pname, param);
    if (currentContext && !currentContext->insideList && !currentContext->insideBeginEnd && retrace::profiling) {
        glretrace::endProfile(call, false);
    }
    if (retrace::debug && currentContext && !currentContext->insideBeginEnd) {
        glretrace::checkGlError(call);
    }
}

static void retrace_glTexParameteriv(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    GLenum target;
    target = static_cast<GLenum>((call.arg(0)).toSInt());

    GLenum pname;
    pname = static_cast<GLenum>((call.arg(1)).toSInt());

    GLint * params;
    params = _allocator.allocArray<GLint>(&call.arg(2));
    const trace::Array *_a_GLint14_0 = (call.arg(2)).toArray();
    if (_a_GLint14_0) {
        for (size_t _jGLint14 = 0; _jGLint14 < _a_GLint14_0->values.size(); ++_jGLint14) {
    params[_jGLint14] = (*_a_GLint14_0->values[_jGLint14]).toSInt();
        }
    }

    glretrace::Context *currentContext = glretrace::getCurrentContext();
    if (!currentContext) {
        if (retrace::debug) {
            retrace::warning(call) << "no current context\n";
        }
#ifndef _WIN32
        return;
#endif
    }
    if (currentContext && !currentContext->insideList && !currentContext->insideBeginEnd && retrace::profiling) {
        glretrace::beginProfile(call, false);
    }
    glTexParameteriv(target, pname, params);
    if (currentContext && !currentContext->insideList && !currentContext->insideBeginEnd && retrace::profiling) {
        glretrace::endProfile(call, false);
    }
    if (retrace::debug && currentContext && !currentContext->insideBeginEnd) {
        glretrace::checkGlError(call);
    }
}

static void retrace_glTexImage2D(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    GLenum target;
    target = static_cast<GLenum>((call.arg(0)).toSInt());

    GLint level;
    level = (call.arg(1)).toSInt();

    GLint internalformat;
    internalformat = static_cast<GLenum>((call.arg(2)).toSInt());

    GLsizei width;
    width = (call.arg(3)).toSInt();

    GLsizei height;
    height = (call.arg(4)).toSInt();

    GLint border;
    border = (call.arg(5)).toSInt();

    GLenum format;
    format = static_cast<GLenum>((call.arg(6)).toSInt());

    GLenum type;
    type = static_cast<GLenum>((call.arg(7)).toSInt());

    GLvoid * pixels;
    pixels = static_cast<GLvoid *>((call.arg(8)).toPointer());

    glretrace::Context *currentContext = glretrace::getCurrentContext();
    if (!currentContext) {
        if (retrace::debug) {
            retrace::warning(call) << "no current context\n";
        }
#ifndef _WIN32
        return;
#endif
    }
    if (currentContext && !currentContext->insideList && !currentContext->insideBeginEnd && retrace::profiling) {
        glretrace::beginProfile(call, false);
    }
    glTexImage2D(target, level, internalformat, width, height, border, format, type, pixels);
    if (currentContext && !currentContext->insideList && !currentContext->insideBeginEnd && retrace::profiling) {
        glretrace::endProfile(call, false);
    }
    if (retrace::debug && currentContext && !currentContext->insideBeginEnd) {
        glretrace::checkGlError(call);
    }
}

static void retrace_glClear(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    GLbitfield mask;
    mask = (call.arg(0)).toUInt();

    glretrace::Context *currentContext = glretrace::getCurrentContext();
    if (!currentContext) {
        if (retrace::debug) {
            retrace::warning(call) << "no current context\n";
        }
#ifndef _WIN32
        return;
#endif
    }
    if (currentContext && !currentContext->insideList && !currentContext->insideBeginEnd && retrace::profiling) {
        glretrace::beginProfile(call, true);
    }
    glClear(mask);
    if (currentContext && !currentContext->insideList && !currentContext->insideBeginEnd && retrace::profiling) {
        glretrace::endProfile(call, true);
    }
    if (retrace::debug && currentContext && !currentContext->insideBeginEnd) {
        glretrace::checkGlError(call);
    }
    assert(call.flags & trace::CALL_FLAG_RENDER);
}

static void retrace_glClearColor(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    GLfloat red;
    red = (call.arg(0)).toFloat();

    GLfloat green;
    green = (call.arg(1)).toFloat();

    GLfloat blue;
    blue = (call.arg(2)).toFloat();

    GLfloat alpha;
    alpha = (call.arg(3)).toFloat();

    glretrace::Context *currentContext = glretrace::getCurrentContext();
    if (!currentContext) {
        if (retrace::debug) {
            retrace::warning(call) << "no current context\n";
        }
#ifndef _WIN32
        return;
#endif
    }
    if (currentContext && !currentContext->insideList && !currentContext->insideBeginEnd && retrace::profiling) {
        glretrace::beginProfile(call, false);
    }
    glClearColor(red, green, blue, alpha);
    if (currentContext && !currentContext->insideList && !currentContext->insideBeginEnd && retrace::profiling) {
        glretrace::endProfile(call, false);
    }
    if (retrace::debug && currentContext && !currentContext->insideBeginEnd) {
        glretrace::checkGlError(call);
    }
}

static void retrace_glClearStencil(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    GLint s;
    s = (call.arg(0)).toSInt();

    glretrace::Context *currentContext = glretrace::getCurrentContext();
    if (!currentContext) {
        if (retrace::debug) {
            retrace::warning(call) << "no current context\n";
        }
#ifndef _WIN32
        return;
#endif
    }
    if (currentContext && !currentContext->insideList && !currentContext->insideBeginEnd && retrace::profiling) {
        glretrace::beginProfile(call, false);
    }
    glClearStencil(s);
    if (currentContext && !currentContext->insideList && !currentContext->insideBeginEnd && retrace::profiling) {
        glretrace::endProfile(call, false);
    }
    if (retrace::debug && currentContext && !currentContext->insideBeginEnd) {
        glretrace::checkGlError(call);
    }
}

static void retrace_glStencilMask(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    GLuint mask;
    mask = (call.arg(0)).toUInt();

    glretrace::Context *currentContext = glretrace::getCurrentContext();
    if (!currentContext) {
        if (retrace::debug) {
            retrace::warning(call) << "no current context\n";
        }
#ifndef _WIN32
        return;
#endif
    }
    if (currentContext && !currentContext->insideList && !currentContext->insideBeginEnd && retrace::profiling) {
        glretrace::beginProfile(call, false);
    }
    glStencilMask(mask);
    if (currentContext && !currentContext->insideList && !currentContext->insideBeginEnd && retrace::profiling) {
        glretrace::endProfile(call, false);
    }
    if (retrace::debug && currentContext && !currentContext->insideBeginEnd) {
        glretrace::checkGlError(call);
    }
}

static void retrace_glColorMask(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    GLboolean red;
    red = static_cast<GLboolean>((call.arg(0)).toSInt());

    GLboolean green;
    green = static_cast<GLboolean>((call.arg(1)).toSInt());

    GLboolean blue;
    blue = static_cast<GLboolean>((call.arg(2)).toSInt());

    GLboolean alpha;
    alpha = static_cast<GLboolean>((call.arg(3)).toSInt());

    glretrace::Context *currentContext = glretrace::getCurrentContext();
    if (!currentContext) {
        if (retrace::debug) {
            retrace::warning(call) << "no current context\n";
        }
#ifndef _WIN32
        return;
#endif
    }
    if (currentContext && !currentContext->insideList && !currentContext->insideBeginEnd && retrace::profiling) {
        glretrace::beginProfile(call, false);
    }
    glColorMask(red, green, blue, alpha);
    if (currentContext && !currentContext->insideList && !currentContext->insideBeginEnd && retrace::profiling) {
        glretrace::endProfile(call, false);
    }
    if (retrace::debug && currentContext && !currentContext->insideBeginEnd) {
        glretrace::checkGlError(call);
    }
}

static void retrace_glDepthMask(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    GLboolean flag;
    flag = static_cast<GLboolean>((call.arg(0)).toSInt());

    glretrace::Context *currentContext = glretrace::getCurrentContext();
    if (!currentContext) {
        if (retrace::debug) {
            retrace::warning(call) << "no current context\n";
        }
#ifndef _WIN32
        return;
#endif
    }
    if (currentContext && !currentContext->insideList && !currentContext->insideBeginEnd && retrace::profiling) {
        glretrace::beginProfile(call, false);
    }
    glDepthMask(flag);
    if (currentContext && !currentContext->insideList && !currentContext->insideBeginEnd && retrace::profiling) {
        glretrace::endProfile(call, false);
    }
    if (retrace::debug && currentContext && !currentContext->insideBeginEnd) {
        glretrace::checkGlError(call);
    }
}

static void retrace_glDisable(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    GLenum cap;
    cap = static_cast<GLenum>((call.arg(0)).toSInt());

    glretrace::Context *currentContext = glretrace::getCurrentContext();
    if (!currentContext) {
        if (retrace::debug) {
            retrace::warning(call) << "no current context\n";
        }
#ifndef _WIN32
        return;
#endif
    }
    if (cap == GL_DEBUG_OUTPUT_SYNCHRONOUS_ARB) return;
    if (currentContext && !currentContext->insideList && !currentContext->insideBeginEnd && retrace::profiling) {
        glretrace::beginProfile(call, false);
    }
    glDisable(cap);
    if (currentContext && !currentContext->insideList && !currentContext->insideBeginEnd && retrace::profiling) {
        glretrace::endProfile(call, false);
    }
    if (retrace::debug && currentContext && !currentContext->insideBeginEnd) {
        glretrace::checkGlError(call);
    }
}

static void retrace_glEnable(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    GLenum cap;
    cap = static_cast<GLenum>((call.arg(0)).toSInt());

    glretrace::Context *currentContext = glretrace::getCurrentContext();
    if (!currentContext) {
        if (retrace::debug) {
            retrace::warning(call) << "no current context\n";
        }
#ifndef _WIN32
        return;
#endif
    }
    if (cap == GL_DEBUG_OUTPUT_SYNCHRONOUS_ARB) return;
    if (currentContext && !currentContext->insideList && !currentContext->insideBeginEnd && retrace::profiling) {
        glretrace::beginProfile(call, false);
    }
    glEnable(cap);
    if (currentContext && !currentContext->insideList && !currentContext->insideBeginEnd && retrace::profiling) {
        glretrace::endProfile(call, false);
    }
    if (retrace::debug && currentContext && !currentContext->insideBeginEnd) {
        glretrace::checkGlError(call);
    }
}

static void retrace_glFinish(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    glretrace::Context *currentContext = glretrace::getCurrentContext();
    if (!currentContext) {
        if (retrace::debug) {
            retrace::warning(call) << "no current context\n";
        }
#ifndef _WIN32
        return;
#endif
    }
    if (currentContext && !currentContext->insideList && !currentContext->insideBeginEnd && retrace::profiling) {
        glretrace::beginProfile(call, false);
    }
    glFinish();
    if (currentContext && !currentContext->insideList && !currentContext->insideBeginEnd && retrace::profiling) {
        glretrace::endProfile(call, false);
    }
    if (retrace::debug && currentContext && !currentContext->insideBeginEnd) {
        glretrace::checkGlError(call);
    }
    if (!retrace::doubleBuffer) {
        glretrace::frame_complete(call);
    }
}

static void retrace_glFlush(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    glretrace::Context *currentContext = glretrace::getCurrentContext();
    if (!currentContext) {
        if (retrace::debug) {
            retrace::warning(call) << "no current context\n";
        }
#ifndef _WIN32
        return;
#endif
    }
    if (currentContext && !currentContext->insideList && !currentContext->insideBeginEnd && retrace::profiling) {
        glretrace::beginProfile(call, false);
    }
    glFlush();
    if (currentContext && !currentContext->insideList && !currentContext->insideBeginEnd && retrace::profiling) {
        glretrace::endProfile(call, false);
    }
    if (retrace::debug && currentContext && !currentContext->insideBeginEnd) {
        glretrace::checkGlError(call);
    }
    if (!retrace::doubleBuffer) {
        glretrace::frame_complete(call);
    }
}

static void retrace_glBlendFunc(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    GLenum sfactor;
    sfactor = static_cast<GLenum>((call.arg(0)).toSInt());

    GLenum dfactor;
    dfactor = static_cast<GLenum>((call.arg(1)).toSInt());

    glretrace::Context *currentContext = glretrace::getCurrentContext();
    if (!currentContext) {
        if (retrace::debug) {
            retrace::warning(call) << "no current context\n";
        }
#ifndef _WIN32
        return;
#endif
    }
    if (currentContext && !currentContext->insideList && !currentContext->insideBeginEnd && retrace::profiling) {
        glretrace::beginProfile(call, false);
    }
    glBlendFunc(sfactor, dfactor);
    if (currentContext && !currentContext->insideList && !currentContext->insideBeginEnd && retrace::profiling) {
        glretrace::endProfile(call, false);
    }
    if (retrace::debug && currentContext && !currentContext->insideBeginEnd) {
        glretrace::checkGlError(call);
    }
}

static void retrace_glStencilFunc(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    GLenum func;
    func = static_cast<GLenum>((call.arg(0)).toSInt());

    GLint ref;
    ref = (call.arg(1)).toSInt();

    GLuint mask;
    mask = (call.arg(2)).toUInt();

    glretrace::Context *currentContext = glretrace::getCurrentContext();
    if (!currentContext) {
        if (retrace::debug) {
            retrace::warning(call) << "no current context\n";
        }
#ifndef _WIN32
        return;
#endif
    }
    if (currentContext && !currentContext->insideList && !currentContext->insideBeginEnd && retrace::profiling) {
        glretrace::beginProfile(call, false);
    }
    glStencilFunc(func, ref, mask);
    if (currentContext && !currentContext->insideList && !currentContext->insideBeginEnd && retrace::profiling) {
        glretrace::endProfile(call, false);
    }
    if (retrace::debug && currentContext && !currentContext->insideBeginEnd) {
        glretrace::checkGlError(call);
    }
}

static void retrace_glStencilOp(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    GLenum fail;
    fail = static_cast<GLenum>((call.arg(0)).toSInt());

    GLenum zfail;
    zfail = static_cast<GLenum>((call.arg(1)).toSInt());

    GLenum zpass;
    zpass = static_cast<GLenum>((call.arg(2)).toSInt());

    glretrace::Context *currentContext = glretrace::getCurrentContext();
    if (!currentContext) {
        if (retrace::debug) {
            retrace::warning(call) << "no current context\n";
        }
#ifndef _WIN32
        return;
#endif
    }
    if (currentContext && !currentContext->insideList && !currentContext->insideBeginEnd && retrace::profiling) {
        glretrace::beginProfile(call, false);
    }
    glStencilOp(fail, zfail, zpass);
    if (currentContext && !currentContext->insideList && !currentContext->insideBeginEnd && retrace::profiling) {
        glretrace::endProfile(call, false);
    }
    if (retrace::debug && currentContext && !currentContext->insideBeginEnd) {
        glretrace::checkGlError(call);
    }
}

static void retrace_glDepthFunc(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    GLenum func;
    func = static_cast<GLenum>((call.arg(0)).toSInt());

    glretrace::Context *currentContext = glretrace::getCurrentContext();
    if (!currentContext) {
        if (retrace::debug) {
            retrace::warning(call) << "no current context\n";
        }
#ifndef _WIN32
        return;
#endif
    }
    if (currentContext && !currentContext->insideList && !currentContext->insideBeginEnd && retrace::profiling) {
        glretrace::beginProfile(call, false);
    }
    glDepthFunc(func);
    if (currentContext && !currentContext->insideList && !currentContext->insideBeginEnd && retrace::profiling) {
        glretrace::endProfile(call, false);
    }
    if (retrace::debug && currentContext && !currentContext->insideBeginEnd) {
        glretrace::checkGlError(call);
    }
}

static void retrace_glPixelStorei(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    GLenum pname;
    pname = static_cast<GLenum>((call.arg(0)).toSInt());

    GLint param;
    param = (call.arg(1)).toSInt();

    glretrace::Context *currentContext = glretrace::getCurrentContext();
    if (!currentContext) {
        if (retrace::debug) {
            retrace::warning(call) << "no current context\n";
        }
#ifndef _WIN32
        return;
#endif
    }
    if (currentContext && !currentContext->insideList && !currentContext->insideBeginEnd && retrace::profiling) {
        glretrace::beginProfile(call, false);
    }
    glPixelStorei(pname, param);
    if (currentContext && !currentContext->insideList && !currentContext->insideBeginEnd && retrace::profiling) {
        glretrace::endProfile(call, false);
    }
    if (retrace::debug && currentContext && !currentContext->insideBeginEnd) {
        glretrace::checkGlError(call);
    }
}

static void retrace_glReadPixels(trace::Call &call) {
    GLint _pack_buffer = 0;
    glGetIntegerv(GL_PIXEL_PACK_BUFFER_BINDING, &_pack_buffer);
    if (!_pack_buffer) {
        return;
    }
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    GLint x;
    x = (call.arg(0)).toSInt();

    GLint y;
    y = (call.arg(1)).toSInt();

    GLsizei width;
    width = (call.arg(2)).toSInt();

    GLsizei height;
    height = (call.arg(3)).toSInt();

    GLenum format;
    format = static_cast<GLenum>((call.arg(4)).toSInt());

    GLenum type;
    type = static_cast<GLenum>((call.arg(5)).toSInt());

    GLvoid * pixels;
    pixels = static_cast<GLvoid *>((call.arg(6)).toPointer());

    glretrace::Context *currentContext = glretrace::getCurrentContext();
    if (!currentContext) {
        if (retrace::debug) {
            retrace::warning(call) << "no current context\n";
        }
#ifndef _WIN32
        return;
#endif
    }
    if (currentContext && !currentContext->insideList && !currentContext->insideBeginEnd && retrace::profiling) {
        glretrace::beginProfile(call, false);
    }
    glReadPixels(x, y, width, height, format, type, pixels);
    if (currentContext && !currentContext->insideList && !currentContext->insideBeginEnd && retrace::profiling) {
        glretrace::endProfile(call, false);
    }
    if (retrace::debug && currentContext && !currentContext->insideBeginEnd) {
        glretrace::checkGlError(call);
    }
}

static void retrace_glViewport(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    GLint x;
    x = (call.arg(0)).toSInt();

    GLint y;
    y = (call.arg(1)).toSInt();

    GLsizei width;
    width = (call.arg(2)).toSInt();

    GLsizei height;
    height = (call.arg(3)).toSInt();

    glretrace::updateDrawable(x + width, y + height);
    glretrace::Context *currentContext = glretrace::getCurrentContext();
    if (!currentContext) {
        if (retrace::debug) {
            retrace::warning(call) << "no current context\n";
        }
#ifndef _WIN32
        return;
#endif
    }
    if (currentContext && !currentContext->insideList && !currentContext->insideBeginEnd && retrace::profiling) {
        glretrace::beginProfile(call, false);
    }
    glViewport(x, y, width, height);
    if (currentContext && !currentContext->insideList && !currentContext->insideBeginEnd && retrace::profiling) {
        glretrace::endProfile(call, false);
    }
    if (retrace::debug && currentContext && !currentContext->insideBeginEnd) {
        glretrace::checkGlError(call);
    }
}

static void retrace_glDrawArrays(trace::Call &call) {
    if (retrace::parser->getVersion() < 1) {
        GLint _array_buffer = 0;
        glGetIntegerv(GL_ARRAY_BUFFER_BINDING, &_array_buffer);
        if (!_array_buffer) {
    if (retrace::verbosity >= 0) {
        retrace::unsupported(call);
    }
    return;
        }
    }
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    GLenum mode;
    mode = static_cast<GLenum>((call.arg(0)).toSInt());

    GLint first;
    first = (call.arg(1)).toSInt();

    GLsizei count;
    count = (call.arg(2)).toSInt();

    glretrace::Context *currentContext = glretrace::getCurrentContext();
    if (!currentContext) {
        if (retrace::debug) {
            retrace::warning(call) << "no current context\n";
        }
#ifndef _WIN32
        return;
#endif
    }
    if (retrace::debug) {
        _validateActiveProgram(call);
    }
    if (currentContext && !currentContext->insideList && !currentContext->insideBeginEnd && retrace::profiling) {
        glretrace::beginProfile(call, true);
    }
    glDrawArrays(mode, first, count);
    if (currentContext && !currentContext->insideList && !currentContext->insideBeginEnd && retrace::profiling) {
        glretrace::endProfile(call, true);
    }
    if (retrace::debug && currentContext && !currentContext->insideBeginEnd) {
        glretrace::checkGlError(call);
    }
    assert(call.flags & trace::CALL_FLAG_RENDER);
}

static void retrace_glDrawElements(trace::Call &call) {
    if (retrace::parser->getVersion() < 1) {
        GLint _element_array_buffer = 0;
        glGetIntegerv(GL_ELEMENT_ARRAY_BUFFER_BINDING, &_element_array_buffer);
        if (!_element_array_buffer) {
    if (retrace::verbosity >= 0) {
        retrace::unsupported(call);
    }
    return;
        }
    }
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    GLenum mode;
    mode = static_cast<GLenum>((call.arg(0)).toSInt());

    GLsizei count;
    count = (call.arg(1)).toSInt();

    GLenum type;
    type = static_cast<GLenum>((call.arg(2)).toSInt());

    const GLvoid * indices;
    indices = static_cast<const GLvoid *>((call.arg(3)).toPointer());

    glretrace::Context *currentContext = glretrace::getCurrentContext();
    if (!currentContext) {
        if (retrace::debug) {
            retrace::warning(call) << "no current context\n";
        }
#ifndef _WIN32
        return;
#endif
    }
    if (retrace::debug) {
        _validateActiveProgram(call);
    }
    if (currentContext && !currentContext->insideList && !currentContext->insideBeginEnd && retrace::profiling) {
        glretrace::beginProfile(call, true);
    }
    glDrawElements(mode, count, type, indices);
    if (currentContext && !currentContext->insideList && !currentContext->insideBeginEnd && retrace::profiling) {
        glretrace::endProfile(call, true);
    }
    if (retrace::debug && currentContext && !currentContext->insideBeginEnd) {
        glretrace::checkGlError(call);
    }
    assert(call.flags & trace::CALL_FLAG_RENDER);
}

static void retrace_glPolygonOffset(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    GLfloat factor;
    factor = (call.arg(0)).toFloat();

    GLfloat units;
    units = (call.arg(1)).toFloat();

    glretrace::Context *currentContext = glretrace::getCurrentContext();
    if (!currentContext) {
        if (retrace::debug) {
            retrace::warning(call) << "no current context\n";
        }
#ifndef _WIN32
        return;
#endif
    }
    if (currentContext && !currentContext->insideList && !currentContext->insideBeginEnd && retrace::profiling) {
        glretrace::beginProfile(call, false);
    }
    glPolygonOffset(factor, units);
    if (currentContext && !currentContext->insideList && !currentContext->insideBeginEnd && retrace::profiling) {
        glretrace::endProfile(call, false);
    }
    if (retrace::debug && currentContext && !currentContext->insideBeginEnd) {
        glretrace::checkGlError(call);
    }
}

static void retrace_glCopyTexImage2D(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    GLenum target;
    target = static_cast<GLenum>((call.arg(0)).toSInt());

    GLint level;
    level = (call.arg(1)).toSInt();

    GLenum internalformat;
    internalformat = static_cast<GLenum>((call.arg(2)).toSInt());

    GLint x;
    x = (call.arg(3)).toSInt();

    GLint y;
    y = (call.arg(4)).toSInt();

    GLsizei width;
    width = (call.arg(5)).toSInt();

    GLsizei height;
    height = (call.arg(6)).toSInt();

    GLint border;
    border = (call.arg(7)).toSInt();

    glretrace::Context *currentContext = glretrace::getCurrentContext();
    if (!currentContext) {
        if (retrace::debug) {
            retrace::warning(call) << "no current context\n";
        }
#ifndef _WIN32
        return;
#endif
    }
    if (currentContext && !currentContext->insideList && !currentContext->insideBeginEnd && retrace::profiling) {
        glretrace::beginProfile(call, false);
    }
    glCopyTexImage2D(target, level, internalformat, x, y, width, height, border);
    if (currentContext && !currentContext->insideList && !currentContext->insideBeginEnd && retrace::profiling) {
        glretrace::endProfile(call, false);
    }
    if (retrace::debug && currentContext && !currentContext->insideBeginEnd) {
        glretrace::checkGlError(call);
    }
}

static void retrace_glCopyTexSubImage2D(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    GLenum target;
    target = static_cast<GLenum>((call.arg(0)).toSInt());

    GLint level;
    level = (call.arg(1)).toSInt();

    GLint xoffset;
    xoffset = (call.arg(2)).toSInt();

    GLint yoffset;
    yoffset = (call.arg(3)).toSInt();

    GLint x;
    x = (call.arg(4)).toSInt();

    GLint y;
    y = (call.arg(5)).toSInt();

    GLsizei width;
    width = (call.arg(6)).toSInt();

    GLsizei height;
    height = (call.arg(7)).toSInt();

    glretrace::Context *currentContext = glretrace::getCurrentContext();
    if (!currentContext) {
        if (retrace::debug) {
            retrace::warning(call) << "no current context\n";
        }
#ifndef _WIN32
        return;
#endif
    }
    if (currentContext && !currentContext->insideList && !currentContext->insideBeginEnd && retrace::profiling) {
        glretrace::beginProfile(call, false);
    }
    glCopyTexSubImage2D(target, level, xoffset, yoffset, x, y, width, height);
    if (currentContext && !currentContext->insideList && !currentContext->insideBeginEnd && retrace::profiling) {
        glretrace::endProfile(call, false);
    }
    if (retrace::debug && currentContext && !currentContext->insideBeginEnd) {
        glretrace::checkGlError(call);
    }
}

static void retrace_glTexSubImage2D(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    GLenum target;
    target = static_cast<GLenum>((call.arg(0)).toSInt());

    GLint level;
    level = (call.arg(1)).toSInt();

    GLint xoffset;
    xoffset = (call.arg(2)).toSInt();

    GLint yoffset;
    yoffset = (call.arg(3)).toSInt();

    GLsizei width;
    width = (call.arg(4)).toSInt();

    GLsizei height;
    height = (call.arg(5)).toSInt();

    GLenum format;
    format = static_cast<GLenum>((call.arg(6)).toSInt());

    GLenum type;
    type = static_cast<GLenum>((call.arg(7)).toSInt());

    GLvoid * pixels;
    pixels = static_cast<GLvoid *>((call.arg(8)).toPointer());

    glretrace::Context *currentContext = glretrace::getCurrentContext();
    if (!currentContext) {
        if (retrace::debug) {
            retrace::warning(call) << "no current context\n";
        }
#ifndef _WIN32
        return;
#endif
    }
    if (currentContext && !currentContext->insideList && !currentContext->insideBeginEnd && retrace::profiling) {
        glretrace::beginProfile(call, false);
    }
    glTexSubImage2D(target, level, xoffset, yoffset, width, height, format, type, pixels);
    if (currentContext && !currentContext->insideList && !currentContext->insideBeginEnd && retrace::profiling) {
        glretrace::endProfile(call, false);
    }
    if (retrace::debug && currentContext && !currentContext->insideBeginEnd) {
        glretrace::checkGlError(call);
    }
}

static void retrace_glBindTexture(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    GLenum target;
    target = static_cast<GLenum>((call.arg(0)).toSInt());

    GLuint texture;
    texture = (call.arg(1)).toUInt();
    if (retrace::verbosity >= 2) {
        std::cout << "texture " << size_t(texture) << " <- " << size_t(_texture_map[texture]) << "\n";
    }
    texture = _texture_map[texture];

    glretrace::Context *currentContext = glretrace::getCurrentContext();
    if (!currentContext) {
        if (retrace::debug) {
            retrace::warning(call) << "no current context\n";
        }
#ifndef _WIN32
        return;
#endif
    }
    if (currentContext && !currentContext->insideList && !currentContext->insideBeginEnd && retrace::profiling) {
        glretrace::beginProfile(call, false);
    }
    glBindTexture(target, texture);
    if (currentContext && !currentContext->insideList && !currentContext->insideBeginEnd && retrace::profiling) {
        glretrace::endProfile(call, false);
    }
    if (retrace::debug && currentContext && !currentContext->insideBeginEnd) {
        glretrace::checkGlError(call);
    }
}

static void retrace_glDeleteTextures(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    GLsizei n;
    n = (call.arg(0)).toSInt();

    GLuint * textures;
    textures = _allocator.allocArray<GLuint>(&call.arg(1));
    const trace::Array *_a_GLuint6_0 = (call.arg(1)).toArray();
    if (_a_GLuint6_0) {
        for (size_t _jGLuint6 = 0; _jGLuint6 < _a_GLuint6_0->values.size(); ++_jGLuint6) {
    textures[_jGLuint6] = (*_a_GLuint6_0->values[_jGLuint6]).toUInt();
    if (retrace::verbosity >= 2) {
        std::cout << "texture " << size_t(textures[_jGLuint6]) << " <- " << size_t(_texture_map[textures[_jGLuint6]]) << "\n";
    }
    textures[_jGLuint6] = _texture_map[textures[_jGLuint6]];
        }
    }

    glretrace::Context *currentContext = glretrace::getCurrentContext();
    if (!currentContext) {
        if (retrace::debug) {
            retrace::warning(call) << "no current context\n";
        }
#ifndef _WIN32
        return;
#endif
    }
    if (currentContext && !currentContext->insideList && !currentContext->insideBeginEnd && retrace::profiling) {
        glretrace::beginProfile(call, false);
    }
    glDeleteTextures(n, textures);
    if (currentContext && !currentContext->insideList && !currentContext->insideBeginEnd && retrace::profiling) {
        glretrace::endProfile(call, false);
    }
    if (retrace::debug && currentContext && !currentContext->insideBeginEnd) {
        glretrace::checkGlError(call);
    }
}

static void retrace_glGenTextures(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    GLsizei n;
    n = (call.arg(0)).toSInt();

    GLuint * textures;
    textures = _allocator.allocArray<GLuint>(&call.arg(1));

    glretrace::Context *currentContext = glretrace::getCurrentContext();
    if (!currentContext) {
        if (retrace::debug) {
            retrace::warning(call) << "no current context\n";
        }
#ifndef _WIN32
        return;
#endif
    }
    if (currentContext && !currentContext->insideList && !currentContext->insideBeginEnd && retrace::profiling) {
        glretrace::beginProfile(call, false);
    }
    glGenTextures(n, textures);
    if (currentContext && !currentContext->insideList && !currentContext->insideBeginEnd && retrace::profiling) {
        glretrace::endProfile(call, false);
    }
    if (retrace::debug && currentContext && !currentContext->insideBeginEnd) {
        glretrace::checkGlError(call);
    }
    const trace::Array *_aGLuint8 = (call.arg(1)).toArray();
    if (_aGLuint8) {
        for (size_t _jGLuint8 = 0; _jGLuint8 < _aGLuint8->values.size(); ++_jGLuint8) {
    GLuint _origResult;
    _origResult = (*_aGLuint8->values[_jGLuint8]).toUInt();
    _texture_map[_origResult] = textures[_jGLuint8];
    if (retrace::verbosity >= 2) {
        std::cout << "texture " << _origResult << " -> " << textures[_jGLuint8] << "\n";
    }
        }
    }
}

static void retrace_glBlendColor(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    GLfloat red;
    red = (call.arg(0)).toFloat();

    GLfloat green;
    green = (call.arg(1)).toFloat();

    GLfloat blue;
    blue = (call.arg(2)).toFloat();

    GLfloat alpha;
    alpha = (call.arg(3)).toFloat();

    glretrace::Context *currentContext = glretrace::getCurrentContext();
    if (!currentContext) {
        if (retrace::debug) {
            retrace::warning(call) << "no current context\n";
        }
#ifndef _WIN32
        return;
#endif
    }
    if (currentContext && !currentContext->insideList && !currentContext->insideBeginEnd && retrace::profiling) {
        glretrace::beginProfile(call, false);
    }
    glBlendColor(red, green, blue, alpha);
    if (currentContext && !currentContext->insideList && !currentContext->insideBeginEnd && retrace::profiling) {
        glretrace::endProfile(call, false);
    }
    if (retrace::debug && currentContext && !currentContext->insideBeginEnd) {
        glretrace::checkGlError(call);
    }
}

static void retrace_glBlendEquation(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    GLenum mode;
    mode = static_cast<GLenum>((call.arg(0)).toSInt());

    glretrace::Context *currentContext = glretrace::getCurrentContext();
    if (!currentContext) {
        if (retrace::debug) {
            retrace::warning(call) << "no current context\n";
        }
#ifndef _WIN32
        return;
#endif
    }
    if (currentContext && !currentContext->insideList && !currentContext->insideBeginEnd && retrace::profiling) {
        glretrace::beginProfile(call, false);
    }
    glBlendEquation(mode);
    if (currentContext && !currentContext->insideList && !currentContext->insideBeginEnd && retrace::profiling) {
        glretrace::endProfile(call, false);
    }
    if (retrace::debug && currentContext && !currentContext->insideBeginEnd) {
        glretrace::checkGlError(call);
    }
}

static void retrace_glActiveTexture(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    GLenum texture;
    texture = static_cast<GLenum>((call.arg(0)).toSInt());

    glretrace::Context *currentContext = glretrace::getCurrentContext();
    if (!currentContext) {
        if (retrace::debug) {
            retrace::warning(call) << "no current context\n";
        }
#ifndef _WIN32
        return;
#endif
    }
    if (currentContext && !currentContext->insideList && !currentContext->insideBeginEnd && retrace::profiling) {
        glretrace::beginProfile(call, false);
    }
    glActiveTexture(texture);
    if (currentContext && !currentContext->insideList && !currentContext->insideBeginEnd && retrace::profiling) {
        glretrace::endProfile(call, false);
    }
    if (retrace::debug && currentContext && !currentContext->insideBeginEnd) {
        glretrace::checkGlError(call);
    }
}

static void retrace_glSampleCoverage(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    GLfloat value;
    value = (call.arg(0)).toFloat();

    GLboolean invert;
    invert = static_cast<GLboolean>((call.arg(1)).toSInt());

    glretrace::Context *currentContext = glretrace::getCurrentContext();
    if (!currentContext) {
        if (retrace::debug) {
            retrace::warning(call) << "no current context\n";
        }
#ifndef _WIN32
        return;
#endif
    }
    if (currentContext && !currentContext->insideList && !currentContext->insideBeginEnd && retrace::profiling) {
        glretrace::beginProfile(call, false);
    }
    glSampleCoverage(value, invert);
    if (currentContext && !currentContext->insideList && !currentContext->insideBeginEnd && retrace::profiling) {
        glretrace::endProfile(call, false);
    }
    if (retrace::debug && currentContext && !currentContext->insideBeginEnd) {
        glretrace::checkGlError(call);
    }
}

static void retrace_glCompressedTexImage2D(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    GLenum target;
    target = static_cast<GLenum>((call.arg(0)).toSInt());

    GLint level;
    level = (call.arg(1)).toSInt();

    GLenum internalformat;
    internalformat = static_cast<GLenum>((call.arg(2)).toSInt());

    GLsizei width;
    width = (call.arg(3)).toSInt();

    GLsizei height;
    height = (call.arg(4)).toSInt();

    GLint border;
    border = (call.arg(5)).toSInt();

    GLsizei imageSize;
    imageSize = (call.arg(6)).toSInt();

    GLvoid * data;
    data = static_cast<GLvoid *>((call.arg(7)).toPointer());

    glretrace::Context *currentContext = glretrace::getCurrentContext();
    if (!currentContext) {
        if (retrace::debug) {
            retrace::warning(call) << "no current context\n";
        }
#ifndef _WIN32
        return;
#endif
    }
    if (currentContext && !currentContext->insideList && !currentContext->insideBeginEnd && retrace::profiling) {
        glretrace::beginProfile(call, false);
    }
    glCompressedTexImage2D(target, level, internalformat, width, height, border, imageSize, data);
    if (currentContext && !currentContext->insideList && !currentContext->insideBeginEnd && retrace::profiling) {
        glretrace::endProfile(call, false);
    }
    if (retrace::debug && currentContext && !currentContext->insideBeginEnd) {
        glretrace::checkGlError(call);
    }
}

static void retrace_glCompressedTexSubImage2D(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    GLenum target;
    target = static_cast<GLenum>((call.arg(0)).toSInt());

    GLint level;
    level = (call.arg(1)).toSInt();

    GLint xoffset;
    xoffset = (call.arg(2)).toSInt();

    GLint yoffset;
    yoffset = (call.arg(3)).toSInt();

    GLsizei width;
    width = (call.arg(4)).toSInt();

    GLsizei height;
    height = (call.arg(5)).toSInt();

    GLenum format;
    format = static_cast<GLenum>((call.arg(6)).toSInt());

    GLsizei imageSize;
    imageSize = (call.arg(7)).toSInt();

    GLvoid * data;
    data = static_cast<GLvoid *>((call.arg(8)).toPointer());

    glretrace::Context *currentContext = glretrace::getCurrentContext();
    if (!currentContext) {
        if (retrace::debug) {
            retrace::warning(call) << "no current context\n";
        }
#ifndef _WIN32
        return;
#endif
    }
    if (currentContext && !currentContext->insideList && !currentContext->insideBeginEnd && retrace::profiling) {
        glretrace::beginProfile(call, false);
    }
    glCompressedTexSubImage2D(target, level, xoffset, yoffset, width, height, format, imageSize, data);
    if (currentContext && !currentContext->insideList && !currentContext->insideBeginEnd && retrace::profiling) {
        glretrace::endProfile(call, false);
    }
    if (retrace::debug && currentContext && !currentContext->insideBeginEnd) {
        glretrace::checkGlError(call);
    }
}

static void retrace_glBlendFuncSeparate(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    GLenum sfactorRGB;
    sfactorRGB = static_cast<GLenum>((call.arg(0)).toSInt());

    GLenum dfactorRGB;
    dfactorRGB = static_cast<GLenum>((call.arg(1)).toSInt());

    GLenum sfactorAlpha;
    sfactorAlpha = static_cast<GLenum>((call.arg(2)).toSInt());

    GLenum dfactorAlpha;
    dfactorAlpha = static_cast<GLenum>((call.arg(3)).toSInt());

    glretrace::Context *currentContext = glretrace::getCurrentContext();
    if (!currentContext) {
        if (retrace::debug) {
            retrace::warning(call) << "no current context\n";
        }
#ifndef _WIN32
        return;
#endif
    }
    if (currentContext && !currentContext->insideList && !currentContext->insideBeginEnd && retrace::profiling) {
        glretrace::beginProfile(call, false);
    }
    glBlendFuncSeparate(sfactorRGB, dfactorRGB, sfactorAlpha, dfactorAlpha);
    if (currentContext && !currentContext->insideList && !currentContext->insideBeginEnd && retrace::profiling) {
        glretrace::endProfile(call, false);
    }
    if (retrace::debug && currentContext && !currentContext->insideBeginEnd) {
        glretrace::checkGlError(call);
    }
}

static void retrace_glBindBuffer(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    GLenum target;
    target = static_cast<GLenum>((call.arg(0)).toSInt());

    GLuint buffer;
    buffer = (call.arg(1)).toUInt();
    if (retrace::verbosity >= 2) {
        std::cout << "buffer " << size_t(buffer) << " <- " << size_t(_buffer_map[buffer]) << "\n";
    }
    buffer = _buffer_map[buffer];

    glretrace::Context *currentContext = glretrace::getCurrentContext();
    if (!currentContext) {
        if (retrace::debug) {
            retrace::warning(call) << "no current context\n";
        }
#ifndef _WIN32
        return;
#endif
    }
    if (currentContext && !currentContext->insideList && !currentContext->insideBeginEnd && retrace::profiling) {
        glretrace::beginProfile(call, false);
    }
    glBindBuffer(target, buffer);
    if (currentContext && !currentContext->insideList && !currentContext->insideBeginEnd && retrace::profiling) {
        glretrace::endProfile(call, false);
    }
    if (retrace::debug && currentContext && !currentContext->insideBeginEnd) {
        glretrace::checkGlError(call);
    }
}

static void retrace_glDeleteBuffers(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    GLsizei n;
    n = (call.arg(0)).toSInt();

    GLuint * buffer;
    buffer = _allocator.allocArray<GLuint>(&call.arg(1));
    const trace::Array *_a_GLuint9_0 = (call.arg(1)).toArray();
    if (_a_GLuint9_0) {
        for (size_t _jGLuint9 = 0; _jGLuint9 < _a_GLuint9_0->values.size(); ++_jGLuint9) {
    buffer[_jGLuint9] = (*_a_GLuint9_0->values[_jGLuint9]).toUInt();
    if (retrace::verbosity >= 2) {
        std::cout << "buffer " << size_t(buffer[_jGLuint9]) << " <- " << size_t(_buffer_map[buffer[_jGLuint9]]) << "\n";
    }
    buffer[_jGLuint9] = _buffer_map[buffer[_jGLuint9]];
        }
    }

    glretrace::Context *currentContext = glretrace::getCurrentContext();
    if (!currentContext) {
        if (retrace::debug) {
            retrace::warning(call) << "no current context\n";
        }
#ifndef _WIN32
        return;
#endif
    }
    if (currentContext && !currentContext->insideList && !currentContext->insideBeginEnd && retrace::profiling) {
        glretrace::beginProfile(call, false);
    }
    glDeleteBuffers(n, buffer);
    if (currentContext && !currentContext->insideList && !currentContext->insideBeginEnd && retrace::profiling) {
        glretrace::endProfile(call, false);
    }
    if (retrace::debug && currentContext && !currentContext->insideBeginEnd) {
        glretrace::checkGlError(call);
    }
}

static void retrace_glGenBuffers(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    GLsizei n;
    n = (call.arg(0)).toSInt();

    GLuint * buffer;
    buffer = _allocator.allocArray<GLuint>(&call.arg(1));

    glretrace::Context *currentContext = glretrace::getCurrentContext();
    if (!currentContext) {
        if (retrace::debug) {
            retrace::warning(call) << "no current context\n";
        }
#ifndef _WIN32
        return;
#endif
    }
    if (currentContext && !currentContext->insideList && !currentContext->insideBeginEnd && retrace::profiling) {
        glretrace::beginProfile(call, false);
    }
    glGenBuffers(n, buffer);
    if (currentContext && !currentContext->insideList && !currentContext->insideBeginEnd && retrace::profiling) {
        glretrace::endProfile(call, false);
    }
    if (retrace::debug && currentContext && !currentContext->insideBeginEnd) {
        glretrace::checkGlError(call);
    }
    const trace::Array *_aGLuint11 = (call.arg(1)).toArray();
    if (_aGLuint11) {
        for (size_t _jGLuint11 = 0; _jGLuint11 < _aGLuint11->values.size(); ++_jGLuint11) {
    GLuint _origResult;
    _origResult = (*_aGLuint11->values[_jGLuint11]).toUInt();
    _buffer_map[_origResult] = buffer[_jGLuint11];
    if (retrace::verbosity >= 2) {
        std::cout << "buffer " << _origResult << " -> " << buffer[_jGLuint11] << "\n";
    }
        }
    }
}

static void retrace_glBufferData(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    GLenum target;
    target = static_cast<GLenum>((call.arg(0)).toSInt());

    GLsizeiptr size;
    size = (call.arg(1)).toSInt();

    GLvoid * data;
    data = static_cast<GLvoid *>((call.arg(2)).toPointer());

    GLenum usage;
    usage = static_cast<GLenum>((call.arg(3)).toSInt());

    glretrace::Context *currentContext = glretrace::getCurrentContext();
    if (!currentContext) {
        if (retrace::debug) {
            retrace::warning(call) << "no current context\n";
        }
#ifndef _WIN32
        return;
#endif
    }
    if (currentContext && !currentContext->insideList && !currentContext->insideBeginEnd && retrace::profiling) {
        glretrace::beginProfile(call, false);
    }
    glBufferData(target, size, data, usage);
    if (currentContext && !currentContext->insideList && !currentContext->insideBeginEnd && retrace::profiling) {
        glretrace::endProfile(call, false);
    }
    if (retrace::debug && currentContext && !currentContext->insideBeginEnd) {
        glretrace::checkGlError(call);
    }
}

static void retrace_glBufferSubData(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    GLenum target;
    target = static_cast<GLenum>((call.arg(0)).toSInt());

    GLintptr offset;
    offset = (call.arg(1)).toSInt();

    GLsizeiptr size;
    size = (call.arg(2)).toSInt();

    GLvoid * data;
    data = static_cast<GLvoid *>((call.arg(3)).toPointer());

    glretrace::Context *currentContext = glretrace::getCurrentContext();
    if (!currentContext) {
        if (retrace::debug) {
            retrace::warning(call) << "no current context\n";
        }
#ifndef _WIN32
        return;
#endif
    }
    if (currentContext && !currentContext->insideList && !currentContext->insideBeginEnd && retrace::profiling) {
        glretrace::beginProfile(call, false);
    }
    glBufferSubData(target, offset, size, data);
    if (currentContext && !currentContext->insideList && !currentContext->insideBeginEnd && retrace::profiling) {
        glretrace::endProfile(call, false);
    }
    if (retrace::debug && currentContext && !currentContext->insideBeginEnd) {
        glretrace::checkGlError(call);
    }
}

static void retrace_glBlendEquationSeparate(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    GLenum modeRGB;
    modeRGB = static_cast<GLenum>((call.arg(0)).toSInt());

    GLenum modeAlpha;
    modeAlpha = static_cast<GLenum>((call.arg(1)).toSInt());

    glretrace::Context *currentContext = glretrace::getCurrentContext();
    if (!currentContext) {
        if (retrace::debug) {
            retrace::warning(call) << "no current context\n";
        }
#ifndef _WIN32
        return;
#endif
    }
    if (currentContext && !currentContext->insideList && !currentContext->insideBeginEnd && retrace::profiling) {
        glretrace::beginProfile(call, false);
    }
    glBlendEquationSeparate(modeRGB, modeAlpha);
    if (currentContext && !currentContext->insideList && !currentContext->insideBeginEnd && retrace::profiling) {
        glretrace::endProfile(call, false);
    }
    if (retrace::debug && currentContext && !currentContext->insideBeginEnd) {
        glretrace::checkGlError(call);
    }
}

static void retrace_glStencilOpSeparate(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    GLenum face;
    face = static_cast<GLenum>((call.arg(0)).toSInt());

    GLenum sfail;
    sfail = static_cast<GLenum>((call.arg(1)).toSInt());

    GLenum dpfail;
    dpfail = static_cast<GLenum>((call.arg(2)).toSInt());

    GLenum dppass;
    dppass = static_cast<GLenum>((call.arg(3)).toSInt());

    glretrace::Context *currentContext = glretrace::getCurrentContext();
    if (!currentContext) {
        if (retrace::debug) {
            retrace::warning(call) << "no current context\n";
        }
#ifndef _WIN32
        return;
#endif
    }
    if (currentContext && !currentContext->insideList && !currentContext->insideBeginEnd && retrace::profiling) {
        glretrace::beginProfile(call, false);
    }
    glStencilOpSeparate(face, sfail, dpfail, dppass);
    if (currentContext && !currentContext->insideList && !currentContext->insideBeginEnd && retrace::profiling) {
        glretrace::endProfile(call, false);
    }
    if (retrace::debug && currentContext && !currentContext->insideBeginEnd) {
        glretrace::checkGlError(call);
    }
}

static void retrace_glStencilFuncSeparate(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    GLenum face;
    face = static_cast<GLenum>((call.arg(0)).toSInt());

    GLenum func;
    func = static_cast<GLenum>((call.arg(1)).toSInt());

    GLint ref;
    ref = (call.arg(2)).toSInt();

    GLuint mask;
    mask = (call.arg(3)).toUInt();

    glretrace::Context *currentContext = glretrace::getCurrentContext();
    if (!currentContext) {
        if (retrace::debug) {
            retrace::warning(call) << "no current context\n";
        }
#ifndef _WIN32
        return;
#endif
    }
    if (currentContext && !currentContext->insideList && !currentContext->insideBeginEnd && retrace::profiling) {
        glretrace::beginProfile(call, false);
    }
    glStencilFuncSeparate(face, func, ref, mask);
    if (currentContext && !currentContext->insideList && !currentContext->insideBeginEnd && retrace::profiling) {
        glretrace::endProfile(call, false);
    }
    if (retrace::debug && currentContext && !currentContext->insideBeginEnd) {
        glretrace::checkGlError(call);
    }
}

static void retrace_glStencilMaskSeparate(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    GLenum face;
    face = static_cast<GLenum>((call.arg(0)).toSInt());

    GLuint mask;
    mask = (call.arg(1)).toUInt();

    glretrace::Context *currentContext = glretrace::getCurrentContext();
    if (!currentContext) {
        if (retrace::debug) {
            retrace::warning(call) << "no current context\n";
        }
#ifndef _WIN32
        return;
#endif
    }
    if (currentContext && !currentContext->insideList && !currentContext->insideBeginEnd && retrace::profiling) {
        glretrace::beginProfile(call, false);
    }
    glStencilMaskSeparate(face, mask);
    if (currentContext && !currentContext->insideList && !currentContext->insideBeginEnd && retrace::profiling) {
        glretrace::endProfile(call, false);
    }
    if (retrace::debug && currentContext && !currentContext->insideBeginEnd) {
        glretrace::checkGlError(call);
    }
}

static void retrace_glAttachShader(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    GLuint program;
    program = (call.arg(0)).toUInt();
    if (retrace::verbosity >= 2) {
        std::cout << "program " << size_t(program) << " <- " << size_t(_program_map[program]) << "\n";
    }
if (glretrace::supportsARBShaderObjects) {
    program = _handleARB_map[program];
} else {
    program = _program_map[program];
}

    GLuint shader;
    shader = (call.arg(1)).toUInt();
    if (retrace::verbosity >= 2) {
        std::cout << "shader " << size_t(shader) << " <- " << size_t(_shader_map[shader]) << "\n";
    }
if (glretrace::supportsARBShaderObjects) {
    shader = _handleARB_map[shader];
} else {
    shader = _shader_map[shader];
}

    glretrace::Context *currentContext = glretrace::getCurrentContext();
    if (!currentContext) {
        if (retrace::debug) {
            retrace::warning(call) << "no current context\n";
        }
#ifndef _WIN32
        return;
#endif
    }
    if (currentContext && !currentContext->insideList && !currentContext->insideBeginEnd && retrace::profiling) {
        glretrace::beginProfile(call, false);
    }
    glAttachShader(program, shader);
    if (currentContext && !currentContext->insideList && !currentContext->insideBeginEnd && retrace::profiling) {
        glretrace::endProfile(call, false);
    }
    if (retrace::debug && currentContext && !currentContext->insideBeginEnd) {
        glretrace::checkGlError(call);
    }
}

static void retrace_glBindAttribLocation(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    GLuint program;
    program = (call.arg(0)).toUInt();
    if (retrace::verbosity >= 2) {
        std::cout << "program " << size_t(program) << " <- " << size_t(_program_map[program]) << "\n";
    }
if (glretrace::supportsARBShaderObjects) {
    program = _handleARB_map[program];
} else {
    program = _program_map[program];
}

    GLuint index;
    index = (call.arg(1)).toUInt();

    const GLchar * name;
    name = (const GLchar *)((call.arg(2)).toString());

    glretrace::Context *currentContext = glretrace::getCurrentContext();
    if (!currentContext) {
        if (retrace::debug) {
            retrace::warning(call) << "no current context\n";
        }
#ifndef _WIN32
        return;
#endif
    }
    if (currentContext && !currentContext->insideList && !currentContext->insideBeginEnd && retrace::profiling) {
        glretrace::beginProfile(call, false);
    }
    glBindAttribLocation(program, index, name);
    if (currentContext && !currentContext->insideList && !currentContext->insideBeginEnd && retrace::profiling) {
        glretrace::endProfile(call, false);
    }
    if (retrace::debug && currentContext && !currentContext->insideBeginEnd) {
        glretrace::checkGlError(call);
    }
}

static void retrace_glCompileShader(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    GLuint shader;
    shader = (call.arg(0)).toUInt();
    if (retrace::verbosity >= 2) {
        std::cout << "shader " << size_t(shader) << " <- " << size_t(_shader_map[shader]) << "\n";
    }
if (glretrace::supportsARBShaderObjects) {
    shader = _handleARB_map[shader];
} else {
    shader = _shader_map[shader];
}

    glretrace::Context *currentContext = glretrace::getCurrentContext();
    if (!currentContext) {
        if (retrace::debug) {
            retrace::warning(call) << "no current context\n";
        }
#ifndef _WIN32
        return;
#endif
    }
    if (currentContext && !currentContext->insideList && !currentContext->insideBeginEnd && retrace::profiling) {
        glretrace::beginProfile(call, false);
    }
    glCompileShader(shader);
    if (currentContext && !currentContext->insideList && !currentContext->insideBeginEnd && retrace::profiling) {
        glretrace::endProfile(call, false);
    }
    if (retrace::debug && currentContext && !currentContext->insideBeginEnd) {
        glretrace::checkGlError(call);
        GLint compile_status = 0;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &compile_status);
        if (!compile_status) {
             retrace::warning(call) << "compilation failed\n";
        }
        GLint info_log_length = 0;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &info_log_length);
        if (info_log_length > 1) {
             GLchar *infoLog = new GLchar[info_log_length];
             glGetShaderInfoLog(shader, info_log_length, NULL, infoLog);
             retrace::warning(call) << infoLog << "\n";
             delete [] infoLog;
        }
    }
}

static void retrace_glCreateProgram(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    GLuint _result;
    glretrace::Context *currentContext = glretrace::getCurrentContext();
    if (!currentContext) {
        if (retrace::debug) {
            retrace::warning(call) << "no current context\n";
        }
#ifndef _WIN32
        return;
#endif
    }
    if (currentContext && !currentContext->insideList && !currentContext->insideBeginEnd && retrace::profiling) {
        glretrace::beginProfile(call, false);
    }
    _result = glCreateProgram();
    (void)_result;
    if (currentContext && !currentContext->insideList && !currentContext->insideBeginEnd && retrace::profiling) {
        glretrace::endProfile(call, false);
    }
    if (retrace::debug && currentContext && !currentContext->insideBeginEnd) {
        glretrace::checkGlError(call);
    }
    GLuint _origResult;
    _origResult = (*call.ret).toUInt();
if (glretrace::supportsARBShaderObjects) {
    _handleARB_map[_origResult] = _result;
} else {
    _program_map[_origResult] = _result;
}
    if (retrace::verbosity >= 2) {
        std::cout << "program " << _origResult << " -> " << _result << "\n";
    }
}

static void retrace_glCreateShader(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    GLenum type;
    type = static_cast<GLenum>((call.arg(0)).toSInt());

    GLuint _result;
    glretrace::Context *currentContext = glretrace::getCurrentContext();
    if (!currentContext) {
        if (retrace::debug) {
            retrace::warning(call) << "no current context\n";
        }
#ifndef _WIN32
        return;
#endif
    }
    if (currentContext && !currentContext->insideList && !currentContext->insideBeginEnd && retrace::profiling) {
        glretrace::beginProfile(call, false);
    }
    _result = glCreateShader(type);
    (void)_result;
    if (currentContext && !currentContext->insideList && !currentContext->insideBeginEnd && retrace::profiling) {
        glretrace::endProfile(call, false);
    }
    if (retrace::debug && currentContext && !currentContext->insideBeginEnd) {
        glretrace::checkGlError(call);
    }
    GLuint _origResult;
    _origResult = (*call.ret).toUInt();
if (glretrace::supportsARBShaderObjects) {
    _handleARB_map[_origResult] = _result;
} else {
    _shader_map[_origResult] = _result;
}
    if (retrace::verbosity >= 2) {
        std::cout << "shader " << _origResult << " -> " << _result << "\n";
    }
}

static void retrace_glDeleteProgram(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    GLuint program;
    program = (call.arg(0)).toUInt();
    if (retrace::verbosity >= 2) {
        std::cout << "program " << size_t(program) << " <- " << size_t(_program_map[program]) << "\n";
    }
if (glretrace::supportsARBShaderObjects) {
    program = _handleARB_map[program];
} else {
    program = _program_map[program];
}

    glretrace::Context *currentContext = glretrace::getCurrentContext();
    if (!currentContext) {
        if (retrace::debug) {
            retrace::warning(call) << "no current context\n";
        }
#ifndef _WIN32
        return;
#endif
    }
    if (currentContext && !currentContext->insideList && !currentContext->insideBeginEnd && retrace::profiling) {
        glretrace::beginProfile(call, false);
    }
    glDeleteProgram(program);
    if (currentContext && !currentContext->insideList && !currentContext->insideBeginEnd && retrace::profiling) {
        glretrace::endProfile(call, false);
    }
    if (retrace::debug && currentContext && !currentContext->insideBeginEnd) {
        glretrace::checkGlError(call);
    }
}

static void retrace_glDeleteShader(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    GLuint shader;
    shader = (call.arg(0)).toUInt();
    if (retrace::verbosity >= 2) {
        std::cout << "shader " << size_t(shader) << " <- " << size_t(_shader_map[shader]) << "\n";
    }
if (glretrace::supportsARBShaderObjects) {
    shader = _handleARB_map[shader];
} else {
    shader = _shader_map[shader];
}

    glretrace::Context *currentContext = glretrace::getCurrentContext();
    if (!currentContext) {
        if (retrace::debug) {
            retrace::warning(call) << "no current context\n";
        }
#ifndef _WIN32
        return;
#endif
    }
    if (currentContext && !currentContext->insideList && !currentContext->insideBeginEnd && retrace::profiling) {
        glretrace::beginProfile(call, false);
    }
    glDeleteShader(shader);
    if (currentContext && !currentContext->insideList && !currentContext->insideBeginEnd && retrace::profiling) {
        glretrace::endProfile(call, false);
    }
    if (retrace::debug && currentContext && !currentContext->insideBeginEnd) {
        glretrace::checkGlError(call);
    }
}

static void retrace_glDetachShader(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    GLuint program;
    program = (call.arg(0)).toUInt();
    if (retrace::verbosity >= 2) {
        std::cout << "program " << size_t(program) << " <- " << size_t(_program_map[program]) << "\n";
    }
if (glretrace::supportsARBShaderObjects) {
    program = _handleARB_map[program];
} else {
    program = _program_map[program];
}

    GLuint shader;
    shader = (call.arg(1)).toUInt();
    if (retrace::verbosity >= 2) {
        std::cout << "shader " << size_t(shader) << " <- " << size_t(_shader_map[shader]) << "\n";
    }
if (glretrace::supportsARBShaderObjects) {
    shader = _handleARB_map[shader];
} else {
    shader = _shader_map[shader];
}

    glretrace::Context *currentContext = glretrace::getCurrentContext();
    if (!currentContext) {
        if (retrace::debug) {
            retrace::warning(call) << "no current context\n";
        }
#ifndef _WIN32
        return;
#endif
    }
    if (currentContext && !currentContext->insideList && !currentContext->insideBeginEnd && retrace::profiling) {
        glretrace::beginProfile(call, false);
    }
    if (!retrace::dumpingState) {
    glDetachShader(program, shader);
    }
    if (currentContext && !currentContext->insideList && !currentContext->insideBeginEnd && retrace::profiling) {
        glretrace::endProfile(call, false);
    }
    if (retrace::debug && currentContext && !currentContext->insideBeginEnd) {
        glretrace::checkGlError(call);
    }
}

static void retrace_glDisableVertexAttribArray(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    GLuint index;
    index = (call.arg(0)).toUInt();

    glretrace::Context *currentContext = glretrace::getCurrentContext();
    if (!currentContext) {
        if (retrace::debug) {
            retrace::warning(call) << "no current context\n";
        }
#ifndef _WIN32
        return;
#endif
    }
    if (currentContext && !currentContext->insideList && !currentContext->insideBeginEnd && retrace::profiling) {
        glretrace::beginProfile(call, false);
    }
    glDisableVertexAttribArray(index);
    if (currentContext && !currentContext->insideList && !currentContext->insideBeginEnd && retrace::profiling) {
        glretrace::endProfile(call, false);
    }
    if (retrace::debug && currentContext && !currentContext->insideBeginEnd) {
        glretrace::checkGlError(call);
    }
}

static void retrace_glEnableVertexAttribArray(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    GLuint index;
    index = (call.arg(0)).toUInt();

    glretrace::Context *currentContext = glretrace::getCurrentContext();
    if (!currentContext) {
        if (retrace::debug) {
            retrace::warning(call) << "no current context\n";
        }
#ifndef _WIN32
        return;
#endif
    }
    if (currentContext && !currentContext->insideList && !currentContext->insideBeginEnd && retrace::profiling) {
        glretrace::beginProfile(call, false);
    }
    glEnableVertexAttribArray(index);
    if (currentContext && !currentContext->insideList && !currentContext->insideBeginEnd && retrace::profiling) {
        glretrace::endProfile(call, false);
    }
    if (retrace::debug && currentContext && !currentContext->insideBeginEnd) {
        glretrace::checkGlError(call);
    }
}

static void retrace_glGetAttribLocation(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    GLuint program;
    program = (call.arg(0)).toUInt();
    if (retrace::verbosity >= 2) {
        std::cout << "program " << size_t(program) << " <- " << size_t(_program_map[program]) << "\n";
    }
if (glretrace::supportsARBShaderObjects) {
    program = _handleARB_map[program];
} else {
    program = _program_map[program];
}

    const GLchar * name;
    name = (const GLchar *)((call.arg(1)).toString());

    GLint _result;
    glretrace::Context *currentContext = glretrace::getCurrentContext();
    if (!currentContext) {
        if (retrace::debug) {
            retrace::warning(call) << "no current context\n";
        }
#ifndef _WIN32
        return;
#endif
    }
    if (currentContext && !currentContext->insideList && !currentContext->insideBeginEnd && retrace::profiling) {
        glretrace::beginProfile(call, false);
    }
    _result = glGetAttribLocation(program, name);
    (void)_result;
    if (currentContext && !currentContext->insideList && !currentContext->insideBeginEnd && retrace::profiling) {
        glretrace::endProfile(call, false);
    }
    if (retrace::debug && currentContext && !currentContext->insideBeginEnd) {
        glretrace::checkGlError(call);
    GLint _origResult = call.ret->toSInt();
    if (_result != _origResult) {
        retrace::warning(call) << "vertex attrib location mismatch " << _origResult << " -> " << _result << "\n";
    }
    }
}

static void retrace_glGetUniformLocation(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    GLuint program;
    program = (call.arg(0)).toUInt();
    if (retrace::verbosity >= 2) {
        std::cout << "program " << size_t(program) << " <- " << size_t(_program_map[program]) << "\n";
    }
if (glretrace::supportsARBShaderObjects) {
    program = _handleARB_map[program];
} else {
    program = _program_map[program];
}

    const GLchar * name;
    name = (const GLchar *)((call.arg(1)).toString());

    GLint _result;
    glretrace::Context *currentContext = glretrace::getCurrentContext();
    if (!currentContext) {
        if (retrace::debug) {
            retrace::warning(call) << "no current context\n";
        }
#ifndef _WIN32
        return;
#endif
    }
    if (currentContext && !currentContext->insideList && !currentContext->insideBeginEnd && retrace::profiling) {
        glretrace::beginProfile(call, false);
    }
    _result = glGetUniformLocation(program, name);
    (void)_result;
    if (currentContext && !currentContext->insideList && !currentContext->insideBeginEnd && retrace::profiling) {
        glretrace::endProfile(call, false);
    }
    if (retrace::debug && currentContext && !currentContext->insideBeginEnd) {
        glretrace::checkGlError(call);
    }
    GLint _origResult;
    _origResult = (*call.ret).toSInt();
    _location_map[program][_origResult] = _result;
    if (retrace::verbosity >= 2) {
        std::cout << "location " << _origResult << " -> " << _result << "\n";
    }
}

static void retrace_glLinkProgram(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    GLuint program;
    program = (call.arg(0)).toUInt();
    if (retrace::verbosity >= 2) {
        std::cout << "program " << size_t(program) << " <- " << size_t(_program_map[program]) << "\n";
    }
if (glretrace::supportsARBShaderObjects) {
    program = _handleARB_map[program];
} else {
    program = _program_map[program];
}

    glretrace::Context *currentContext = glretrace::getCurrentContext();
    if (!currentContext) {
        if (retrace::debug) {
            retrace::warning(call) << "no current context\n";
        }
#ifndef _WIN32
        return;
#endif
    }
    if (currentContext && !currentContext->insideList && !currentContext->insideBeginEnd && retrace::profiling) {
        glretrace::beginProfile(call, false);
    }
    glLinkProgram(program);
    if (currentContext && !currentContext->insideList && !currentContext->insideBeginEnd && retrace::profiling) {
        glretrace::endProfile(call, false);
    }
    if (retrace::debug && currentContext && !currentContext->insideBeginEnd) {
        glretrace::checkGlError(call);
        GLint link_status = 0;
        glGetProgramiv(program, GL_LINK_STATUS, &link_status);
        if (!link_status) {
             retrace::warning(call) << "link failed\n";
        }
        GLint info_log_length = 0;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &info_log_length);
        if (info_log_length > 1) {
             GLchar *infoLog = new GLchar[info_log_length];
             glGetProgramInfoLog(program, info_log_length, NULL, infoLog);
             retrace::warning(call) << infoLog << "\n";
             delete [] infoLog;
        }
    }
}

static void retrace_glShaderSource(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    GLuint shader;
    shader = (call.arg(0)).toUInt();
    if (retrace::verbosity >= 2) {
        std::cout << "shader " << size_t(shader) << " <- " << size_t(_shader_map[shader]) << "\n";
    }
if (glretrace::supportsARBShaderObjects) {
    shader = _handleARB_map[shader];
} else {
    shader = _shader_map[shader];
}

    GLsizei count;
    count = (call.arg(1)).toSInt();

    const GLchar * * string;
    string = _allocator.allocArray<const GLchar *>(&call.arg(2));
    const trace::Array *_a_constGLchar2_0 = (call.arg(2)).toArray();
    if (_a_constGLchar2_0) {
        for (size_t _jconstGLchar2 = 0; _jconstGLchar2 < _a_constGLchar2_0->values.size(); ++_jconstGLchar2) {
    string[_jconstGLchar2] = (const GLchar *)((*_a_constGLchar2_0->values[_jconstGLchar2]).toString());
        }
    }

    GLint * length;
    length = _allocator.allocArray<GLint>(&call.arg(3));
    const trace::Array *_a_GLint15_0 = (call.arg(3)).toArray();
    if (_a_GLint15_0) {
        for (size_t _jGLint15 = 0; _jGLint15 < _a_GLint15_0->values.size(); ++_jGLint15) {
    length[_jGLint15] = (*_a_GLint15_0->values[_jGLint15]).toSInt();
        }
    }

    glretrace::Context *currentContext = glretrace::getCurrentContext();
    if (!currentContext) {
        if (retrace::debug) {
            retrace::warning(call) << "no current context\n";
        }
#ifndef _WIN32
        return;
#endif
    }
    if (currentContext && !currentContext->insideList && !currentContext->insideBeginEnd && retrace::profiling) {
        glretrace::beginProfile(call, false);
    }
    glShaderSource(shader, count, string, length);
    if (currentContext && !currentContext->insideList && !currentContext->insideBeginEnd && retrace::profiling) {
        glretrace::endProfile(call, false);
    }
    if (retrace::debug && currentContext && !currentContext->insideBeginEnd) {
        glretrace::checkGlError(call);
    }
}

static void retrace_glUseProgram(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    GLuint program;
    program = (call.arg(0)).toUInt();
    if (retrace::verbosity >= 2) {
        std::cout << "program " << size_t(program) << " <- " << size_t(_program_map[program]) << "\n";
    }
if (glretrace::supportsARBShaderObjects) {
    program = _handleARB_map[program];
} else {
    program = _program_map[program];
}

    glretrace::Context *currentContext = glretrace::getCurrentContext();
    if (!currentContext) {
        if (retrace::debug) {
            retrace::warning(call) << "no current context\n";
        }
#ifndef _WIN32
        return;
#endif
    }
    if (currentContext) {
        currentContext->activeProgram = call.arg(0).toUInt();
    }
    if (currentContext && !currentContext->insideList && !currentContext->insideBeginEnd && retrace::profiling) {
        glretrace::beginProfile(call, false);
    }
    glUseProgram(program);
    if (currentContext && !currentContext->insideList && !currentContext->insideBeginEnd && retrace::profiling) {
        glretrace::endProfile(call, false);
    }
    if (retrace::debug && currentContext && !currentContext->insideBeginEnd) {
        glretrace::checkGlError(call);
    }
}

static void retrace_glUniform1f(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    GLint location;
    GLint program = _getActiveProgram();
    location = (call.arg(0)).toSInt();
    if (retrace::verbosity >= 2) {
        std::cout << "location " << size_t(location) << " <- " << size_t(_location_map[program].lookupUniformLocation(location)) << "\n";
    }
    location = _location_map[program].lookupUniformLocation(location);

    GLfloat v0;
    v0 = (call.arg(1)).toFloat();

    glretrace::Context *currentContext = glretrace::getCurrentContext();
    if (!currentContext) {
        if (retrace::debug) {
            retrace::warning(call) << "no current context\n";
        }
#ifndef _WIN32
        return;
#endif
    }
    if (currentContext && !currentContext->insideList && !currentContext->insideBeginEnd && retrace::profiling) {
        glretrace::beginProfile(call, false);
    }
    glUniform1f(location, v0);
    if (currentContext && !currentContext->insideList && !currentContext->insideBeginEnd && retrace::profiling) {
        glretrace::endProfile(call, false);
    }
    if (retrace::debug && currentContext && !currentContext->insideBeginEnd) {
        glretrace::checkGlError(call);
    }
}

static void retrace_glUniform2f(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    GLint location;
    GLint program = _getActiveProgram();
    location = (call.arg(0)).toSInt();
    if (retrace::verbosity >= 2) {
        std::cout << "location " << size_t(location) << " <- " << size_t(_location_map[program].lookupUniformLocation(location)) << "\n";
    }
    location = _location_map[program].lookupUniformLocation(location);

    GLfloat v0;
    v0 = (call.arg(1)).toFloat();

    GLfloat v1;
    v1 = (call.arg(2)).toFloat();

    glretrace::Context *currentContext = glretrace::getCurrentContext();
    if (!currentContext) {
        if (retrace::debug) {
            retrace::warning(call) << "no current context\n";
        }
#ifndef _WIN32
        return;
#endif
    }
    if (currentContext && !currentContext->insideList && !currentContext->insideBeginEnd && retrace::profiling) {
        glretrace::beginProfile(call, false);
    }
    glUniform2f(location, v0, v1);
    if (currentContext && !currentContext->insideList && !currentContext->insideBeginEnd && retrace::profiling) {
        glretrace::endProfile(call, false);
    }
    if (retrace::debug && currentContext && !currentContext->insideBeginEnd) {
        glretrace::checkGlError(call);
    }
}

static void retrace_glUniform3f(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    GLint location;
    GLint program = _getActiveProgram();
    location = (call.arg(0)).toSInt();
    if (retrace::verbosity >= 2) {
        std::cout << "location " << size_t(location) << " <- " << size_t(_location_map[program].lookupUniformLocation(location)) << "\n";
    }
    location = _location_map[program].lookupUniformLocation(location);

    GLfloat v0;
    v0 = (call.arg(1)).toFloat();

    GLfloat v1;
    v1 = (call.arg(2)).toFloat();

    GLfloat v2;
    v2 = (call.arg(3)).toFloat();

    glretrace::Context *currentContext = glretrace::getCurrentContext();
    if (!currentContext) {
        if (retrace::debug) {
            retrace::warning(call) << "no current context\n";
        }
#ifndef _WIN32
        return;
#endif
    }
    if (currentContext && !currentContext->insideList && !currentContext->insideBeginEnd && retrace::profiling) {
        glretrace::beginProfile(call, false);
    }
    glUniform3f(location, v0, v1, v2);
    if (currentContext && !currentContext->insideList && !currentContext->insideBeginEnd && retrace::profiling) {
        glretrace::endProfile(call, false);
    }
    if (retrace::debug && currentContext && !currentContext->insideBeginEnd) {
        glretrace::checkGlError(call);
    }
}

static void retrace_glUniform4f(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    GLint location;
    GLint program = _getActiveProgram();
    location = (call.arg(0)).toSInt();
    if (retrace::verbosity >= 2) {
        std::cout << "location " << size_t(location) << " <- " << size_t(_location_map[program].lookupUniformLocation(location)) << "\n";
    }
    location = _location_map[program].lookupUniformLocation(location);

    GLfloat v0;
    v0 = (call.arg(1)).toFloat();

    GLfloat v1;
    v1 = (call.arg(2)).toFloat();

    GLfloat v2;
    v2 = (call.arg(3)).toFloat();

    GLfloat v3;
    v3 = (call.arg(4)).toFloat();

    glretrace::Context *currentContext = glretrace::getCurrentContext();
    if (!currentContext) {
        if (retrace::debug) {
            retrace::warning(call) << "no current context\n";
        }
#ifndef _WIN32
        return;
#endif
    }
    if (currentContext && !currentContext->insideList && !currentContext->insideBeginEnd && retrace::profiling) {
        glretrace::beginProfile(call, false);
    }
    glUniform4f(location, v0, v1, v2, v3);
    if (currentContext && !currentContext->insideList && !currentContext->insideBeginEnd && retrace::profiling) {
        glretrace::endProfile(call, false);
    }
    if (retrace::debug && currentContext && !currentContext->insideBeginEnd) {
        glretrace::checkGlError(call);
    }
}

static void retrace_glUniform1i(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    GLint location;
    GLint program = _getActiveProgram();
    location = (call.arg(0)).toSInt();
    if (retrace::verbosity >= 2) {
        std::cout << "location " << size_t(location) << " <- " << size_t(_location_map[program].lookupUniformLocation(location)) << "\n";
    }
    location = _location_map[program].lookupUniformLocation(location);

    GLint v0;
    v0 = (call.arg(1)).toSInt();

    glretrace::Context *currentContext = glretrace::getCurrentContext();
    if (!currentContext) {
        if (retrace::debug) {
            retrace::warning(call) << "no current context\n";
        }
#ifndef _WIN32
        return;
#endif
    }
    if (currentContext && !currentContext->insideList && !currentContext->insideBeginEnd && retrace::profiling) {
        glretrace::beginProfile(call, false);
    }
    glUniform1i(location, v0);
    if (currentContext && !currentContext->insideList && !currentContext->insideBeginEnd && retrace::profiling) {
        glretrace::endProfile(call, false);
    }
    if (retrace::debug && currentContext && !currentContext->insideBeginEnd) {
        glretrace::checkGlError(call);
    }
}

static void retrace_glUniform2i(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    GLint location;
    GLint program = _getActiveProgram();
    location = (call.arg(0)).toSInt();
    if (retrace::verbosity >= 2) {
        std::cout << "location " << size_t(location) << " <- " << size_t(_location_map[program].lookupUniformLocation(location)) << "\n";
    }
    location = _location_map[program].lookupUniformLocation(location);

    GLint v0;
    v0 = (call.arg(1)).toSInt();

    GLint v1;
    v1 = (call.arg(2)).toSInt();

    glretrace::Context *currentContext = glretrace::getCurrentContext();
    if (!currentContext) {
        if (retrace::debug) {
            retrace::warning(call) << "no current context\n";
        }
#ifndef _WIN32
        return;
#endif
    }
    if (currentContext && !currentContext->insideList && !currentContext->insideBeginEnd && retrace::profiling) {
        glretrace::beginProfile(call, false);
    }
    glUniform2i(location, v0, v1);
    if (currentContext && !currentContext->insideList && !currentContext->insideBeginEnd && retrace::profiling) {
        glretrace::endProfile(call, false);
    }
    if (retrace::debug && currentContext && !currentContext->insideBeginEnd) {
        glretrace::checkGlError(call);
    }
}

static void retrace_glUniform3i(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    GLint location;
    GLint program = _getActiveProgram();
    location = (call.arg(0)).toSInt();
    if (retrace::verbosity >= 2) {
        std::cout << "location " << size_t(location) << " <- " << size_t(_location_map[program].lookupUniformLocation(location)) << "\n";
    }
    location = _location_map[program].lookupUniformLocation(location);

    GLint v0;
    v0 = (call.arg(1)).toSInt();

    GLint v1;
    v1 = (call.arg(2)).toSInt();

    GLint v2;
    v2 = (call.arg(3)).toSInt();

    glretrace::Context *currentContext = glretrace::getCurrentContext();
    if (!currentContext) {
        if (retrace::debug) {
            retrace::warning(call) << "no current context\n";
        }
#ifndef _WIN32
        return;
#endif
    }
    if (currentContext && !currentContext->insideList && !currentContext->insideBeginEnd && retrace::profiling) {
        glretrace::beginProfile(call, false);
    }
    glUniform3i(location, v0, v1, v2);
    if (currentContext && !currentContext->insideList && !currentContext->insideBeginEnd && retrace::profiling) {
        glretrace::endProfile(call, false);
    }
    if (retrace::debug && currentContext && !currentContext->insideBeginEnd) {
        glretrace::checkGlError(call);
    }
}

static void retrace_glUniform4i(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    GLint location;
    GLint program = _getActiveProgram();
    location = (call.arg(0)).toSInt();
    if (retrace::verbosity >= 2) {
        std::cout << "location " << size_t(location) << " <- " << size_t(_location_map[program].lookupUniformLocation(location)) << "\n";
    }
    location = _location_map[program].lookupUniformLocation(location);

    GLint v0;
    v0 = (call.arg(1)).toSInt();

    GLint v1;
    v1 = (call.arg(2)).toSInt();

    GLint v2;
    v2 = (call.arg(3)).toSInt();

    GLint v3;
    v3 = (call.arg(4)).toSInt();

    glretrace::Context *currentContext = glretrace::getCurrentContext();
    if (!currentContext) {
        if (retrace::debug) {
            retrace::warning(call) << "no current context\n";
        }
#ifndef _WIN32
        return;
#endif
    }
    if (currentContext && !currentContext->insideList && !currentContext->insideBeginEnd && retrace::profiling) {
        glretrace::beginProfile(call, false);
    }
    glUniform4i(location, v0, v1, v2, v3);
    if (currentContext && !currentContext->insideList && !currentContext->insideBeginEnd && retrace::profiling) {
        glretrace::endProfile(call, false);
    }
    if (retrace::debug && currentContext && !currentContext->insideBeginEnd) {
        glretrace::checkGlError(call);
    }
}

static void retrace_glUniform1fv(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    GLint location;
    GLint program = _getActiveProgram();
    location = (call.arg(0)).toSInt();
    if (retrace::verbosity >= 2) {
        std::cout << "location " << size_t(location) << " <- " << size_t(_location_map[program].lookupUniformLocation(location)) << "\n";
    }
    location = _location_map[program].lookupUniformLocation(location);

    GLsizei count;
    count = (call.arg(1)).toSInt();

    GLfloat * value;
    value = _allocator.allocArray<GLfloat>(&call.arg(2));
    const trace::Array *_a_GLfloat6_0 = (call.arg(2)).toArray();
    if (_a_GLfloat6_0) {
        for (size_t _jGLfloat6 = 0; _jGLfloat6 < _a_GLfloat6_0->values.size(); ++_jGLfloat6) {
    value[_jGLfloat6] = (*_a_GLfloat6_0->values[_jGLfloat6]).toFloat();
        }
    }

    glretrace::Context *currentContext = glretrace::getCurrentContext();
    if (!currentContext) {
        if (retrace::debug) {
            retrace::warning(call) << "no current context\n";
        }
#ifndef _WIN32
        return;
#endif
    }
    if (currentContext && !currentContext->insideList && !currentContext->insideBeginEnd && retrace::profiling) {
        glretrace::beginProfile(call, false);
    }
    glUniform1fv(location, count, value);
    if (currentContext && !currentContext->insideList && !currentContext->insideBeginEnd && retrace::profiling) {
        glretrace::endProfile(call, false);
    }
    if (retrace::debug && currentContext && !currentContext->insideBeginEnd) {
        glretrace::checkGlError(call);
    }
}

static void retrace_glUniform2fv(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    GLint location;
    GLint program = _getActiveProgram();
    location = (call.arg(0)).toSInt();
    if (retrace::verbosity >= 2) {
        std::cout << "location " << size_t(location) << " <- " << size_t(_location_map[program].lookupUniformLocation(location)) << "\n";
    }
    location = _location_map[program].lookupUniformLocation(location);

    GLsizei count;
    count = (call.arg(1)).toSInt();

    GLfloat * value;
    value = _allocator.allocArray<GLfloat>(&call.arg(2));
    const trace::Array *_a_GLfloat7_0 = (call.arg(2)).toArray();
    if (_a_GLfloat7_0) {
        for (size_t _jGLfloat7 = 0; _jGLfloat7 < _a_GLfloat7_0->values.size(); ++_jGLfloat7) {
    value[_jGLfloat7] = (*_a_GLfloat7_0->values[_jGLfloat7]).toFloat();
        }
    }

    glretrace::Context *currentContext = glretrace::getCurrentContext();
    if (!currentContext) {
        if (retrace::debug) {
            retrace::warning(call) << "no current context\n";
        }
#ifndef _WIN32
        return;
#endif
    }
    if (currentContext && !currentContext->insideList && !currentContext->insideBeginEnd && retrace::profiling) {
        glretrace::beginProfile(call, false);
    }
    glUniform2fv(location, count, value);
    if (currentContext && !currentContext->insideList && !currentContext->insideBeginEnd && retrace::profiling) {
        glretrace::endProfile(call, false);
    }
    if (retrace::debug && currentContext && !currentContext->insideBeginEnd) {
        glretrace::checkGlError(call);
    }
}

static void retrace_glUniform3fv(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    GLint location;
    GLint program = _getActiveProgram();
    location = (call.arg(0)).toSInt();
    if (retrace::verbosity >= 2) {
        std::cout << "location " << size_t(location) << " <- " << size_t(_location_map[program].lookupUniformLocation(location)) << "\n";
    }
    location = _location_map[program].lookupUniformLocation(location);

    GLsizei count;
    count = (call.arg(1)).toSInt();

    GLfloat * value;
    value = _allocator.allocArray<GLfloat>(&call.arg(2));
    const trace::Array *_a_GLfloat8_0 = (call.arg(2)).toArray();
    if (_a_GLfloat8_0) {
        for (size_t _jGLfloat8 = 0; _jGLfloat8 < _a_GLfloat8_0->values.size(); ++_jGLfloat8) {
    value[_jGLfloat8] = (*_a_GLfloat8_0->values[_jGLfloat8]).toFloat();
        }
    }

    glretrace::Context *currentContext = glretrace::getCurrentContext();
    if (!currentContext) {
        if (retrace::debug) {
            retrace::warning(call) << "no current context\n";
        }
#ifndef _WIN32
        return;
#endif
    }
    if (currentContext && !currentContext->insideList && !currentContext->insideBeginEnd && retrace::profiling) {
        glretrace::beginProfile(call, false);
    }
    glUniform3fv(location, count, value);
    if (currentContext && !currentContext->insideList && !currentContext->insideBeginEnd && retrace::profiling) {
        glretrace::endProfile(call, false);
    }
    if (retrace::debug && currentContext && !currentContext->insideBeginEnd) {
        glretrace::checkGlError(call);
    }
}

static void retrace_glUniform4fv(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    GLint location;
    GLint program = _getActiveProgram();
    location = (call.arg(0)).toSInt();
    if (retrace::verbosity >= 2) {
        std::cout << "location " << size_t(location) << " <- " << size_t(_location_map[program].lookupUniformLocation(location)) << "\n";
    }
    location = _location_map[program].lookupUniformLocation(location);

    GLsizei count;
    count = (call.arg(1)).toSInt();

    GLfloat * value;
    value = _allocator.allocArray<GLfloat>(&call.arg(2));
    const trace::Array *_a_GLfloat9_0 = (call.arg(2)).toArray();
    if (_a_GLfloat9_0) {
        for (size_t _jGLfloat9 = 0; _jGLfloat9 < _a_GLfloat9_0->values.size(); ++_jGLfloat9) {
    value[_jGLfloat9] = (*_a_GLfloat9_0->values[_jGLfloat9]).toFloat();
        }
    }

    glretrace::Context *currentContext = glretrace::getCurrentContext();
    if (!currentContext) {
        if (retrace::debug) {
            retrace::warning(call) << "no current context\n";
        }
#ifndef _WIN32
        return;
#endif
    }
    if (currentContext && !currentContext->insideList && !currentContext->insideBeginEnd && retrace::profiling) {
        glretrace::beginProfile(call, false);
    }
    glUniform4fv(location, count, value);
    if (currentContext && !currentContext->insideList && !currentContext->insideBeginEnd && retrace::profiling) {
        glretrace::endProfile(call, false);
    }
    if (retrace::debug && currentContext && !currentContext->insideBeginEnd) {
        glretrace::checkGlError(call);
    }
}

static void retrace_glUniform1iv(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    GLint location;
    GLint program = _getActiveProgram();
    location = (call.arg(0)).toSInt();
    if (retrace::verbosity >= 2) {
        std::cout << "location " << size_t(location) << " <- " << size_t(_location_map[program].lookupUniformLocation(location)) << "\n";
    }
    location = _location_map[program].lookupUniformLocation(location);

    GLsizei count;
    count = (call.arg(1)).toSInt();

    GLint * value;
    value = _allocator.allocArray<GLint>(&call.arg(2));
    const trace::Array *_a_GLint16_0 = (call.arg(2)).toArray();
    if (_a_GLint16_0) {
        for (size_t _jGLint16 = 0; _jGLint16 < _a_GLint16_0->values.size(); ++_jGLint16) {
    value[_jGLint16] = (*_a_GLint16_0->values[_jGLint16]).toSInt();
        }
    }

    glretrace::Context *currentContext = glretrace::getCurrentContext();
    if (!currentContext) {
        if (retrace::debug) {
            retrace::warning(call) << "no current context\n";
        }
#ifndef _WIN32
        return;
#endif
    }
    if (currentContext && !currentContext->insideList && !currentContext->insideBeginEnd && retrace::profiling) {
        glretrace::beginProfile(call, false);
    }
    glUniform1iv(location, count, value);
    if (currentContext && !currentContext->insideList && !currentContext->insideBeginEnd && retrace::profiling) {
        glretrace::endProfile(call, false);
    }
    if (retrace::debug && currentContext && !currentContext->insideBeginEnd) {
        glretrace::checkGlError(call);
    }
}

static void retrace_glUniform2iv(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    GLint location;
    GLint program = _getActiveProgram();
    location = (call.arg(0)).toSInt();
    if (retrace::verbosity >= 2) {
        std::cout << "location " << size_t(location) << " <- " << size_t(_location_map[program].lookupUniformLocation(location)) << "\n";
    }
    location = _location_map[program].lookupUniformLocation(location);

    GLsizei count;
    count = (call.arg(1)).toSInt();

    GLint * value;
    value = _allocator.allocArray<GLint>(&call.arg(2));
    const trace::Array *_a_GLint17_0 = (call.arg(2)).toArray();
    if (_a_GLint17_0) {
        for (size_t _jGLint17 = 0; _jGLint17 < _a_GLint17_0->values.size(); ++_jGLint17) {
    value[_jGLint17] = (*_a_GLint17_0->values[_jGLint17]).toSInt();
        }
    }

    glretrace::Context *currentContext = glretrace::getCurrentContext();
    if (!currentContext) {
        if (retrace::debug) {
            retrace::warning(call) << "no current context\n";
        }
#ifndef _WIN32
        return;
#endif
    }
    if (currentContext && !currentContext->insideList && !currentContext->insideBeginEnd && retrace::profiling) {
        glretrace::beginProfile(call, false);
    }
    glUniform2iv(location, count, value);
    if (currentContext && !currentContext->insideList && !currentContext->insideBeginEnd && retrace::profiling) {
        glretrace::endProfile(call, false);
    }
    if (retrace::debug && currentContext && !currentContext->insideBeginEnd) {
        glretrace::checkGlError(call);
    }
}

static void retrace_glUniform3iv(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    GLint location;
    GLint program = _getActiveProgram();
    location = (call.arg(0)).toSInt();
    if (retrace::verbosity >= 2) {
        std::cout << "location " << size_t(location) << " <- " << size_t(_location_map[program].lookupUniformLocation(location)) << "\n";
    }
    location = _location_map[program].lookupUniformLocation(location);

    GLsizei count;
    count = (call.arg(1)).toSInt();

    GLint * value;
    value = _allocator.allocArray<GLint>(&call.arg(2));
    const trace::Array *_a_GLint18_0 = (call.arg(2)).toArray();
    if (_a_GLint18_0) {
        for (size_t _jGLint18 = 0; _jGLint18 < _a_GLint18_0->values.size(); ++_jGLint18) {
    value[_jGLint18] = (*_a_GLint18_0->values[_jGLint18]).toSInt();
        }
    }

    glretrace::Context *currentContext = glretrace::getCurrentContext();
    if (!currentContext) {
        if (retrace::debug) {
            retrace::warning(call) << "no current context\n";
        }
#ifndef _WIN32
        return;
#endif
    }
    if (currentContext && !currentContext->insideList && !currentContext->insideBeginEnd && retrace::profiling) {
        glretrace::beginProfile(call, false);
    }
    glUniform3iv(location, count, value);
    if (currentContext && !currentContext->insideList && !currentContext->insideBeginEnd && retrace::profiling) {
        glretrace::endProfile(call, false);
    }
    if (retrace::debug && currentContext && !currentContext->insideBeginEnd) {
        glretrace::checkGlError(call);
    }
}

static void retrace_glUniform4iv(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    GLint location;
    GLint program = _getActiveProgram();
    location = (call.arg(0)).toSInt();
    if (retrace::verbosity >= 2) {
        std::cout << "location " << size_t(location) << " <- " << size_t(_location_map[program].lookupUniformLocation(location)) << "\n";
    }
    location = _location_map[program].lookupUniformLocation(location);

    GLsizei count;
    count = (call.arg(1)).toSInt();

    GLint * value;
    value = _allocator.allocArray<GLint>(&call.arg(2));
    const trace::Array *_a_GLint19_0 = (call.arg(2)).toArray();
    if (_a_GLint19_0) {
        for (size_t _jGLint19 = 0; _jGLint19 < _a_GLint19_0->values.size(); ++_jGLint19) {
    value[_jGLint19] = (*_a_GLint19_0->values[_jGLint19]).toSInt();
        }
    }

    glretrace::Context *currentContext = glretrace::getCurrentContext();
    if (!currentContext) {
        if (retrace::debug) {
            retrace::warning(call) << "no current context\n";
        }
#ifndef _WIN32
        return;
#endif
    }
    if (currentContext && !currentContext->insideList && !currentContext->insideBeginEnd && retrace::profiling) {
        glretrace::beginProfile(call, false);
    }
    glUniform4iv(location, count, value);
    if (currentContext && !currentContext->insideList && !currentContext->insideBeginEnd && retrace::profiling) {
        glretrace::endProfile(call, false);
    }
    if (retrace::debug && currentContext && !currentContext->insideBeginEnd) {
        glretrace::checkGlError(call);
    }
}

static void retrace_glUniformMatrix2fv(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    GLint location;
    GLint program = _getActiveProgram();
    location = (call.arg(0)).toSInt();
    if (retrace::verbosity >= 2) {
        std::cout << "location " << size_t(location) << " <- " << size_t(_location_map[program].lookupUniformLocation(location)) << "\n";
    }
    location = _location_map[program].lookupUniformLocation(location);

    GLsizei count;
    count = (call.arg(1)).toSInt();

    GLboolean transpose;
    transpose = static_cast<GLboolean>((call.arg(2)).toSInt());

    GLfloat * value;
    value = _allocator.allocArray<GLfloat>(&call.arg(3));
    const trace::Array *_a_GLfloat10_0 = (call.arg(3)).toArray();
    if (_a_GLfloat10_0) {
        for (size_t _jGLfloat10 = 0; _jGLfloat10 < _a_GLfloat10_0->values.size(); ++_jGLfloat10) {
    value[_jGLfloat10] = (*_a_GLfloat10_0->values[_jGLfloat10]).toFloat();
        }
    }

    glretrace::Context *currentContext = glretrace::getCurrentContext();
    if (!currentContext) {
        if (retrace::debug) {
            retrace::warning(call) << "no current context\n";
        }
#ifndef _WIN32
        return;
#endif
    }
    if (currentContext && !currentContext->insideList && !currentContext->insideBeginEnd && retrace::profiling) {
        glretrace::beginProfile(call, false);
    }
    glUniformMatrix2fv(location, count, transpose, value);
    if (currentContext && !currentContext->insideList && !currentContext->insideBeginEnd && retrace::profiling) {
        glretrace::endProfile(call, false);
    }
    if (retrace::debug && currentContext && !currentContext->insideBeginEnd) {
        glretrace::checkGlError(call);
    }
}

static void retrace_glUniformMatrix3fv(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    GLint location;
    GLint program = _getActiveProgram();
    location = (call.arg(0)).toSInt();
    if (retrace::verbosity >= 2) {
        std::cout << "location " << size_t(location) << " <- " << size_t(_location_map[program].lookupUniformLocation(location)) << "\n";
    }
    location = _location_map[program].lookupUniformLocation(location);

    GLsizei count;
    count = (call.arg(1)).toSInt();

    GLboolean transpose;
    transpose = static_cast<GLboolean>((call.arg(2)).toSInt());

    GLfloat * value;
    value = _allocator.allocArray<GLfloat>(&call.arg(3));
    const trace::Array *_a_GLfloat11_0 = (call.arg(3)).toArray();
    if (_a_GLfloat11_0) {
        for (size_t _jGLfloat11 = 0; _jGLfloat11 < _a_GLfloat11_0->values.size(); ++_jGLfloat11) {
    value[_jGLfloat11] = (*_a_GLfloat11_0->values[_jGLfloat11]).toFloat();
        }
    }

    glretrace::Context *currentContext = glretrace::getCurrentContext();
    if (!currentContext) {
        if (retrace::debug) {
            retrace::warning(call) << "no current context\n";
        }
#ifndef _WIN32
        return;
#endif
    }
    if (currentContext && !currentContext->insideList && !currentContext->insideBeginEnd && retrace::profiling) {
        glretrace::beginProfile(call, false);
    }
    glUniformMatrix3fv(location, count, transpose, value);
    if (currentContext && !currentContext->insideList && !currentContext->insideBeginEnd && retrace::profiling) {
        glretrace::endProfile(call, false);
    }
    if (retrace::debug && currentContext && !currentContext->insideBeginEnd) {
        glretrace::checkGlError(call);
    }
}

static void retrace_glUniformMatrix4fv(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    GLint location;
    GLint program = _getActiveProgram();
    location = (call.arg(0)).toSInt();
    if (retrace::verbosity >= 2) {
        std::cout << "location " << size_t(location) << " <- " << size_t(_location_map[program].lookupUniformLocation(location)) << "\n";
    }
    location = _location_map[program].lookupUniformLocation(location);

    GLsizei count;
    count = (call.arg(1)).toSInt();

    GLboolean transpose;
    transpose = static_cast<GLboolean>((call.arg(2)).toSInt());

    GLfloat * value;
    value = _allocator.allocArray<GLfloat>(&call.arg(3));
    const trace::Array *_a_GLfloat12_0 = (call.arg(3)).toArray();
    if (_a_GLfloat12_0) {
        for (size_t _jGLfloat12 = 0; _jGLfloat12 < _a_GLfloat12_0->values.size(); ++_jGLfloat12) {
    value[_jGLfloat12] = (*_a_GLfloat12_0->values[_jGLfloat12]).toFloat();
        }
    }

    glretrace::Context *currentContext = glretrace::getCurrentContext();
    if (!currentContext) {
        if (retrace::debug) {
            retrace::warning(call) << "no current context\n";
        }
#ifndef _WIN32
        return;
#endif
    }
    if (currentContext && !currentContext->insideList && !currentContext->insideBeginEnd && retrace::profiling) {
        glretrace::beginProfile(call, false);
    }
    glUniformMatrix4fv(location, count, transpose, value);
    if (currentContext && !currentContext->insideList && !currentContext->insideBeginEnd && retrace::profiling) {
        glretrace::endProfile(call, false);
    }
    if (retrace::debug && currentContext && !currentContext->insideBeginEnd) {
        glretrace::checkGlError(call);
    }
}

static void retrace_glValidateProgram(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    GLuint program;
    program = (call.arg(0)).toUInt();
    if (retrace::verbosity >= 2) {
        std::cout << "program " << size_t(program) << " <- " << size_t(_program_map[program]) << "\n";
    }
if (glretrace::supportsARBShaderObjects) {
    program = _handleARB_map[program];
} else {
    program = _program_map[program];
}

    glretrace::Context *currentContext = glretrace::getCurrentContext();
    if (!currentContext) {
        if (retrace::debug) {
            retrace::warning(call) << "no current context\n";
        }
#ifndef _WIN32
        return;
#endif
    }
    if (currentContext && !currentContext->insideList && !currentContext->insideBeginEnd && retrace::profiling) {
        glretrace::beginProfile(call, false);
    }
    glValidateProgram(program);
    if (currentContext && !currentContext->insideList && !currentContext->insideBeginEnd && retrace::profiling) {
        glretrace::endProfile(call, false);
    }
    if (retrace::debug && currentContext && !currentContext->insideBeginEnd) {
        glretrace::checkGlError(call);
    }
}

static void retrace_glVertexAttrib1f(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    GLuint index;
    index = (call.arg(0)).toUInt();

    GLfloat x;
    x = (call.arg(1)).toFloat();

    glretrace::Context *currentContext = glretrace::getCurrentContext();
    if (!currentContext) {
        if (retrace::debug) {
            retrace::warning(call) << "no current context\n";
        }
#ifndef _WIN32
        return;
#endif
    }
    if (currentContext && !currentContext->insideList && !currentContext->insideBeginEnd && retrace::profiling) {
        glretrace::beginProfile(call, false);
    }
    glVertexAttrib1f(index, x);
    if (currentContext && !currentContext->insideList && !currentContext->insideBeginEnd && retrace::profiling) {
        glretrace::endProfile(call, false);
    }
    if (retrace::debug && currentContext && !currentContext->insideBeginEnd) {
        glretrace::checkGlError(call);
    }
}

static void retrace_glVertexAttrib1fv(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    GLuint index;
    index = (call.arg(0)).toUInt();

    GLfloat * v;
    v = _allocator.allocArray<GLfloat>(&call.arg(1));
    if (v) {
        const trace::Array *_a_PGLfloat_0 = (call.arg(1)).toArray();
    v[0] = (*_a_PGLfloat_0->values[0]).toFloat();
    }

    glretrace::Context *currentContext = glretrace::getCurrentContext();
    if (!currentContext) {
        if (retrace::debug) {
            retrace::warning(call) << "no current context\n";
        }
#ifndef _WIN32
        return;
#endif
    }
    if (currentContext && !currentContext->insideList && !currentContext->insideBeginEnd && retrace::profiling) {
        glretrace::beginProfile(call, false);
    }
    glVertexAttrib1fv(index, v);
    if (currentContext && !currentContext->insideList && !currentContext->insideBeginEnd && retrace::profiling) {
        glretrace::endProfile(call, false);
    }
    if (retrace::debug && currentContext && !currentContext->insideBeginEnd) {
        glretrace::checkGlError(call);
    }
}

static void retrace_glVertexAttrib2f(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    GLuint index;
    index = (call.arg(0)).toUInt();

    GLfloat x;
    x = (call.arg(1)).toFloat();

    GLfloat y;
    y = (call.arg(2)).toFloat();

    glretrace::Context *currentContext = glretrace::getCurrentContext();
    if (!currentContext) {
        if (retrace::debug) {
            retrace::warning(call) << "no current context\n";
        }
#ifndef _WIN32
        return;
#endif
    }
    if (currentContext && !currentContext->insideList && !currentContext->insideBeginEnd && retrace::profiling) {
        glretrace::beginProfile(call, false);
    }
    glVertexAttrib2f(index, x, y);
    if (currentContext && !currentContext->insideList && !currentContext->insideBeginEnd && retrace::profiling) {
        glretrace::endProfile(call, false);
    }
    if (retrace::debug && currentContext && !currentContext->insideBeginEnd) {
        glretrace::checkGlError(call);
    }
}

static void retrace_glVertexAttrib2fv(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    GLuint index;
    index = (call.arg(0)).toUInt();

    GLfloat * v;
    v = _allocator.allocArray<GLfloat>(&call.arg(1));
    const trace::Array *_a_GLfloat13_0 = (call.arg(1)).toArray();
    if (_a_GLfloat13_0) {
        for (size_t _jGLfloat13 = 0; _jGLfloat13 < _a_GLfloat13_0->values.size(); ++_jGLfloat13) {
    v[_jGLfloat13] = (*_a_GLfloat13_0->values[_jGLfloat13]).toFloat();
        }
    }

    glretrace::Context *currentContext = glretrace::getCurrentContext();
    if (!currentContext) {
        if (retrace::debug) {
            retrace::warning(call) << "no current context\n";
        }
#ifndef _WIN32
        return;
#endif
    }
    if (currentContext && !currentContext->insideList && !currentContext->insideBeginEnd && retrace::profiling) {
        glretrace::beginProfile(call, false);
    }
    glVertexAttrib2fv(index, v);
    if (currentContext && !currentContext->insideList && !currentContext->insideBeginEnd && retrace::profiling) {
        glretrace::endProfile(call, false);
    }
    if (retrace::debug && currentContext && !currentContext->insideBeginEnd) {
        glretrace::checkGlError(call);
    }
}

static void retrace_glVertexAttrib3f(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    GLuint index;
    index = (call.arg(0)).toUInt();

    GLfloat x;
    x = (call.arg(1)).toFloat();

    GLfloat y;
    y = (call.arg(2)).toFloat();

    GLfloat z;
    z = (call.arg(3)).toFloat();

    glretrace::Context *currentContext = glretrace::getCurrentContext();
    if (!currentContext) {
        if (retrace::debug) {
            retrace::warning(call) << "no current context\n";
        }
#ifndef _WIN32
        return;
#endif
    }
    if (currentContext && !currentContext->insideList && !currentContext->insideBeginEnd && retrace::profiling) {
        glretrace::beginProfile(call, false);
    }
    glVertexAttrib3f(index, x, y, z);
    if (currentContext && !currentContext->insideList && !currentContext->insideBeginEnd && retrace::profiling) {
        glretrace::endProfile(call, false);
    }
    if (retrace::debug && currentContext && !currentContext->insideBeginEnd) {
        glretrace::checkGlError(call);
    }
}

static void retrace_glVertexAttrib3fv(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    GLuint index;
    index = (call.arg(0)).toUInt();

    GLfloat * v;
    v = _allocator.allocArray<GLfloat>(&call.arg(1));
    const trace::Array *_a_GLfloat14_0 = (call.arg(1)).toArray();
    if (_a_GLfloat14_0) {
        for (size_t _jGLfloat14 = 0; _jGLfloat14 < _a_GLfloat14_0->values.size(); ++_jGLfloat14) {
    v[_jGLfloat14] = (*_a_GLfloat14_0->values[_jGLfloat14]).toFloat();
        }
    }

    glretrace::Context *currentContext = glretrace::getCurrentContext();
    if (!currentContext) {
        if (retrace::debug) {
            retrace::warning(call) << "no current context\n";
        }
#ifndef _WIN32
        return;
#endif
    }
    if (currentContext && !currentContext->insideList && !currentContext->insideBeginEnd && retrace::profiling) {
        glretrace::beginProfile(call, false);
    }
    glVertexAttrib3fv(index, v);
    if (currentContext && !currentContext->insideList && !currentContext->insideBeginEnd && retrace::profiling) {
        glretrace::endProfile(call, false);
    }
    if (retrace::debug && currentContext && !currentContext->insideBeginEnd) {
        glretrace::checkGlError(call);
    }
}

static void retrace_glVertexAttrib4f(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    GLuint index;
    index = (call.arg(0)).toUInt();

    GLfloat x;
    x = (call.arg(1)).toFloat();

    GLfloat y;
    y = (call.arg(2)).toFloat();

    GLfloat z;
    z = (call.arg(3)).toFloat();

    GLfloat w;
    w = (call.arg(4)).toFloat();

    glretrace::Context *currentContext = glretrace::getCurrentContext();
    if (!currentContext) {
        if (retrace::debug) {
            retrace::warning(call) << "no current context\n";
        }
#ifndef _WIN32
        return;
#endif
    }
    if (currentContext && !currentContext->insideList && !currentContext->insideBeginEnd && retrace::profiling) {
        glretrace::beginProfile(call, false);
    }
    glVertexAttrib4f(index, x, y, z, w);
    if (currentContext && !currentContext->insideList && !currentContext->insideBeginEnd && retrace::profiling) {
        glretrace::endProfile(call, false);
    }
    if (retrace::debug && currentContext && !currentContext->insideBeginEnd) {
        glretrace::checkGlError(call);
    }
}

static void retrace_glVertexAttrib4fv(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    GLuint index;
    index = (call.arg(0)).toUInt();

    GLfloat * v;
    v = _allocator.allocArray<GLfloat>(&call.arg(1));
    const trace::Array *_a_GLfloat15_0 = (call.arg(1)).toArray();
    if (_a_GLfloat15_0) {
        for (size_t _jGLfloat15 = 0; _jGLfloat15 < _a_GLfloat15_0->values.size(); ++_jGLfloat15) {
    v[_jGLfloat15] = (*_a_GLfloat15_0->values[_jGLfloat15]).toFloat();
        }
    }

    glretrace::Context *currentContext = glretrace::getCurrentContext();
    if (!currentContext) {
        if (retrace::debug) {
            retrace::warning(call) << "no current context\n";
        }
#ifndef _WIN32
        return;
#endif
    }
    if (currentContext && !currentContext->insideList && !currentContext->insideBeginEnd && retrace::profiling) {
        glretrace::beginProfile(call, false);
    }
    glVertexAttrib4fv(index, v);
    if (currentContext && !currentContext->insideList && !currentContext->insideBeginEnd && retrace::profiling) {
        glretrace::endProfile(call, false);
    }
    if (retrace::debug && currentContext && !currentContext->insideBeginEnd) {
        glretrace::checkGlError(call);
    }
}

static void retrace_glVertexAttribPointer(trace::Call &call) {
    if (retrace::parser->getVersion() < 1) {
        GLint _array_buffer = 0;
        glGetIntegerv(GL_ARRAY_BUFFER_BINDING, &_array_buffer);
        if (!_array_buffer) {
    if (retrace::verbosity >= 0) {
        retrace::unsupported(call);
    }
    return;
        }
    }
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    GLuint index;
    index = (call.arg(0)).toUInt();

    GLint size;
    size = static_cast<GLint>((call.arg(1)).toSInt());

    GLenum type;
    type = static_cast<GLenum>((call.arg(2)).toSInt());

    GLboolean normalized;
    normalized = static_cast<GLboolean>((call.arg(3)).toSInt());

    GLsizei stride;
    stride = (call.arg(4)).toSInt();

    const GLvoid * pointer;
    pointer = static_cast<const GLvoid *>(retrace::toPointer(call.arg(5), true));

    glretrace::Context *currentContext = glretrace::getCurrentContext();
    if (!currentContext) {
        if (retrace::debug) {
            retrace::warning(call) << "no current context\n";
        }
#ifndef _WIN32
        return;
#endif
    }
    if (currentContext && !currentContext->insideList && !currentContext->insideBeginEnd && retrace::profiling) {
        glretrace::beginProfile(call, false);
    }
    glVertexAttribPointer(index, size, type, normalized, stride, pointer);
    if (currentContext && !currentContext->insideList && !currentContext->insideBeginEnd && retrace::profiling) {
        glretrace::endProfile(call, false);
    }
    if (retrace::debug && currentContext && !currentContext->insideBeginEnd) {
        glretrace::checkGlError(call);
    }
}

static void retrace_glReleaseShaderCompiler(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    glretrace::Context *currentContext = glretrace::getCurrentContext();
    if (!currentContext) {
        if (retrace::debug) {
            retrace::warning(call) << "no current context\n";
        }
#ifndef _WIN32
        return;
#endif
    }
    if (currentContext && !currentContext->insideList && !currentContext->insideBeginEnd && retrace::profiling) {
        glretrace::beginProfile(call, false);
    }
    glReleaseShaderCompiler();
    if (currentContext && !currentContext->insideList && !currentContext->insideBeginEnd && retrace::profiling) {
        glretrace::endProfile(call, false);
    }
    if (retrace::debug && currentContext && !currentContext->insideBeginEnd) {
        glretrace::checkGlError(call);
    }
}

static void retrace_glShaderBinary(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    GLsizei count;
    count = (call.arg(0)).toSInt();

    GLuint * shaders;
    shaders = _allocator.allocArray<GLuint>(&call.arg(1));
    const trace::Array *_a_GLuint12_0 = (call.arg(1)).toArray();
    if (_a_GLuint12_0) {
        for (size_t _jGLuint12 = 0; _jGLuint12 < _a_GLuint12_0->values.size(); ++_jGLuint12) {
    shaders[_jGLuint12] = (*_a_GLuint12_0->values[_jGLuint12]).toUInt();
        }
    }

    GLenum binaryformat;
    binaryformat = static_cast<GLenum>((call.arg(2)).toSInt());

    GLvoid * binary;
    binary = static_cast<GLvoid *>((call.arg(3)).toPointer());

    GLsizei length;
    length = (call.arg(4)).toSInt();

    glretrace::Context *currentContext = glretrace::getCurrentContext();
    if (!currentContext) {
        if (retrace::debug) {
            retrace::warning(call) << "no current context\n";
        }
#ifndef _WIN32
        return;
#endif
    }
    if (currentContext && !currentContext->insideList && !currentContext->insideBeginEnd && retrace::profiling) {
        glretrace::beginProfile(call, false);
    }
    glShaderBinary(count, shaders, binaryformat, binary, length);
    if (currentContext && !currentContext->insideList && !currentContext->insideBeginEnd && retrace::profiling) {
        glretrace::endProfile(call, false);
    }
    if (retrace::debug && currentContext && !currentContext->insideBeginEnd) {
        glretrace::checkGlError(call);
    }
}

static void retrace_glDepthRangef(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    GLfloat n;
    n = (call.arg(0)).toFloat();

    GLfloat f;
    f = (call.arg(1)).toFloat();

    glretrace::Context *currentContext = glretrace::getCurrentContext();
    if (!currentContext) {
        if (retrace::debug) {
            retrace::warning(call) << "no current context\n";
        }
#ifndef _WIN32
        return;
#endif
    }
    if (currentContext && !currentContext->insideList && !currentContext->insideBeginEnd && retrace::profiling) {
        glretrace::beginProfile(call, false);
    }
    glDepthRangef(n, f);
    if (currentContext && !currentContext->insideList && !currentContext->insideBeginEnd && retrace::profiling) {
        glretrace::endProfile(call, false);
    }
    if (retrace::debug && currentContext && !currentContext->insideBeginEnd) {
        glretrace::checkGlError(call);
    }
}

static void retrace_glClearDepthf(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    GLfloat d;
    d = (call.arg(0)).toFloat();

    glretrace::Context *currentContext = glretrace::getCurrentContext();
    if (!currentContext) {
        if (retrace::debug) {
            retrace::warning(call) << "no current context\n";
        }
#ifndef _WIN32
        return;
#endif
    }
    if (currentContext && !currentContext->insideList && !currentContext->insideBeginEnd && retrace::profiling) {
        glretrace::beginProfile(call, false);
    }
    glClearDepthf(d);
    if (currentContext && !currentContext->insideList && !currentContext->insideBeginEnd && retrace::profiling) {
        glretrace::endProfile(call, false);
    }
    if (retrace::debug && currentContext && !currentContext->insideBeginEnd) {
        glretrace::checkGlError(call);
    }
}

static void retrace_glBindRenderbuffer(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    GLenum target;
    target = static_cast<GLenum>((call.arg(0)).toSInt());

    GLuint renderbuffer;
    renderbuffer = (call.arg(1)).toUInt();
    if (retrace::verbosity >= 2) {
        std::cout << "renderbuffer " << size_t(renderbuffer) << " <- " << size_t(_renderbuffer_map[renderbuffer]) << "\n";
    }
    renderbuffer = _renderbuffer_map[renderbuffer];

    glretrace::Context *currentContext = glretrace::getCurrentContext();
    if (!currentContext) {
        if (retrace::debug) {
            retrace::warning(call) << "no current context\n";
        }
#ifndef _WIN32
        return;
#endif
    }
    if (currentContext && !currentContext->insideList && !currentContext->insideBeginEnd && retrace::profiling) {
        glretrace::beginProfile(call, false);
    }
    glBindRenderbuffer(target, renderbuffer);
    if (currentContext && !currentContext->insideList && !currentContext->insideBeginEnd && retrace::profiling) {
        glretrace::endProfile(call, false);
    }
    if (retrace::debug && currentContext && !currentContext->insideBeginEnd) {
        glretrace::checkGlError(call);
    }
}

static void retrace_glDeleteRenderbuffers(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    GLsizei n;
    n = (call.arg(0)).toSInt();

    GLuint * renderbuffers;
    renderbuffers = _allocator.allocArray<GLuint>(&call.arg(1));
    const trace::Array *_a_GLuint13_0 = (call.arg(1)).toArray();
    if (_a_GLuint13_0) {
        for (size_t _jGLuint13 = 0; _jGLuint13 < _a_GLuint13_0->values.size(); ++_jGLuint13) {
    renderbuffers[_jGLuint13] = (*_a_GLuint13_0->values[_jGLuint13]).toUInt();
    if (retrace::verbosity >= 2) {
        std::cout << "renderbuffer " << size_t(renderbuffers[_jGLuint13]) << " <- " << size_t(_renderbuffer_map[renderbuffers[_jGLuint13]]) << "\n";
    }
    renderbuffers[_jGLuint13] = _renderbuffer_map[renderbuffers[_jGLuint13]];
        }
    }

    glretrace::Context *currentContext = glretrace::getCurrentContext();
    if (!currentContext) {
        if (retrace::debug) {
            retrace::warning(call) << "no current context\n";
        }
#ifndef _WIN32
        return;
#endif
    }
    if (currentContext && !currentContext->insideList && !currentContext->insideBeginEnd && retrace::profiling) {
        glretrace::beginProfile(call, false);
    }
    glDeleteRenderbuffers(n, renderbuffers);
    if (currentContext && !currentContext->insideList && !currentContext->insideBeginEnd && retrace::profiling) {
        glretrace::endProfile(call, false);
    }
    if (retrace::debug && currentContext && !currentContext->insideBeginEnd) {
        glretrace::checkGlError(call);
    }
}

static void retrace_glGenRenderbuffers(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    GLsizei n;
    n = (call.arg(0)).toSInt();

    GLuint * renderbuffers;
    renderbuffers = _allocator.allocArray<GLuint>(&call.arg(1));

    glretrace::Context *currentContext = glretrace::getCurrentContext();
    if (!currentContext) {
        if (retrace::debug) {
            retrace::warning(call) << "no current context\n";
        }
#ifndef _WIN32
        return;
#endif
    }
    if (currentContext && !currentContext->insideList && !currentContext->insideBeginEnd && retrace::profiling) {
        glretrace::beginProfile(call, false);
    }
    glGenRenderbuffers(n, renderbuffers);
    if (currentContext && !currentContext->insideList && !currentContext->insideBeginEnd && retrace::profiling) {
        glretrace::endProfile(call, false);
    }
    if (retrace::debug && currentContext && !currentContext->insideBeginEnd) {
        glretrace::checkGlError(call);
    }
    const trace::Array *_aGLuint15 = (call.arg(1)).toArray();
    if (_aGLuint15) {
        for (size_t _jGLuint15 = 0; _jGLuint15 < _aGLuint15->values.size(); ++_jGLuint15) {
    GLuint _origResult;
    _origResult = (*_aGLuint15->values[_jGLuint15]).toUInt();
    _renderbuffer_map[_origResult] = renderbuffers[_jGLuint15];
    if (retrace::verbosity >= 2) {
        std::cout << "renderbuffer " << _origResult << " -> " << renderbuffers[_jGLuint15] << "\n";
    }
        }
    }
}

static void retrace_glRenderbufferStorage(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    GLenum target;
    target = static_cast<GLenum>((call.arg(0)).toSInt());

    GLenum internalformat;
    internalformat = static_cast<GLenum>((call.arg(1)).toSInt());

    GLsizei width;
    width = (call.arg(2)).toSInt();

    GLsizei height;
    height = (call.arg(3)).toSInt();

    glretrace::Context *currentContext = glretrace::getCurrentContext();
    if (!currentContext) {
        if (retrace::debug) {
            retrace::warning(call) << "no current context\n";
        }
#ifndef _WIN32
        return;
#endif
    }
    if (currentContext && !currentContext->insideList && !currentContext->insideBeginEnd && retrace::profiling) {
        glretrace::beginProfile(call, false);
    }
    glRenderbufferStorage(target, internalformat, width, height);
    if (currentContext && !currentContext->insideList && !currentContext->insideBeginEnd && retrace::profiling) {
        glretrace::endProfile(call, false);
    }
    if (retrace::debug && currentContext && !currentContext->insideBeginEnd) {
        glretrace::checkGlError(call);
    }
}

static void retrace_glBindFramebuffer(trace::Call &call) {
    assert(call.flags & trace::CALL_FLAG_SWAP_RENDERTARGET);
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    GLenum target;
    target = static_cast<GLenum>((call.arg(0)).toSInt());

    GLuint framebuffer;
    framebuffer = (call.arg(1)).toUInt();
    if (retrace::verbosity >= 2) {
        std::cout << "framebuffer " << size_t(framebuffer) << " <- " << size_t(_framebuffer_map[framebuffer]) << "\n";
    }
    framebuffer = _framebuffer_map[framebuffer];

    glretrace::Context *currentContext = glretrace::getCurrentContext();
    if (!currentContext) {
        if (retrace::debug) {
            retrace::warning(call) << "no current context\n";
        }
#ifndef _WIN32
        return;
#endif
    }
    if (currentContext && !currentContext->insideList && !currentContext->insideBeginEnd && retrace::profiling) {
        glretrace::beginProfile(call, false);
    }
    glBindFramebuffer(target, framebuffer);
    if (currentContext && !currentContext->insideList && !currentContext->insideBeginEnd && retrace::profiling) {
        glretrace::endProfile(call, false);
    }
    if (retrace::debug && currentContext && !currentContext->insideBeginEnd) {
        glretrace::checkGlError(call);
    }
}

static void retrace_glDeleteFramebuffers(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    GLsizei n;
    n = (call.arg(0)).toSInt();

    GLuint * framebuffers;
    framebuffers = _allocator.allocArray<GLuint>(&call.arg(1));
    const trace::Array *_a_GLuint16_0 = (call.arg(1)).toArray();
    if (_a_GLuint16_0) {
        for (size_t _jGLuint16 = 0; _jGLuint16 < _a_GLuint16_0->values.size(); ++_jGLuint16) {
    framebuffers[_jGLuint16] = (*_a_GLuint16_0->values[_jGLuint16]).toUInt();
    if (retrace::verbosity >= 2) {
        std::cout << "framebuffer " << size_t(framebuffers[_jGLuint16]) << " <- " << size_t(_framebuffer_map[framebuffers[_jGLuint16]]) << "\n";
    }
    framebuffers[_jGLuint16] = _framebuffer_map[framebuffers[_jGLuint16]];
        }
    }

    glretrace::Context *currentContext = glretrace::getCurrentContext();
    if (!currentContext) {
        if (retrace::debug) {
            retrace::warning(call) << "no current context\n";
        }
#ifndef _WIN32
        return;
#endif
    }
    if (currentContext && !currentContext->insideList && !currentContext->insideBeginEnd && retrace::profiling) {
        glretrace::beginProfile(call, false);
    }
    glDeleteFramebuffers(n, framebuffers);
    if (currentContext && !currentContext->insideList && !currentContext->insideBeginEnd && retrace::profiling) {
        glretrace::endProfile(call, false);
    }
    if (retrace::debug && currentContext && !currentContext->insideBeginEnd) {
        glretrace::checkGlError(call);
    }
}

static void retrace_glGenFramebuffers(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    GLsizei n;
    n = (call.arg(0)).toSInt();

    GLuint * framebuffers;
    framebuffers = _allocator.allocArray<GLuint>(&call.arg(1));

    glretrace::Context *currentContext = glretrace::getCurrentContext();
    if (!currentContext) {
        if (retrace::debug) {
            retrace::warning(call) << "no current context\n";
        }
#ifndef _WIN32
        return;
#endif
    }
    if (currentContext && !currentContext->insideList && !currentContext->insideBeginEnd && retrace::profiling) {
        glretrace::beginProfile(call, false);
    }
    glGenFramebuffers(n, framebuffers);
    if (currentContext && !currentContext->insideList && !currentContext->insideBeginEnd && retrace::profiling) {
        glretrace::endProfile(call, false);
    }
    if (retrace::debug && currentContext && !currentContext->insideBeginEnd) {
        glretrace::checkGlError(call);
    }
    const trace::Array *_aGLuint18 = (call.arg(1)).toArray();
    if (_aGLuint18) {
        for (size_t _jGLuint18 = 0; _jGLuint18 < _aGLuint18->values.size(); ++_jGLuint18) {
    GLuint _origResult;
    _origResult = (*_aGLuint18->values[_jGLuint18]).toUInt();
    _framebuffer_map[_origResult] = framebuffers[_jGLuint18];
    if (retrace::verbosity >= 2) {
        std::cout << "framebuffer " << _origResult << " -> " << framebuffers[_jGLuint18] << "\n";
    }
        }
    }
}

static void retrace_glCheckFramebufferStatus(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    GLenum target;
    target = static_cast<GLenum>((call.arg(0)).toSInt());

    GLenum _result;
    glretrace::Context *currentContext = glretrace::getCurrentContext();
    if (!currentContext) {
        if (retrace::debug) {
            retrace::warning(call) << "no current context\n";
        }
#ifndef _WIN32
        return;
#endif
    }
    if (currentContext && !currentContext->insideList && !currentContext->insideBeginEnd && retrace::profiling) {
        glretrace::beginProfile(call, false);
    }
    _result = glCheckFramebufferStatus(target);
    (void)_result;
    if (currentContext && !currentContext->insideList && !currentContext->insideBeginEnd && retrace::profiling) {
        glretrace::endProfile(call, false);
    }
    if (retrace::debug && currentContext && !currentContext->insideBeginEnd) {
        glretrace::checkGlError(call);
    GLint _origResult = call.ret->toSInt();
    if (_origResult == GL_FRAMEBUFFER_COMPLETE &&
        _result != GL_FRAMEBUFFER_COMPLETE) {
        // TODO akasi
        //retrace::warning(call) << "incomplete framebuffer (" << glstate::enumToString(_result) << ")\n";
    }
    }
}

static void retrace_glFramebufferTexture2D(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    GLenum target;
    target = static_cast<GLenum>((call.arg(0)).toSInt());

    GLenum attachment;
    attachment = static_cast<GLenum>((call.arg(1)).toSInt());

    GLenum textarget;
    textarget = static_cast<GLenum>((call.arg(2)).toSInt());

    GLuint texture;
    texture = (call.arg(3)).toUInt();
    if (retrace::verbosity >= 2) {
        std::cout << "texture " << size_t(texture) << " <- " << size_t(_texture_map[texture]) << "\n";
    }
    texture = _texture_map[texture];

    GLint level;
    level = (call.arg(4)).toSInt();

    glretrace::Context *currentContext = glretrace::getCurrentContext();
    if (!currentContext) {
        if (retrace::debug) {
            retrace::warning(call) << "no current context\n";
        }
#ifndef _WIN32
        return;
#endif
    }
    if (currentContext && !currentContext->insideList && !currentContext->insideBeginEnd && retrace::profiling) {
        glretrace::beginProfile(call, false);
    }
    glFramebufferTexture2D(target, attachment, textarget, texture, level);
    if (currentContext && !currentContext->insideList && !currentContext->insideBeginEnd && retrace::profiling) {
        glretrace::endProfile(call, false);
    }
    if (retrace::debug && currentContext && !currentContext->insideBeginEnd) {
        glretrace::checkGlError(call);
    }
}

static void retrace_glFramebufferRenderbuffer(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    GLenum target;
    target = static_cast<GLenum>((call.arg(0)).toSInt());

    GLenum attachment;
    attachment = static_cast<GLenum>((call.arg(1)).toSInt());

    GLenum renderbuffertarget;
    renderbuffertarget = static_cast<GLenum>((call.arg(2)).toSInt());

    GLuint renderbuffer;
    renderbuffer = (call.arg(3)).toUInt();
    if (retrace::verbosity >= 2) {
        std::cout << "renderbuffer " << size_t(renderbuffer) << " <- " << size_t(_renderbuffer_map[renderbuffer]) << "\n";
    }
    renderbuffer = _renderbuffer_map[renderbuffer];

    glretrace::Context *currentContext = glretrace::getCurrentContext();
    if (!currentContext) {
        if (retrace::debug) {
            retrace::warning(call) << "no current context\n";
        }
#ifndef _WIN32
        return;
#endif
    }
    if (currentContext && !currentContext->insideList && !currentContext->insideBeginEnd && retrace::profiling) {
        glretrace::beginProfile(call, false);
    }
    glFramebufferRenderbuffer(target, attachment, renderbuffertarget, renderbuffer);
    if (currentContext && !currentContext->insideList && !currentContext->insideBeginEnd && retrace::profiling) {
        glretrace::endProfile(call, false);
    }
    if (retrace::debug && currentContext && !currentContext->insideBeginEnd) {
        glretrace::checkGlError(call);
    }
}

static void retrace_glGenerateMipmap(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    GLenum target;
    target = static_cast<GLenum>((call.arg(0)).toSInt());

    glretrace::Context *currentContext = glretrace::getCurrentContext();
    if (!currentContext) {
        if (retrace::debug) {
            retrace::warning(call) << "no current context\n";
        }
#ifndef _WIN32
        return;
#endif
    }
    if (currentContext && !currentContext->insideList && !currentContext->insideBeginEnd && retrace::profiling) {
        glretrace::beginProfile(call, false);
    }
    glGenerateMipmap(target);
    if (currentContext && !currentContext->insideList && !currentContext->insideBeginEnd && retrace::profiling) {
        glretrace::endProfile(call, false);
    }
    if (retrace::debug && currentContext && !currentContext->insideBeginEnd) {
        glretrace::checkGlError(call);
    }
}

const retrace::Entry glretrace::gl_callbacks[] = {
    {"glCullFace", &retrace_glCullFace},
    {"glFrontFace", &retrace_glFrontFace},
    {"glHint", &retrace_glHint},
    {"glLineWidth", &retrace_glLineWidth},
    {"glScissor", &retrace_glScissor},
    {"glTexParameterf", &retrace_glTexParameterf},
    {"glTexParameterfv", &retrace_glTexParameterfv},
    {"glTexParameteri", &retrace_glTexParameteri},
    {"glTexParameteriv", &retrace_glTexParameteriv},
    {"glTexImage2D", &retrace_glTexImage2D},
    {"glClear", &retrace_glClear},
    {"glClearColor", &retrace_glClearColor},
    {"glClearStencil", &retrace_glClearStencil},
    {"glStencilMask", &retrace_glStencilMask},
    {"glColorMask", &retrace_glColorMask},
    {"glDepthMask", &retrace_glDepthMask},
    {"glDisable", &retrace_glDisable},
    {"glEnable", &retrace_glEnable},
    {"glFinish", &retrace_glFinish},
    {"glFlush", &retrace_glFlush},
    {"glBlendFunc", &retrace_glBlendFunc},
    {"glStencilFunc", &retrace_glStencilFunc},
    {"glStencilOp", &retrace_glStencilOp},
    {"glDepthFunc", &retrace_glDepthFunc},
    {"glPixelStorei", &retrace_glPixelStorei},
    {"glReadPixels", &retrace_glReadPixels},
    {"glGetBooleanv", &retrace::ignore},
    {"glGetError", &retrace::ignore},
    {"glGetFloatv", &retrace::ignore},
    {"glGetIntegerv", &retrace::ignore},
    {"glGetString", &retrace::ignore},
    {"glGetTexParameterfv", &retrace::ignore},
    {"glGetTexParameteriv", &retrace::ignore},
    {"glIsEnabled", &retrace::ignore},
    {"glViewport", &retrace_glViewport},
    {"glDrawArrays", &retrace_glDrawArrays},
    {"glDrawElements", &retrace_glDrawElements},
    {"glPolygonOffset", &retrace_glPolygonOffset},
    {"glCopyTexImage2D", &retrace_glCopyTexImage2D},
    {"glCopyTexSubImage2D", &retrace_glCopyTexSubImage2D},
    {"glTexSubImage2D", &retrace_glTexSubImage2D},
    {"glBindTexture", &retrace_glBindTexture},
    {"glDeleteTextures", &retrace_glDeleteTextures},
    {"glGenTextures", &retrace_glGenTextures},
    {"glIsTexture", &retrace::ignore},
    {"glBlendColor", &retrace_glBlendColor},
    {"glBlendEquation", &retrace_glBlendEquation},
    {"glActiveTexture", &retrace_glActiveTexture},
    {"glSampleCoverage", &retrace_glSampleCoverage},
    {"glCompressedTexImage2D", &retrace_glCompressedTexImage2D},
    {"glCompressedTexSubImage2D", &retrace_glCompressedTexSubImage2D},
    {"glBlendFuncSeparate", &retrace_glBlendFuncSeparate},
    {"glBindBuffer", &retrace_glBindBuffer},
    {"glDeleteBuffers", &retrace_glDeleteBuffers},
    {"glGenBuffers", &retrace_glGenBuffers},
    {"glIsBuffer", &retrace::ignore},
    {"glBufferData", &retrace_glBufferData},
    {"glBufferSubData", &retrace_glBufferSubData},
    {"glGetBufferParameteriv", &retrace::ignore},
    {"glBlendEquationSeparate", &retrace_glBlendEquationSeparate},
    {"glStencilOpSeparate", &retrace_glStencilOpSeparate},
    {"glStencilFuncSeparate", &retrace_glStencilFuncSeparate},
    {"glStencilMaskSeparate", &retrace_glStencilMaskSeparate},
    {"glAttachShader", &retrace_glAttachShader},
    {"glBindAttribLocation", &retrace_glBindAttribLocation},
    {"glCompileShader", &retrace_glCompileShader},
    {"glCreateProgram", &retrace_glCreateProgram},
    {"glCreateShader", &retrace_glCreateShader},
    {"glDeleteProgram", &retrace_glDeleteProgram},
    {"glDeleteShader", &retrace_glDeleteShader},
    {"glDetachShader", &retrace_glDetachShader},
    {"glDisableVertexAttribArray", &retrace_glDisableVertexAttribArray},
    {"glEnableVertexAttribArray", &retrace_glEnableVertexAttribArray},
    {"glGetActiveAttrib", &retrace::ignore},
    {"glGetActiveUniform", &retrace::ignore},
    {"glGetAttachedShaders", &retrace::ignore},
    {"glGetAttribLocation", &retrace_glGetAttribLocation},
    {"glGetProgramiv", &retrace::ignore},
    {"glGetProgramInfoLog", &retrace::ignore},
    {"glGetShaderiv", &retrace::ignore},
    {"glGetShaderInfoLog", &retrace::ignore},
    {"glGetShaderSource", &retrace::ignore},
    {"glGetUniformLocation", &retrace_glGetUniformLocation},
    {"glGetUniformfv", &retrace::ignore},
    {"glGetUniformiv", &retrace::ignore},
    {"glGetVertexAttribfv", &retrace::ignore},
    {"glGetVertexAttribiv", &retrace::ignore},
    {"glGetVertexAttribPointerv", &retrace::ignore},
    {"glIsProgram", &retrace::ignore},
    {"glIsShader", &retrace::ignore},
    {"glLinkProgram", &retrace_glLinkProgram},
    {"glShaderSource", &retrace_glShaderSource},
    {"glUseProgram", &retrace_glUseProgram},
    {"glUniform1f", &retrace_glUniform1f},
    {"glUniform2f", &retrace_glUniform2f},
    {"glUniform3f", &retrace_glUniform3f},
    {"glUniform4f", &retrace_glUniform4f},
    {"glUniform1i", &retrace_glUniform1i},
    {"glUniform2i", &retrace_glUniform2i},
    {"glUniform3i", &retrace_glUniform3i},
    {"glUniform4i", &retrace_glUniform4i},
    {"glUniform1fv", &retrace_glUniform1fv},
    {"glUniform2fv", &retrace_glUniform2fv},
    {"glUniform3fv", &retrace_glUniform3fv},
    {"glUniform4fv", &retrace_glUniform4fv},
    {"glUniform1iv", &retrace_glUniform1iv},
    {"glUniform2iv", &retrace_glUniform2iv},
    {"glUniform3iv", &retrace_glUniform3iv},
    {"glUniform4iv", &retrace_glUniform4iv},
    {"glUniformMatrix2fv", &retrace_glUniformMatrix2fv},
    {"glUniformMatrix3fv", &retrace_glUniformMatrix3fv},
    {"glUniformMatrix4fv", &retrace_glUniformMatrix4fv},
    {"glValidateProgram", &retrace_glValidateProgram},
    {"glVertexAttrib1f", &retrace_glVertexAttrib1f},
    {"glVertexAttrib1fv", &retrace_glVertexAttrib1fv},
    {"glVertexAttrib2f", &retrace_glVertexAttrib2f},
    {"glVertexAttrib2fv", &retrace_glVertexAttrib2fv},
    {"glVertexAttrib3f", &retrace_glVertexAttrib3f},
    {"glVertexAttrib3fv", &retrace_glVertexAttrib3fv},
    {"glVertexAttrib4f", &retrace_glVertexAttrib4f},
    {"glVertexAttrib4fv", &retrace_glVertexAttrib4fv},
    {"glVertexAttribPointer", &retrace_glVertexAttribPointer},
    {"glReleaseShaderCompiler", &retrace_glReleaseShaderCompiler},
    {"glShaderBinary", &retrace_glShaderBinary},
    {"glGetShaderPrecisionFormat", &retrace::ignore},
    {"glDepthRangef", &retrace_glDepthRangef},
    {"glClearDepthf", &retrace_glClearDepthf},
    {"glIsRenderbuffer", &retrace::ignore},
    {"glBindRenderbuffer", &retrace_glBindRenderbuffer},
    {"glDeleteRenderbuffers", &retrace_glDeleteRenderbuffers},
    {"glGenRenderbuffers", &retrace_glGenRenderbuffers},
    {"glRenderbufferStorage", &retrace_glRenderbufferStorage},
    {"glGetRenderbufferParameteriv", &retrace::ignore},
    {"glIsFramebuffer", &retrace::ignore},
    {"glBindFramebuffer", &retrace_glBindFramebuffer},
    {"glDeleteFramebuffers", &retrace_glDeleteFramebuffers},
    {"glGenFramebuffers", &retrace_glGenFramebuffers},
    {"glCheckFramebufferStatus", &retrace_glCheckFramebufferStatus},
    {"glFramebufferTexture2D", &retrace_glFramebufferTexture2D},
    {"glFramebufferRenderbuffer", &retrace_glFramebufferRenderbuffer},
    {"glGetFramebufferAttachmentParameteriv", &retrace::ignore},
    {"glGenerateMipmap", &retrace_glGenerateMipmap},
    {NULL, NULL}
};


static GLint
_getActiveProgram(void)
{
    GLint program = -1;
    glretrace::Context *currentContext = glretrace::getCurrentContext();
    if (currentContext && currentContext->insideList) {
        // glUseProgram & glUseProgramObjectARB are display-list-able
        program = _program_map[currentContext->activeProgram];
    } else {
        GLint pipeline = 0;
        if (_pipelineHasBeenBound) {
            glGetIntegerv(GL_PROGRAM_PIPELINE_BINDING, &pipeline);
        }
        if (pipeline) {
            glGetProgramPipelineiv(pipeline, GL_ACTIVE_PROGRAM, &program);
        } else {
            glGetIntegerv(GL_CURRENT_PROGRAM, &program);
        }
    }
    return program;
}

static void
_validateActiveProgram(trace::Call &call)
{
    assert(retrace::debug);

    glretrace::Context *currentContext = glretrace::getCurrentContext();
    if (!currentContext ||
        currentContext->insideList ||
        currentContext->insideBeginEnd ||
        currentContext->wsContext->profile.major < 2) {
        return;
    }

    GLint pipeline = 0;
    if (_pipelineHasBeenBound) {
        glGetIntegerv(GL_PROGRAM_PIPELINE_BINDING, &pipeline);
    }
    if (pipeline) {
        // TODO
    } else {
        GLint program = 0;
        glGetIntegerv(GL_CURRENT_PROGRAM, &program);
        if (!program) {
            return;
        }

        GLint validate_status = GL_FALSE;
        glGetProgramiv(program, GL_VALIDATE_STATUS, &validate_status);
        if (validate_status) {
            // Validate only once
            return;
        }

        glValidateProgram(program);
        glGetProgramiv(program, GL_VALIDATE_STATUS, &validate_status);
        if (!validate_status) {
            retrace::warning(call) << "program validation failed\n";
        }

        GLint info_log_length = 0;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &info_log_length);
        if (info_log_length > 1) {
             GLchar *infoLog = new GLchar[info_log_length];
             glGetProgramInfoLog(program, info_log_length, NULL, infoLog);
             retrace::warning(call) << infoLog << "\n";
             delete [] infoLog;
        }
    }
}
