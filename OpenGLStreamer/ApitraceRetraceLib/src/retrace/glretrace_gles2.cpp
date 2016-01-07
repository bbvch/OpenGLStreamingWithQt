
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
static retrace::map<GLsync> _sync_map;
static std::map<uintptr_t, retrace::map<GLuint> > _array_map;
static retrace::map<GLuint> _query_map;
static retrace::map<GLuint> _pipeline_map;
static retrace::map<GLuint> _sampler_map;
static retrace::map<GLuint> _list_map;
static retrace::map<GLuint> _fence_map;
static retrace::map<GLuint64> _textureHandle_map;
static retrace::map<GLhandleARB> _handleARB_map;

static void retrace_glCullFace(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    GLenum mode;
    mode = static_cast<GLenum>((call.arg(0)).toSInt());

    glCullFace(mode);
}

static void retrace_glFrontFace(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    GLenum mode;
    mode = static_cast<GLenum>((call.arg(0)).toSInt());

    glFrontFace(mode);
}

static void retrace_glHint(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    GLenum target;
    target = static_cast<GLenum>((call.arg(0)).toSInt());

    GLenum mode;
    mode = static_cast<GLenum>((call.arg(1)).toSInt());

    glHint(target, mode);
}

static void retrace_glLineWidth(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    GLfloat width;
    width = (call.arg(0)).toFloat();

    glLineWidth(width);
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

    glScissor(x, y, width, height);
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

    glTexParameterf(target, pname, param);
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
    const trace::Array *_a_GLfloat13_0 = (call.arg(2)).toArray();
    if (_a_GLfloat13_0) {
        for (size_t _jGLfloat13 = 0; _jGLfloat13 < _a_GLfloat13_0->values.size(); ++_jGLfloat13) {
    params[_jGLfloat13] = (*_a_GLfloat13_0->values[_jGLfloat13]).toFloat();
        }
    }

    glTexParameterfv(target, pname, params);
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

    glTexParameteri(target, pname, param);
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
    const trace::Array *_a_GLint20_0 = (call.arg(2)).toArray();
    if (_a_GLint20_0) {
        for (size_t _jGLint20 = 0; _jGLint20 < _a_GLint20_0->values.size(); ++_jGLint20) {
    params[_jGLint20] = (*_a_GLint20_0->values[_jGLint20]).toSInt();
        }
    }

    glTexParameteriv(target, pname, params);
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

    glTexImage2D(target, level, internalformat, width, height, border, format, type, pixels);
}

static void retrace_glClear(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    GLbitfield mask;
    mask = (call.arg(0)).toUInt();

    glClear(mask);
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

    glClearColor(red, green, blue, alpha);
}

static void retrace_glClearStencil(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    GLint s;
    s = (call.arg(0)).toSInt();

    glClearStencil(s);
}

static void retrace_glStencilMask(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    GLuint mask;
    mask = (call.arg(0)).toUInt();

    glStencilMask(mask);
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

    glColorMask(red, green, blue, alpha);
}

static void retrace_glDepthMask(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    GLboolean flag;
    flag = static_cast<GLboolean>((call.arg(0)).toSInt());

    glDepthMask(flag);
}

static void retrace_glDisable(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    GLenum cap;
    cap = static_cast<GLenum>((call.arg(0)).toSInt());

    if (cap == GL_DEBUG_OUTPUT_SYNCHRONOUS_ARB) return;
    glDisable(cap);
}

static void retrace_glEnable(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    GLenum cap;
    cap = static_cast<GLenum>((call.arg(0)).toSInt());

    if (cap == GL_DEBUG_OUTPUT_SYNCHRONOUS_ARB) return;
    glEnable(cap);
}

static void retrace_glFinish(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    glFinish();
    if (!retrace::doubleBuffer) {
        glretrace::frame_complete(call);
    }
}

static void retrace_glFlush(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    glFlush();
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

    glBlendFunc(sfactor, dfactor);
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

    glStencilFunc(func, ref, mask);
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

    glStencilOp(fail, zfail, zpass);
}

static void retrace_glDepthFunc(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    GLenum func;
    func = static_cast<GLenum>((call.arg(0)).toSInt());

    glDepthFunc(func);
}

static void retrace_glPixelStorei(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    GLenum pname;
    pname = static_cast<GLenum>((call.arg(0)).toSInt());

    GLint param;
    param = (call.arg(1)).toSInt();

    glPixelStorei(pname, param);
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

    glReadPixels(x, y, width, height, format, type, pixels);
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
    glViewport(x, y, width, height);
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

    if (retrace::debug) {
        _validateActiveProgram(call);
    }
    glDrawArrays(mode, first, count);
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

    if (retrace::debug) {
        _validateActiveProgram(call);
    }
    glDrawElements(mode, count, type, indices);
    assert(call.flags & trace::CALL_FLAG_RENDER);
}

static void retrace_glPolygonOffset(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    GLfloat factor;
    factor = (call.arg(0)).toFloat();

    GLfloat units;
    units = (call.arg(1)).toFloat();

    glPolygonOffset(factor, units);
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

    glCopyTexImage2D(target, level, internalformat, x, y, width, height, border);
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

    glCopyTexSubImage2D(target, level, xoffset, yoffset, x, y, width, height);
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

    glTexSubImage2D(target, level, xoffset, yoffset, width, height, format, type, pixels);
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

    glBindTexture(target, texture);
}

static void retrace_glDeleteTextures(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    GLsizei n;
    n = (call.arg(0)).toSInt();

    GLuint * textures;
    textures = _allocator.allocArray<GLuint>(&call.arg(1));
    const trace::Array *_a_GLuint22_0 = (call.arg(1)).toArray();
    if (_a_GLuint22_0) {
        for (size_t _jGLuint22 = 0; _jGLuint22 < _a_GLuint22_0->values.size(); ++_jGLuint22) {
    textures[_jGLuint22] = (*_a_GLuint22_0->values[_jGLuint22]).toUInt();
    if (retrace::verbosity >= 2) {
        std::cout << "texture " << size_t(textures[_jGLuint22]) << " <- " << size_t(_texture_map[textures[_jGLuint22]]) << "\n";
    }
    textures[_jGLuint22] = _texture_map[textures[_jGLuint22]];
        }
    }

    glDeleteTextures(n, textures);
}

static void retrace_glGenTextures(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    GLsizei n;
    n = (call.arg(0)).toSInt();

    GLuint * textures;
    textures = _allocator.allocArray<GLuint>(&call.arg(1));

    glGenTextures(n, textures);
    const trace::Array *_aGLuint24 = (call.arg(1)).toArray();
    if (_aGLuint24) {
        for (size_t _jGLuint24 = 0; _jGLuint24 < _aGLuint24->values.size(); ++_jGLuint24) {
    GLuint _origResult;
    _origResult = (*_aGLuint24->values[_jGLuint24]).toUInt();
    _texture_map[_origResult] = textures[_jGLuint24];
    if (retrace::verbosity >= 2) {
        std::cout << "texture " << _origResult << " -> " << textures[_jGLuint24] << "\n";
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

    glBlendColor(red, green, blue, alpha);
}

static void retrace_glBlendEquation(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    GLenum mode;
    mode = static_cast<GLenum>((call.arg(0)).toSInt());

    glBlendEquation(mode);
}

static void retrace_glActiveTexture(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    GLenum texture;
    texture = static_cast<GLenum>((call.arg(0)).toSInt());

    glActiveTexture(texture);
}

static void retrace_glSampleCoverage(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    GLfloat value;
    value = (call.arg(0)).toFloat();

    GLboolean invert;
    invert = static_cast<GLboolean>((call.arg(1)).toSInt());

    glSampleCoverage(value, invert);
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

    glCompressedTexImage2D(target, level, internalformat, width, height, border, imageSize, data);
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

    glCompressedTexSubImage2D(target, level, xoffset, yoffset, width, height, format, imageSize, data);
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

    glBlendFuncSeparate(sfactorRGB, dfactorRGB, sfactorAlpha, dfactorAlpha);
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

    glBindBuffer(target, buffer);
}

static void retrace_glDeleteBuffers(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    GLsizei n;
    n = (call.arg(0)).toSInt();

    GLuint * buffer;
    buffer = _allocator.allocArray<GLuint>(&call.arg(1));
    const trace::Array *_a_GLuint25_0 = (call.arg(1)).toArray();
    if (_a_GLuint25_0) {
        for (size_t _jGLuint25 = 0; _jGLuint25 < _a_GLuint25_0->values.size(); ++_jGLuint25) {
    buffer[_jGLuint25] = (*_a_GLuint25_0->values[_jGLuint25]).toUInt();
    if (retrace::verbosity >= 2) {
        std::cout << "buffer " << size_t(buffer[_jGLuint25]) << " <- " << size_t(_buffer_map[buffer[_jGLuint25]]) << "\n";
    }
    buffer[_jGLuint25] = _buffer_map[buffer[_jGLuint25]];
        }
    }

    glDeleteBuffers(n, buffer);
}

static void retrace_glGenBuffers(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    GLsizei n;
    n = (call.arg(0)).toSInt();

    GLuint * buffer;
    buffer = _allocator.allocArray<GLuint>(&call.arg(1));

    glGenBuffers(n, buffer);
    const trace::Array *_aGLuint27 = (call.arg(1)).toArray();
    if (_aGLuint27) {
        for (size_t _jGLuint27 = 0; _jGLuint27 < _aGLuint27->values.size(); ++_jGLuint27) {
    GLuint _origResult;
    _origResult = (*_aGLuint27->values[_jGLuint27]).toUInt();
    _buffer_map[_origResult] = buffer[_jGLuint27];
    if (retrace::verbosity >= 2) {
        std::cout << "buffer " << _origResult << " -> " << buffer[_jGLuint27] << "\n";
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

    glBufferData(target, size, data, usage);
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

    glBufferSubData(target, offset, size, data);
}

static void retrace_glBlendEquationSeparate(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    GLenum modeRGB;
    modeRGB = static_cast<GLenum>((call.arg(0)).toSInt());

    GLenum modeAlpha;
    modeAlpha = static_cast<GLenum>((call.arg(1)).toSInt());

    glBlendEquationSeparate(modeRGB, modeAlpha);
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

    glStencilOpSeparate(face, sfail, dpfail, dppass);
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

    glStencilFuncSeparate(face, func, ref, mask);
}

static void retrace_glStencilMaskSeparate(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    GLenum face;
    face = static_cast<GLenum>((call.arg(0)).toSInt());

    GLuint mask;
    mask = (call.arg(1)).toUInt();

    glStencilMaskSeparate(face, mask);
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

    glAttachShader(program, shader);
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

    glBindAttribLocation(program, index, name);
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

    glCompileShader(shader);
}

static void retrace_glCreateProgram(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    GLuint _result;
    _result = glCreateProgram();
    (void)_result;
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
    _result = glCreateShader(type);
    (void)_result;
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

    glDeleteProgram(program);
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

    glDeleteShader(shader);
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

    if (!retrace::dumpingState) {
    glDetachShader(program, shader);
    }
}

static void retrace_glDisableVertexAttribArray(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    GLuint index;
    index = (call.arg(0)).toUInt();

    glDisableVertexAttribArray(index);
}

static void retrace_glEnableVertexAttribArray(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    GLuint index;
    index = (call.arg(0)).toUInt();

    glEnableVertexAttribArray(index);
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
    _result = glGetAttribLocation(program, name);
    (void)_result;
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
    _result = glGetUniformLocation(program, name);
    (void)_result;
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

    glLinkProgram(program);
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
    const trace::Array *_a_constGLchar9_0 = (call.arg(2)).toArray();
    if (_a_constGLchar9_0) {
        for (size_t _jconstGLchar9 = 0; _jconstGLchar9 < _a_constGLchar9_0->values.size(); ++_jconstGLchar9) {
    string[_jconstGLchar9] = (const GLchar *)((*_a_constGLchar9_0->values[_jconstGLchar9]).toString());
        }
    }

    GLint * length;
    length = _allocator.allocArray<GLint>(&call.arg(3));
    const trace::Array *_a_GLint21_0 = (call.arg(3)).toArray();
    if (_a_GLint21_0) {
        for (size_t _jGLint21 = 0; _jGLint21 < _a_GLint21_0->values.size(); ++_jGLint21) {
    length[_jGLint21] = (*_a_GLint21_0->values[_jGLint21]).toSInt();
        }
    }

    glShaderSource(shader, count, string, length);
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
    if (currentContext) {
        currentContext->activeProgram = call.arg(0).toUInt();
    }
    glUseProgram(program);
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

    glUniform1f(location, v0);
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

    glUniform2f(location, v0, v1);
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

    glUniform3f(location, v0, v1, v2);
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

    glUniform4f(location, v0, v1, v2, v3);
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

    glUniform1i(location, v0);
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

    glUniform2i(location, v0, v1);
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

    glUniform3i(location, v0, v1, v2);
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

    glUniform4i(location, v0, v1, v2, v3);
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
    const trace::Array *_a_GLfloat14_0 = (call.arg(2)).toArray();
    if (_a_GLfloat14_0) {
        for (size_t _jGLfloat14 = 0; _jGLfloat14 < _a_GLfloat14_0->values.size(); ++_jGLfloat14) {
    value[_jGLfloat14] = (*_a_GLfloat14_0->values[_jGLfloat14]).toFloat();
        }
    }

    glUniform1fv(location, count, value);
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
    const trace::Array *_a_GLfloat15_0 = (call.arg(2)).toArray();
    if (_a_GLfloat15_0) {
        for (size_t _jGLfloat15 = 0; _jGLfloat15 < _a_GLfloat15_0->values.size(); ++_jGLfloat15) {
    value[_jGLfloat15] = (*_a_GLfloat15_0->values[_jGLfloat15]).toFloat();
        }
    }

    glUniform2fv(location, count, value);
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
    const trace::Array *_a_GLfloat16_0 = (call.arg(2)).toArray();
    if (_a_GLfloat16_0) {
        for (size_t _jGLfloat16 = 0; _jGLfloat16 < _a_GLfloat16_0->values.size(); ++_jGLfloat16) {
    value[_jGLfloat16] = (*_a_GLfloat16_0->values[_jGLfloat16]).toFloat();
        }
    }

    glUniform3fv(location, count, value);
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
    const trace::Array *_a_GLfloat17_0 = (call.arg(2)).toArray();
    if (_a_GLfloat17_0) {
        for (size_t _jGLfloat17 = 0; _jGLfloat17 < _a_GLfloat17_0->values.size(); ++_jGLfloat17) {
    value[_jGLfloat17] = (*_a_GLfloat17_0->values[_jGLfloat17]).toFloat();
        }
    }

    glUniform4fv(location, count, value);
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
    const trace::Array *_a_GLint22_0 = (call.arg(2)).toArray();
    if (_a_GLint22_0) {
        for (size_t _jGLint22 = 0; _jGLint22 < _a_GLint22_0->values.size(); ++_jGLint22) {
    value[_jGLint22] = (*_a_GLint22_0->values[_jGLint22]).toSInt();
        }
    }

    glUniform1iv(location, count, value);
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
    const trace::Array *_a_GLint23_0 = (call.arg(2)).toArray();
    if (_a_GLint23_0) {
        for (size_t _jGLint23 = 0; _jGLint23 < _a_GLint23_0->values.size(); ++_jGLint23) {
    value[_jGLint23] = (*_a_GLint23_0->values[_jGLint23]).toSInt();
        }
    }

    glUniform2iv(location, count, value);
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
    const trace::Array *_a_GLint24_0 = (call.arg(2)).toArray();
    if (_a_GLint24_0) {
        for (size_t _jGLint24 = 0; _jGLint24 < _a_GLint24_0->values.size(); ++_jGLint24) {
    value[_jGLint24] = (*_a_GLint24_0->values[_jGLint24]).toSInt();
        }
    }

    glUniform3iv(location, count, value);
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
    const trace::Array *_a_GLint25_0 = (call.arg(2)).toArray();
    if (_a_GLint25_0) {
        for (size_t _jGLint25 = 0; _jGLint25 < _a_GLint25_0->values.size(); ++_jGLint25) {
    value[_jGLint25] = (*_a_GLint25_0->values[_jGLint25]).toSInt();
        }
    }

    glUniform4iv(location, count, value);
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
    const trace::Array *_a_GLfloat18_0 = (call.arg(3)).toArray();
    if (_a_GLfloat18_0) {
        for (size_t _jGLfloat18 = 0; _jGLfloat18 < _a_GLfloat18_0->values.size(); ++_jGLfloat18) {
    value[_jGLfloat18] = (*_a_GLfloat18_0->values[_jGLfloat18]).toFloat();
        }
    }

    glUniformMatrix2fv(location, count, transpose, value);
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
    const trace::Array *_a_GLfloat19_0 = (call.arg(3)).toArray();
    if (_a_GLfloat19_0) {
        for (size_t _jGLfloat19 = 0; _jGLfloat19 < _a_GLfloat19_0->values.size(); ++_jGLfloat19) {
    value[_jGLfloat19] = (*_a_GLfloat19_0->values[_jGLfloat19]).toFloat();
        }
    }

    glUniformMatrix3fv(location, count, transpose, value);
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
    const trace::Array *_a_GLfloat20_0 = (call.arg(3)).toArray();
    if (_a_GLfloat20_0) {
        for (size_t _jGLfloat20 = 0; _jGLfloat20 < _a_GLfloat20_0->values.size(); ++_jGLfloat20) {
    value[_jGLfloat20] = (*_a_GLfloat20_0->values[_jGLfloat20]).toFloat();
        }
    }

    glUniformMatrix4fv(location, count, transpose, value);
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

    glValidateProgram(program);
}

static void retrace_glVertexAttrib1f(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    GLuint index;
    index = (call.arg(0)).toUInt();

    GLfloat x;
    x = (call.arg(1)).toFloat();

    glVertexAttrib1f(index, x);
}

static void retrace_glVertexAttrib1fv(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    GLuint index;
    index = (call.arg(0)).toUInt();

    GLfloat * v;
    v = _allocator.allocArray<GLfloat>(&call.arg(1));
    if (v) {
        const trace::Array *_a_PGLfloat4_0 = (call.arg(1)).toArray();
    v[0] = (*_a_PGLfloat4_0->values[0]).toFloat();
    }

    glVertexAttrib1fv(index, v);
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

    glVertexAttrib2f(index, x, y);
}

static void retrace_glVertexAttrib2fv(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    GLuint index;
    index = (call.arg(0)).toUInt();

    GLfloat * v;
    v = _allocator.allocArray<GLfloat>(&call.arg(1));
    const trace::Array *_a_GLfloat21_0 = (call.arg(1)).toArray();
    if (_a_GLfloat21_0) {
        for (size_t _jGLfloat21 = 0; _jGLfloat21 < _a_GLfloat21_0->values.size(); ++_jGLfloat21) {
    v[_jGLfloat21] = (*_a_GLfloat21_0->values[_jGLfloat21]).toFloat();
        }
    }

    glVertexAttrib2fv(index, v);
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

    glVertexAttrib3f(index, x, y, z);
}

static void retrace_glVertexAttrib3fv(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    GLuint index;
    index = (call.arg(0)).toUInt();

    GLfloat * v;
    v = _allocator.allocArray<GLfloat>(&call.arg(1));
    const trace::Array *_a_GLfloat22_0 = (call.arg(1)).toArray();
    if (_a_GLfloat22_0) {
        for (size_t _jGLfloat22 = 0; _jGLfloat22 < _a_GLfloat22_0->values.size(); ++_jGLfloat22) {
    v[_jGLfloat22] = (*_a_GLfloat22_0->values[_jGLfloat22]).toFloat();
        }
    }

    glVertexAttrib3fv(index, v);
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

    glVertexAttrib4f(index, x, y, z, w);
}

static void retrace_glVertexAttrib4fv(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    GLuint index;
    index = (call.arg(0)).toUInt();

    GLfloat * v;
    v = _allocator.allocArray<GLfloat>(&call.arg(1));
    const trace::Array *_a_GLfloat23_0 = (call.arg(1)).toArray();
    if (_a_GLfloat23_0) {
        for (size_t _jGLfloat23 = 0; _jGLfloat23 < _a_GLfloat23_0->values.size(); ++_jGLfloat23) {
    v[_jGLfloat23] = (*_a_GLfloat23_0->values[_jGLfloat23]).toFloat();
        }
    }

    glVertexAttrib4fv(index, v);
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

    glVertexAttribPointer(index, size, type, normalized, stride, pointer);
}

static void retrace_glReleaseShaderCompiler(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    glReleaseShaderCompiler();
}

static void retrace_glShaderBinary(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    GLsizei count;
    count = (call.arg(0)).toSInt();

    GLuint * shaders;
    shaders = _allocator.allocArray<GLuint>(&call.arg(1));
    const trace::Array *_a_GLuint28_0 = (call.arg(1)).toArray();
    if (_a_GLuint28_0) {
        for (size_t _jGLuint28 = 0; _jGLuint28 < _a_GLuint28_0->values.size(); ++_jGLuint28) {
    shaders[_jGLuint28] = (*_a_GLuint28_0->values[_jGLuint28]).toUInt();
        }
    }

    GLenum binaryformat;
    binaryformat = static_cast<GLenum>((call.arg(2)).toSInt());

    GLvoid * binary;
    binary = static_cast<GLvoid *>((call.arg(3)).toPointer());

    GLsizei length;
    length = (call.arg(4)).toSInt();

    glShaderBinary(count, shaders, binaryformat, binary, length);
}

static void retrace_glDepthRangef(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    GLfloat n;
    n = (call.arg(0)).toFloat();

    GLfloat f;
    f = (call.arg(1)).toFloat();

    glDepthRangef(n, f);
}

static void retrace_glClearDepthf(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    GLfloat d;
    d = (call.arg(0)).toFloat();

    glClearDepthf(d);
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

    glBindRenderbuffer(target, renderbuffer);
}

static void retrace_glDeleteRenderbuffers(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    GLsizei n;
    n = (call.arg(0)).toSInt();

    GLuint * renderbuffers;
    renderbuffers = _allocator.allocArray<GLuint>(&call.arg(1));
    const trace::Array *_a_GLuint29_0 = (call.arg(1)).toArray();
    if (_a_GLuint29_0) {
        for (size_t _jGLuint29 = 0; _jGLuint29 < _a_GLuint29_0->values.size(); ++_jGLuint29) {
    renderbuffers[_jGLuint29] = (*_a_GLuint29_0->values[_jGLuint29]).toUInt();
    if (retrace::verbosity >= 2) {
        std::cout << "renderbuffer " << size_t(renderbuffers[_jGLuint29]) << " <- " << size_t(_renderbuffer_map[renderbuffers[_jGLuint29]]) << "\n";
    }
    renderbuffers[_jGLuint29] = _renderbuffer_map[renderbuffers[_jGLuint29]];
        }
    }

    glDeleteRenderbuffers(n, renderbuffers);
}

static void retrace_glGenRenderbuffers(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    GLsizei n;
    n = (call.arg(0)).toSInt();

    GLuint * renderbuffers;
    renderbuffers = _allocator.allocArray<GLuint>(&call.arg(1));

    glGenRenderbuffers(n, renderbuffers);
    const trace::Array *_aGLuint31 = (call.arg(1)).toArray();
    if (_aGLuint31) {
        for (size_t _jGLuint31 = 0; _jGLuint31 < _aGLuint31->values.size(); ++_jGLuint31) {
    GLuint _origResult;
    _origResult = (*_aGLuint31->values[_jGLuint31]).toUInt();
    _renderbuffer_map[_origResult] = renderbuffers[_jGLuint31];
    if (retrace::verbosity >= 2) {
        std::cout << "renderbuffer " << _origResult << " -> " << renderbuffers[_jGLuint31] << "\n";
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

    glRenderbufferStorage(target, internalformat, width, height);
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

    glBindFramebuffer(target, framebuffer);
}

static void retrace_glDeleteFramebuffers(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    GLsizei n;
    n = (call.arg(0)).toSInt();

    GLuint * framebuffers;
    framebuffers = _allocator.allocArray<GLuint>(&call.arg(1));
    const trace::Array *_a_GLuint32_0 = (call.arg(1)).toArray();
    if (_a_GLuint32_0) {
        for (size_t _jGLuint32 = 0; _jGLuint32 < _a_GLuint32_0->values.size(); ++_jGLuint32) {
    framebuffers[_jGLuint32] = (*_a_GLuint32_0->values[_jGLuint32]).toUInt();
    if (retrace::verbosity >= 2) {
        std::cout << "framebuffer " << size_t(framebuffers[_jGLuint32]) << " <- " << size_t(_framebuffer_map[framebuffers[_jGLuint32]]) << "\n";
    }
    framebuffers[_jGLuint32] = _framebuffer_map[framebuffers[_jGLuint32]];
        }
    }

    glDeleteFramebuffers(n, framebuffers);
}

static void retrace_glGenFramebuffers(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    GLsizei n;
    n = (call.arg(0)).toSInt();

    GLuint * framebuffers;
    framebuffers = _allocator.allocArray<GLuint>(&call.arg(1));

    glGenFramebuffers(n, framebuffers);
    const trace::Array *_aGLuint34 = (call.arg(1)).toArray();
    if (_aGLuint34) {
        for (size_t _jGLuint34 = 0; _jGLuint34 < _aGLuint34->values.size(); ++_jGLuint34) {
    GLuint _origResult;
    _origResult = (*_aGLuint34->values[_jGLuint34]).toUInt();
    _framebuffer_map[_origResult] = framebuffers[_jGLuint34];
    if (retrace::verbosity >= 2) {
        std::cout << "framebuffer " << _origResult << " -> " << framebuffers[_jGLuint34] << "\n";
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
    _result = glCheckFramebufferStatus(target);
    (void)_result;
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

    glFramebufferTexture2D(target, attachment, textarget, texture, level);
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

    glFramebufferRenderbuffer(target, attachment, renderbuffertarget, renderbuffer);
}

static void retrace_glGenerateMipmap(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    GLenum target;
    target = static_cast<GLenum>((call.arg(0)).toSInt());

    glGenerateMipmap(target);
}

static void retrace_glGenPerfMonitorsAMD(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    GLsizei n;
    n = (call.arg(0)).toSInt();

    GLuint * monitors;
    monitors = _allocator.allocArray<GLuint>(&call.arg(1));

    glGenPerfMonitorsAMD(n, monitors);
    const trace::Array *_aGLuint36 = (call.arg(1)).toArray();
    if (_aGLuint36) {
        for (size_t _jGLuint36 = 0; _jGLuint36 < _aGLuint36->values.size(); ++_jGLuint36) {
        }
    }
}

static void retrace_glDeletePerfMonitorsAMD(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    GLsizei n;
    n = (call.arg(0)).toSInt();

    GLuint * monitors;
    monitors = _allocator.allocArray<GLuint>(&call.arg(1));
    const trace::Array *_a_GLuint37_0 = (call.arg(1)).toArray();
    if (_a_GLuint37_0) {
        for (size_t _jGLuint37 = 0; _jGLuint37 < _a_GLuint37_0->values.size(); ++_jGLuint37) {
    monitors[_jGLuint37] = (*_a_GLuint37_0->values[_jGLuint37]).toUInt();
        }
    }

    glDeletePerfMonitorsAMD(n, monitors);
}

static void retrace_glSelectPerfMonitorCountersAMD(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    GLuint monitor;
    monitor = (call.arg(0)).toUInt();

    GLboolean enable;
    enable = static_cast<GLboolean>((call.arg(1)).toSInt());

    GLuint group;
    group = (call.arg(2)).toUInt();

    GLint numCounters;
    numCounters = (call.arg(3)).toSInt();

    GLuint * counterList;
    counterList = _allocator.allocArray<GLuint>(&call.arg(4));
    const trace::Array *_a_GLuint38_0 = (call.arg(4)).toArray();
    if (_a_GLuint38_0) {
        for (size_t _jGLuint38 = 0; _jGLuint38 < _a_GLuint38_0->values.size(); ++_jGLuint38) {
    counterList[_jGLuint38] = (*_a_GLuint38_0->values[_jGLuint38]).toUInt();
        }
    }

    glSelectPerfMonitorCountersAMD(monitor, enable, group, numCounters, counterList);
}

static void retrace_glBeginPerfMonitorAMD(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    GLuint monitor;
    monitor = (call.arg(0)).toUInt();

    glBeginPerfMonitorAMD(monitor);
}

static void retrace_glEndPerfMonitorAMD(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    GLuint monitor;
    monitor = (call.arg(0)).toUInt();

    glEndPerfMonitorAMD(monitor);
}

static void retrace_glBlitFramebufferANGLE(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    GLint srcX0;
    srcX0 = (call.arg(0)).toSInt();

    GLint srcY0;
    srcY0 = (call.arg(1)).toSInt();

    GLint srcX1;
    srcX1 = (call.arg(2)).toSInt();

    GLint srcY1;
    srcY1 = (call.arg(3)).toSInt();

    GLint dstX0;
    dstX0 = (call.arg(4)).toSInt();

    GLint dstY0;
    dstY0 = (call.arg(5)).toSInt();

    GLint dstX1;
    dstX1 = (call.arg(6)).toSInt();

    GLint dstY1;
    dstY1 = (call.arg(7)).toSInt();

    GLbitfield mask;
    mask = (call.arg(8)).toUInt();

    GLenum filter;
    filter = static_cast<GLenum>((call.arg(9)).toSInt());

    glBlitFramebufferANGLE(srcX0, srcY0, srcX1, srcY1, dstX0, dstY0, dstX1, dstY1, mask, filter);
    assert(call.flags & trace::CALL_FLAG_RENDER);
}

static void retrace_glRenderbufferStorageMultisampleANGLE(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    GLenum target;
    target = static_cast<GLenum>((call.arg(0)).toSInt());

    GLsizei samples;
    samples = (call.arg(1)).toSInt();
    GLint max_samples = 0;
    glGetIntegerv(GL_MAX_SAMPLES, &max_samples);
    if (samples > max_samples) {
        samples = max_samples;
    }

    GLenum internalformat;
    internalformat = static_cast<GLenum>((call.arg(2)).toSInt());

    GLsizei width;
    width = (call.arg(3)).toSInt();

    GLsizei height;
    height = (call.arg(4)).toSInt();

    glRenderbufferStorageMultisampleANGLE(target, samples, internalformat, width, height);
}

static void retrace_glDrawArraysInstancedANGLE(trace::Call &call) {
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

    GLsizei primcount;
    primcount = (call.arg(3)).toSInt();

    if (retrace::debug) {
        _validateActiveProgram(call);
    }
    glDrawArraysInstancedANGLE(mode, first, count, primcount);
    assert(call.flags & trace::CALL_FLAG_RENDER);
}

static void retrace_glDrawElementsInstancedANGLE(trace::Call &call) {
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

    GLsizei primcount;
    primcount = (call.arg(4)).toSInt();

    if (retrace::debug) {
        _validateActiveProgram(call);
    }
    glDrawElementsInstancedANGLE(mode, count, type, indices, primcount);
    assert(call.flags & trace::CALL_FLAG_RENDER);
}

static void retrace_glVertexAttribDivisorANGLE(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    GLuint index;
    index = (call.arg(0)).toUInt();

    GLuint divisor;
    divisor = (call.arg(1)).toUInt();

    glVertexAttribDivisorANGLE(index, divisor);
}

static void retrace_glCopyTextureLevelsAPPLE(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    GLuint destinationTexture;
    destinationTexture = (call.arg(0)).toUInt();
    if (retrace::verbosity >= 2) {
        std::cout << "texture " << size_t(destinationTexture) << " <- " << size_t(_texture_map[destinationTexture]) << "\n";
    }
    destinationTexture = _texture_map[destinationTexture];

    GLuint sourceTexture;
    sourceTexture = (call.arg(1)).toUInt();
    if (retrace::verbosity >= 2) {
        std::cout << "texture " << size_t(sourceTexture) << " <- " << size_t(_texture_map[sourceTexture]) << "\n";
    }
    sourceTexture = _texture_map[sourceTexture];

    GLint sourceBaseLevel;
    sourceBaseLevel = (call.arg(2)).toSInt();

    GLsizei sourceLevelCount;
    sourceLevelCount = (call.arg(3)).toSInt();

    glCopyTextureLevelsAPPLE(destinationTexture, sourceTexture, sourceBaseLevel, sourceLevelCount);
}

static void retrace_glRenderbufferStorageMultisampleAPPLE(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    GLenum target;
    target = static_cast<GLenum>((call.arg(0)).toSInt());

    GLsizei samples;
    samples = (call.arg(1)).toSInt();
    GLint max_samples = 0;
    glGetIntegerv(GL_MAX_SAMPLES, &max_samples);
    if (samples > max_samples) {
        samples = max_samples;
    }

    GLenum internalformat;
    internalformat = static_cast<GLenum>((call.arg(2)).toSInt());

    GLsizei width;
    width = (call.arg(3)).toSInt();

    GLsizei height;
    height = (call.arg(4)).toSInt();

    glRenderbufferStorageMultisampleAPPLE(target, samples, internalformat, width, height);
}

static void retrace_glResolveMultisampleFramebufferAPPLE(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    glResolveMultisampleFramebufferAPPLE();
}

static void retrace_glFenceSyncAPPLE(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    GLenum condition;
    condition = static_cast<GLenum>((call.arg(0)).toSInt());

    GLbitfield flags;
    flags = (call.arg(1)).toUInt();

    GLsync _result;
    _result = glFenceSyncAPPLE(condition, flags);
    (void)_result;
    GLsync _origResult;
    _origResult = static_cast<GLsync>((*call.ret).toPointer());
    _sync_map[_origResult] = _result;
    if (retrace::verbosity >= 2) {
        std::cout << "sync " << _origResult << " -> " << _result << "\n";
    }
}

static void retrace_glDeleteSyncAPPLE(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    GLsync sync;
    sync = static_cast<GLsync>((call.arg(0)).toPointer());
    if (retrace::verbosity >= 2) {
        std::cout << "sync " << size_t(sync) << " <- " << size_t(_sync_map[sync]) << "\n";
    }
    sync = _sync_map[sync];

    glDeleteSyncAPPLE(sync);
}

static void retrace_glClientWaitSyncAPPLE(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    GLsync sync;
    sync = static_cast<GLsync>((call.arg(0)).toPointer());
    if (retrace::verbosity >= 2) {
        std::cout << "sync " << size_t(sync) << " <- " << size_t(_sync_map[sync]) << "\n";
    }
    sync = _sync_map[sync];

    GLbitfield flags;
    flags = (call.arg(1)).toUInt();

    GLuint64 timeout;
    timeout = (call.arg(2)).toUInt();

    GLenum _result;
    _result = glClientWaitSyncAPPLE(sync, flags, timeout);
    (void)_result;
}

static void retrace_glWaitSyncAPPLE(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    GLsync sync;
    sync = static_cast<GLsync>((call.arg(0)).toPointer());
    if (retrace::verbosity >= 2) {
        std::cout << "sync " << size_t(sync) << " <- " << size_t(_sync_map[sync]) << "\n";
    }
    sync = _sync_map[sync];

    GLbitfield flags;
    flags = (call.arg(1)).toUInt();

    GLuint64 timeout;
    timeout = (call.arg(2)).toUInt();

    glWaitSyncAPPLE(sync, flags, timeout);
}

static void retrace_glTexPageCommitmentARB(trace::Call &call) {
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

    GLint zoffset;
    zoffset = (call.arg(4)).toSInt();

    GLsizei width;
    width = (call.arg(5)).toSInt();

    GLsizei height;
    height = (call.arg(6)).toSInt();

    GLsizei depth;
    depth = (call.arg(7)).toSInt();

    GLboolean resident;
    resident = static_cast<GLboolean>((call.arg(8)).toSInt());

    glTexPageCommitmentARB(target, level, xoffset, yoffset, zoffset, width, height, depth, resident);
}

static void retrace_glCopyImageSubDataEXT(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    GLuint srcName;
    srcName = (call.arg(0)).toUInt();

    GLenum srcTarget;
    srcTarget = static_cast<GLenum>((call.arg(1)).toSInt());

    GLint srcLevel;
    srcLevel = (call.arg(2)).toSInt();

    GLint srcX;
    srcX = (call.arg(3)).toSInt();

    GLint srcY;
    srcY = (call.arg(4)).toSInt();

    GLint srcZ;
    srcZ = (call.arg(5)).toSInt();

    GLuint dstName;
    dstName = (call.arg(6)).toUInt();

    GLenum dstTarget;
    dstTarget = static_cast<GLenum>((call.arg(7)).toSInt());

    GLint dstLevel;
    dstLevel = (call.arg(8)).toSInt();

    GLint dstX;
    dstX = (call.arg(9)).toSInt();

    GLint dstY;
    dstY = (call.arg(10)).toSInt();

    GLint dstZ;
    dstZ = (call.arg(11)).toSInt();

    GLsizei srcWidth;
    srcWidth = (call.arg(12)).toSInt();

    GLsizei srcHeight;
    srcHeight = (call.arg(13)).toSInt();

    GLsizei srcDepth;
    srcDepth = (call.arg(14)).toSInt();

    glCopyImageSubDataEXT(srcName, srcTarget, srcLevel, srcX, srcY, srcZ, dstName, dstTarget, dstLevel, dstX, dstY, dstZ, srcWidth, srcHeight, srcDepth);
}

static void retrace_glLabelObjectEXT(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    GLenum type;
    type = static_cast<GLenum>((call.arg(0)).toSInt());

    GLuint object;
    object = (call.arg(1)).toUInt();

    GLsizei length;
    length = (call.arg(2)).toSInt();

    const GLchar * label;
    label = (const GLchar *)((call.arg(3)).toString());

    glLabelObjectEXT(type, object, length, label);
}

static void retrace_glInsertEventMarkerEXT(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    GLsizei length;
    length = (call.arg(0)).toSInt();

    const GLchar * marker;
    marker = (const GLchar *)((call.arg(1)).toString());

    glInsertEventMarkerEXT(length, marker);
}

static void retrace_glPushGroupMarkerEXT(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    GLsizei length;
    length = (call.arg(0)).toSInt();

    const GLchar * marker;
    marker = (const GLchar *)((call.arg(1)).toString());

    glPushGroupMarkerEXT(length, marker);
}

static void retrace_glPopGroupMarkerEXT(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    glPopGroupMarkerEXT();
}

static void retrace_glProgramUniform1fEXT(trace::Call &call) {
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

    GLint location;
    location = (call.arg(1)).toSInt();
    if (retrace::verbosity >= 2) {
        std::cout << "location " << size_t(location) << " <- " << size_t(_location_map[program].lookupUniformLocation(location)) << "\n";
    }
    location = _location_map[program].lookupUniformLocation(location);

    GLfloat v0;
    v0 = (call.arg(2)).toFloat();

    glProgramUniform1fEXT(program, location, v0);
}

static void retrace_glProgramUniform1fvEXT(trace::Call &call) {
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

    GLint location;
    location = (call.arg(1)).toSInt();
    if (retrace::verbosity >= 2) {
        std::cout << "location " << size_t(location) << " <- " << size_t(_location_map[program].lookupUniformLocation(location)) << "\n";
    }
    location = _location_map[program].lookupUniformLocation(location);

    GLsizei count;
    count = (call.arg(2)).toSInt();

    GLfloat * value;
    value = _allocator.allocArray<GLfloat>(&call.arg(3));
    const trace::Array *_a_GLfloat24_0 = (call.arg(3)).toArray();
    if (_a_GLfloat24_0) {
        for (size_t _jGLfloat24 = 0; _jGLfloat24 < _a_GLfloat24_0->values.size(); ++_jGLfloat24) {
    value[_jGLfloat24] = (*_a_GLfloat24_0->values[_jGLfloat24]).toFloat();
        }
    }

    glProgramUniform1fvEXT(program, location, count, value);
}

static void retrace_glProgramUniform1iEXT(trace::Call &call) {
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

    GLint location;
    location = (call.arg(1)).toSInt();
    if (retrace::verbosity >= 2) {
        std::cout << "location " << size_t(location) << " <- " << size_t(_location_map[program].lookupUniformLocation(location)) << "\n";
    }
    location = _location_map[program].lookupUniformLocation(location);

    GLint v0;
    v0 = (call.arg(2)).toSInt();

    glProgramUniform1iEXT(program, location, v0);
}

static void retrace_glProgramUniform1ivEXT(trace::Call &call) {
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

    GLint location;
    location = (call.arg(1)).toSInt();
    if (retrace::verbosity >= 2) {
        std::cout << "location " << size_t(location) << " <- " << size_t(_location_map[program].lookupUniformLocation(location)) << "\n";
    }
    location = _location_map[program].lookupUniformLocation(location);

    GLsizei count;
    count = (call.arg(2)).toSInt();

    GLint * value;
    value = _allocator.allocArray<GLint>(&call.arg(3));
    const trace::Array *_a_GLint26_0 = (call.arg(3)).toArray();
    if (_a_GLint26_0) {
        for (size_t _jGLint26 = 0; _jGLint26 < _a_GLint26_0->values.size(); ++_jGLint26) {
    value[_jGLint26] = (*_a_GLint26_0->values[_jGLint26]).toSInt();
        }
    }

    glProgramUniform1ivEXT(program, location, count, value);
}

static void retrace_glProgramUniform1uiEXT(trace::Call &call) {
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

    GLint location;
    location = (call.arg(1)).toSInt();
    if (retrace::verbosity >= 2) {
        std::cout << "location " << size_t(location) << " <- " << size_t(_location_map[program].lookupUniformLocation(location)) << "\n";
    }
    location = _location_map[program].lookupUniformLocation(location);

    GLuint v0;
    v0 = (call.arg(2)).toUInt();

    glProgramUniform1uiEXT(program, location, v0);
}

static void retrace_glProgramUniform1uivEXT(trace::Call &call) {
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

    GLint location;
    location = (call.arg(1)).toSInt();
    if (retrace::verbosity >= 2) {
        std::cout << "location " << size_t(location) << " <- " << size_t(_location_map[program].lookupUniformLocation(location)) << "\n";
    }
    location = _location_map[program].lookupUniformLocation(location);

    GLsizei count;
    count = (call.arg(2)).toSInt();

    GLuint * value;
    value = _allocator.allocArray<GLuint>(&call.arg(3));
    const trace::Array *_a_GLuint41_0 = (call.arg(3)).toArray();
    if (_a_GLuint41_0) {
        for (size_t _jGLuint41 = 0; _jGLuint41 < _a_GLuint41_0->values.size(); ++_jGLuint41) {
    value[_jGLuint41] = (*_a_GLuint41_0->values[_jGLuint41]).toUInt();
        }
    }

    glProgramUniform1uivEXT(program, location, count, value);
}

static void retrace_glProgramUniform2fEXT(trace::Call &call) {
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

    GLint location;
    location = (call.arg(1)).toSInt();
    if (retrace::verbosity >= 2) {
        std::cout << "location " << size_t(location) << " <- " << size_t(_location_map[program].lookupUniformLocation(location)) << "\n";
    }
    location = _location_map[program].lookupUniformLocation(location);

    GLfloat v0;
    v0 = (call.arg(2)).toFloat();

    GLfloat v1;
    v1 = (call.arg(3)).toFloat();

    glProgramUniform2fEXT(program, location, v0, v1);
}

static void retrace_glProgramUniform2fvEXT(trace::Call &call) {
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

    GLint location;
    location = (call.arg(1)).toSInt();
    if (retrace::verbosity >= 2) {
        std::cout << "location " << size_t(location) << " <- " << size_t(_location_map[program].lookupUniformLocation(location)) << "\n";
    }
    location = _location_map[program].lookupUniformLocation(location);

    GLsizei count;
    count = (call.arg(2)).toSInt();

    GLfloat * value;
    value = _allocator.allocArray<GLfloat>(&call.arg(3));
    const trace::Array *_a_GLfloat25_0 = (call.arg(3)).toArray();
    if (_a_GLfloat25_0) {
        for (size_t _jGLfloat25 = 0; _jGLfloat25 < _a_GLfloat25_0->values.size(); ++_jGLfloat25) {
    value[_jGLfloat25] = (*_a_GLfloat25_0->values[_jGLfloat25]).toFloat();
        }
    }

    glProgramUniform2fvEXT(program, location, count, value);
}

static void retrace_glProgramUniform2iEXT(trace::Call &call) {
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

    GLint location;
    location = (call.arg(1)).toSInt();
    if (retrace::verbosity >= 2) {
        std::cout << "location " << size_t(location) << " <- " << size_t(_location_map[program].lookupUniformLocation(location)) << "\n";
    }
    location = _location_map[program].lookupUniformLocation(location);

    GLint v0;
    v0 = (call.arg(2)).toSInt();

    GLint v1;
    v1 = (call.arg(3)).toSInt();

    glProgramUniform2iEXT(program, location, v0, v1);
}

static void retrace_glProgramUniform2ivEXT(trace::Call &call) {
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

    GLint location;
    location = (call.arg(1)).toSInt();
    if (retrace::verbosity >= 2) {
        std::cout << "location " << size_t(location) << " <- " << size_t(_location_map[program].lookupUniformLocation(location)) << "\n";
    }
    location = _location_map[program].lookupUniformLocation(location);

    GLsizei count;
    count = (call.arg(2)).toSInt();

    GLint * value;
    value = _allocator.allocArray<GLint>(&call.arg(3));
    const trace::Array *_a_GLint27_0 = (call.arg(3)).toArray();
    if (_a_GLint27_0) {
        for (size_t _jGLint27 = 0; _jGLint27 < _a_GLint27_0->values.size(); ++_jGLint27) {
    value[_jGLint27] = (*_a_GLint27_0->values[_jGLint27]).toSInt();
        }
    }

    glProgramUniform2ivEXT(program, location, count, value);
}

static void retrace_glProgramUniform2uiEXT(trace::Call &call) {
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

    GLint location;
    location = (call.arg(1)).toSInt();
    if (retrace::verbosity >= 2) {
        std::cout << "location " << size_t(location) << " <- " << size_t(_location_map[program].lookupUniformLocation(location)) << "\n";
    }
    location = _location_map[program].lookupUniformLocation(location);

    GLuint v0;
    v0 = (call.arg(2)).toUInt();

    GLuint v1;
    v1 = (call.arg(3)).toUInt();

    glProgramUniform2uiEXT(program, location, v0, v1);
}

static void retrace_glProgramUniform2uivEXT(trace::Call &call) {
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

    GLint location;
    location = (call.arg(1)).toSInt();
    if (retrace::verbosity >= 2) {
        std::cout << "location " << size_t(location) << " <- " << size_t(_location_map[program].lookupUniformLocation(location)) << "\n";
    }
    location = _location_map[program].lookupUniformLocation(location);

    GLsizei count;
    count = (call.arg(2)).toSInt();

    GLuint * value;
    value = _allocator.allocArray<GLuint>(&call.arg(3));
    const trace::Array *_a_GLuint42_0 = (call.arg(3)).toArray();
    if (_a_GLuint42_0) {
        for (size_t _jGLuint42 = 0; _jGLuint42 < _a_GLuint42_0->values.size(); ++_jGLuint42) {
    value[_jGLuint42] = (*_a_GLuint42_0->values[_jGLuint42]).toUInt();
        }
    }

    glProgramUniform2uivEXT(program, location, count, value);
}

static void retrace_glProgramUniform3fEXT(trace::Call &call) {
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

    GLint location;
    location = (call.arg(1)).toSInt();
    if (retrace::verbosity >= 2) {
        std::cout << "location " << size_t(location) << " <- " << size_t(_location_map[program].lookupUniformLocation(location)) << "\n";
    }
    location = _location_map[program].lookupUniformLocation(location);

    GLfloat v0;
    v0 = (call.arg(2)).toFloat();

    GLfloat v1;
    v1 = (call.arg(3)).toFloat();

    GLfloat v2;
    v2 = (call.arg(4)).toFloat();

    glProgramUniform3fEXT(program, location, v0, v1, v2);
}

static void retrace_glProgramUniform3fvEXT(trace::Call &call) {
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

    GLint location;
    location = (call.arg(1)).toSInt();
    if (retrace::verbosity >= 2) {
        std::cout << "location " << size_t(location) << " <- " << size_t(_location_map[program].lookupUniformLocation(location)) << "\n";
    }
    location = _location_map[program].lookupUniformLocation(location);

    GLsizei count;
    count = (call.arg(2)).toSInt();

    GLfloat * value;
    value = _allocator.allocArray<GLfloat>(&call.arg(3));
    const trace::Array *_a_GLfloat26_0 = (call.arg(3)).toArray();
    if (_a_GLfloat26_0) {
        for (size_t _jGLfloat26 = 0; _jGLfloat26 < _a_GLfloat26_0->values.size(); ++_jGLfloat26) {
    value[_jGLfloat26] = (*_a_GLfloat26_0->values[_jGLfloat26]).toFloat();
        }
    }

    glProgramUniform3fvEXT(program, location, count, value);
}

static void retrace_glProgramUniform3iEXT(trace::Call &call) {
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

    GLint location;
    location = (call.arg(1)).toSInt();
    if (retrace::verbosity >= 2) {
        std::cout << "location " << size_t(location) << " <- " << size_t(_location_map[program].lookupUniformLocation(location)) << "\n";
    }
    location = _location_map[program].lookupUniformLocation(location);

    GLint v0;
    v0 = (call.arg(2)).toSInt();

    GLint v1;
    v1 = (call.arg(3)).toSInt();

    GLint v2;
    v2 = (call.arg(4)).toSInt();

    glProgramUniform3iEXT(program, location, v0, v1, v2);
}

static void retrace_glProgramUniform3ivEXT(trace::Call &call) {
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

    GLint location;
    location = (call.arg(1)).toSInt();
    if (retrace::verbosity >= 2) {
        std::cout << "location " << size_t(location) << " <- " << size_t(_location_map[program].lookupUniformLocation(location)) << "\n";
    }
    location = _location_map[program].lookupUniformLocation(location);

    GLsizei count;
    count = (call.arg(2)).toSInt();

    GLint * value;
    value = _allocator.allocArray<GLint>(&call.arg(3));
    const trace::Array *_a_GLint28_0 = (call.arg(3)).toArray();
    if (_a_GLint28_0) {
        for (size_t _jGLint28 = 0; _jGLint28 < _a_GLint28_0->values.size(); ++_jGLint28) {
    value[_jGLint28] = (*_a_GLint28_0->values[_jGLint28]).toSInt();
        }
    }

    glProgramUniform3ivEXT(program, location, count, value);
}

static void retrace_glProgramUniform3uiEXT(trace::Call &call) {
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

    GLint location;
    location = (call.arg(1)).toSInt();
    if (retrace::verbosity >= 2) {
        std::cout << "location " << size_t(location) << " <- " << size_t(_location_map[program].lookupUniformLocation(location)) << "\n";
    }
    location = _location_map[program].lookupUniformLocation(location);

    GLuint v0;
    v0 = (call.arg(2)).toUInt();

    GLuint v1;
    v1 = (call.arg(3)).toUInt();

    GLuint v2;
    v2 = (call.arg(4)).toUInt();

    glProgramUniform3uiEXT(program, location, v0, v1, v2);
}

static void retrace_glProgramUniform3uivEXT(trace::Call &call) {
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

    GLint location;
    location = (call.arg(1)).toSInt();
    if (retrace::verbosity >= 2) {
        std::cout << "location " << size_t(location) << " <- " << size_t(_location_map[program].lookupUniformLocation(location)) << "\n";
    }
    location = _location_map[program].lookupUniformLocation(location);

    GLsizei count;
    count = (call.arg(2)).toSInt();

    GLuint * value;
    value = _allocator.allocArray<GLuint>(&call.arg(3));
    const trace::Array *_a_GLuint43_0 = (call.arg(3)).toArray();
    if (_a_GLuint43_0) {
        for (size_t _jGLuint43 = 0; _jGLuint43 < _a_GLuint43_0->values.size(); ++_jGLuint43) {
    value[_jGLuint43] = (*_a_GLuint43_0->values[_jGLuint43]).toUInt();
        }
    }

    glProgramUniform3uivEXT(program, location, count, value);
}

static void retrace_glProgramUniform4fEXT(trace::Call &call) {
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

    GLint location;
    location = (call.arg(1)).toSInt();
    if (retrace::verbosity >= 2) {
        std::cout << "location " << size_t(location) << " <- " << size_t(_location_map[program].lookupUniformLocation(location)) << "\n";
    }
    location = _location_map[program].lookupUniformLocation(location);

    GLfloat v0;
    v0 = (call.arg(2)).toFloat();

    GLfloat v1;
    v1 = (call.arg(3)).toFloat();

    GLfloat v2;
    v2 = (call.arg(4)).toFloat();

    GLfloat v3;
    v3 = (call.arg(5)).toFloat();

    glProgramUniform4fEXT(program, location, v0, v1, v2, v3);
}

static void retrace_glProgramUniform4fvEXT(trace::Call &call) {
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

    GLint location;
    location = (call.arg(1)).toSInt();
    if (retrace::verbosity >= 2) {
        std::cout << "location " << size_t(location) << " <- " << size_t(_location_map[program].lookupUniformLocation(location)) << "\n";
    }
    location = _location_map[program].lookupUniformLocation(location);

    GLsizei count;
    count = (call.arg(2)).toSInt();

    GLfloat * value;
    value = _allocator.allocArray<GLfloat>(&call.arg(3));
    const trace::Array *_a_GLfloat27_0 = (call.arg(3)).toArray();
    if (_a_GLfloat27_0) {
        for (size_t _jGLfloat27 = 0; _jGLfloat27 < _a_GLfloat27_0->values.size(); ++_jGLfloat27) {
    value[_jGLfloat27] = (*_a_GLfloat27_0->values[_jGLfloat27]).toFloat();
        }
    }

    glProgramUniform4fvEXT(program, location, count, value);
}

static void retrace_glProgramUniform4iEXT(trace::Call &call) {
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

    GLint location;
    location = (call.arg(1)).toSInt();
    if (retrace::verbosity >= 2) {
        std::cout << "location " << size_t(location) << " <- " << size_t(_location_map[program].lookupUniformLocation(location)) << "\n";
    }
    location = _location_map[program].lookupUniformLocation(location);

    GLint v0;
    v0 = (call.arg(2)).toSInt();

    GLint v1;
    v1 = (call.arg(3)).toSInt();

    GLint v2;
    v2 = (call.arg(4)).toSInt();

    GLint v3;
    v3 = (call.arg(5)).toSInt();

    glProgramUniform4iEXT(program, location, v0, v1, v2, v3);
}

static void retrace_glProgramUniform4ivEXT(trace::Call &call) {
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

    GLint location;
    location = (call.arg(1)).toSInt();
    if (retrace::verbosity >= 2) {
        std::cout << "location " << size_t(location) << " <- " << size_t(_location_map[program].lookupUniformLocation(location)) << "\n";
    }
    location = _location_map[program].lookupUniformLocation(location);

    GLsizei count;
    count = (call.arg(2)).toSInt();

    GLint * value;
    value = _allocator.allocArray<GLint>(&call.arg(3));
    const trace::Array *_a_GLint29_0 = (call.arg(3)).toArray();
    if (_a_GLint29_0) {
        for (size_t _jGLint29 = 0; _jGLint29 < _a_GLint29_0->values.size(); ++_jGLint29) {
    value[_jGLint29] = (*_a_GLint29_0->values[_jGLint29]).toSInt();
        }
    }

    glProgramUniform4ivEXT(program, location, count, value);
}

static void retrace_glProgramUniform4uiEXT(trace::Call &call) {
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

    GLint location;
    location = (call.arg(1)).toSInt();
    if (retrace::verbosity >= 2) {
        std::cout << "location " << size_t(location) << " <- " << size_t(_location_map[program].lookupUniformLocation(location)) << "\n";
    }
    location = _location_map[program].lookupUniformLocation(location);

    GLuint v0;
    v0 = (call.arg(2)).toUInt();

    GLuint v1;
    v1 = (call.arg(3)).toUInt();

    GLuint v2;
    v2 = (call.arg(4)).toUInt();

    GLuint v3;
    v3 = (call.arg(5)).toUInt();

    glProgramUniform4uiEXT(program, location, v0, v1, v2, v3);
}

static void retrace_glProgramUniform4uivEXT(trace::Call &call) {
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

    GLint location;
    location = (call.arg(1)).toSInt();
    if (retrace::verbosity >= 2) {
        std::cout << "location " << size_t(location) << " <- " << size_t(_location_map[program].lookupUniformLocation(location)) << "\n";
    }
    location = _location_map[program].lookupUniformLocation(location);

    GLsizei count;
    count = (call.arg(2)).toSInt();

    GLuint * value;
    value = _allocator.allocArray<GLuint>(&call.arg(3));
    const trace::Array *_a_GLuint44_0 = (call.arg(3)).toArray();
    if (_a_GLuint44_0) {
        for (size_t _jGLuint44 = 0; _jGLuint44 < _a_GLuint44_0->values.size(); ++_jGLuint44) {
    value[_jGLuint44] = (*_a_GLuint44_0->values[_jGLuint44]).toUInt();
        }
    }

    glProgramUniform4uivEXT(program, location, count, value);
}

static void retrace_glProgramUniformMatrix2fvEXT(trace::Call &call) {
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

    GLint location;
    location = (call.arg(1)).toSInt();
    if (retrace::verbosity >= 2) {
        std::cout << "location " << size_t(location) << " <- " << size_t(_location_map[program].lookupUniformLocation(location)) << "\n";
    }
    location = _location_map[program].lookupUniformLocation(location);

    GLsizei count;
    count = (call.arg(2)).toSInt();

    GLboolean transpose;
    transpose = static_cast<GLboolean>((call.arg(3)).toSInt());

    GLfloat * value;
    value = _allocator.allocArray<GLfloat>(&call.arg(4));
    const trace::Array *_a_GLfloat28_0 = (call.arg(4)).toArray();
    if (_a_GLfloat28_0) {
        for (size_t _jGLfloat28 = 0; _jGLfloat28 < _a_GLfloat28_0->values.size(); ++_jGLfloat28) {
    value[_jGLfloat28] = (*_a_GLfloat28_0->values[_jGLfloat28]).toFloat();
        }
    }

    glProgramUniformMatrix2fvEXT(program, location, count, transpose, value);
}

static void retrace_glProgramUniformMatrix2x3fvEXT(trace::Call &call) {
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

    GLint location;
    location = (call.arg(1)).toSInt();
    if (retrace::verbosity >= 2) {
        std::cout << "location " << size_t(location) << " <- " << size_t(_location_map[program].lookupUniformLocation(location)) << "\n";
    }
    location = _location_map[program].lookupUniformLocation(location);

    GLsizei count;
    count = (call.arg(2)).toSInt();

    GLboolean transpose;
    transpose = static_cast<GLboolean>((call.arg(3)).toSInt());

    GLfloat * value;
    value = _allocator.allocArray<GLfloat>(&call.arg(4));
    const trace::Array *_a_GLfloat29_0 = (call.arg(4)).toArray();
    if (_a_GLfloat29_0) {
        for (size_t _jGLfloat29 = 0; _jGLfloat29 < _a_GLfloat29_0->values.size(); ++_jGLfloat29) {
    value[_jGLfloat29] = (*_a_GLfloat29_0->values[_jGLfloat29]).toFloat();
        }
    }

    glProgramUniformMatrix2x3fvEXT(program, location, count, transpose, value);
}

static void retrace_glProgramUniformMatrix2x4fvEXT(trace::Call &call) {
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

    GLint location;
    location = (call.arg(1)).toSInt();
    if (retrace::verbosity >= 2) {
        std::cout << "location " << size_t(location) << " <- " << size_t(_location_map[program].lookupUniformLocation(location)) << "\n";
    }
    location = _location_map[program].lookupUniformLocation(location);

    GLsizei count;
    count = (call.arg(2)).toSInt();

    GLboolean transpose;
    transpose = static_cast<GLboolean>((call.arg(3)).toSInt());

    GLfloat * value;
    value = _allocator.allocArray<GLfloat>(&call.arg(4));
    const trace::Array *_a_GLfloat30_0 = (call.arg(4)).toArray();
    if (_a_GLfloat30_0) {
        for (size_t _jGLfloat30 = 0; _jGLfloat30 < _a_GLfloat30_0->values.size(); ++_jGLfloat30) {
    value[_jGLfloat30] = (*_a_GLfloat30_0->values[_jGLfloat30]).toFloat();
        }
    }

    glProgramUniformMatrix2x4fvEXT(program, location, count, transpose, value);
}

static void retrace_glProgramUniformMatrix3fvEXT(trace::Call &call) {
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

    GLint location;
    location = (call.arg(1)).toSInt();
    if (retrace::verbosity >= 2) {
        std::cout << "location " << size_t(location) << " <- " << size_t(_location_map[program].lookupUniformLocation(location)) << "\n";
    }
    location = _location_map[program].lookupUniformLocation(location);

    GLsizei count;
    count = (call.arg(2)).toSInt();

    GLboolean transpose;
    transpose = static_cast<GLboolean>((call.arg(3)).toSInt());

    GLfloat * value;
    value = _allocator.allocArray<GLfloat>(&call.arg(4));
    const trace::Array *_a_GLfloat31_0 = (call.arg(4)).toArray();
    if (_a_GLfloat31_0) {
        for (size_t _jGLfloat31 = 0; _jGLfloat31 < _a_GLfloat31_0->values.size(); ++_jGLfloat31) {
    value[_jGLfloat31] = (*_a_GLfloat31_0->values[_jGLfloat31]).toFloat();
        }
    }

    glProgramUniformMatrix3fvEXT(program, location, count, transpose, value);
}

static void retrace_glProgramUniformMatrix3x2fvEXT(trace::Call &call) {
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

    GLint location;
    location = (call.arg(1)).toSInt();
    if (retrace::verbosity >= 2) {
        std::cout << "location " << size_t(location) << " <- " << size_t(_location_map[program].lookupUniformLocation(location)) << "\n";
    }
    location = _location_map[program].lookupUniformLocation(location);

    GLsizei count;
    count = (call.arg(2)).toSInt();

    GLboolean transpose;
    transpose = static_cast<GLboolean>((call.arg(3)).toSInt());

    GLfloat * value;
    value = _allocator.allocArray<GLfloat>(&call.arg(4));
    const trace::Array *_a_GLfloat32_0 = (call.arg(4)).toArray();
    if (_a_GLfloat32_0) {
        for (size_t _jGLfloat32 = 0; _jGLfloat32 < _a_GLfloat32_0->values.size(); ++_jGLfloat32) {
    value[_jGLfloat32] = (*_a_GLfloat32_0->values[_jGLfloat32]).toFloat();
        }
    }

    glProgramUniformMatrix3x2fvEXT(program, location, count, transpose, value);
}

static void retrace_glProgramUniformMatrix3x4fvEXT(trace::Call &call) {
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

    GLint location;
    location = (call.arg(1)).toSInt();
    if (retrace::verbosity >= 2) {
        std::cout << "location " << size_t(location) << " <- " << size_t(_location_map[program].lookupUniformLocation(location)) << "\n";
    }
    location = _location_map[program].lookupUniformLocation(location);

    GLsizei count;
    count = (call.arg(2)).toSInt();

    GLboolean transpose;
    transpose = static_cast<GLboolean>((call.arg(3)).toSInt());

    GLfloat * value;
    value = _allocator.allocArray<GLfloat>(&call.arg(4));
    const trace::Array *_a_GLfloat33_0 = (call.arg(4)).toArray();
    if (_a_GLfloat33_0) {
        for (size_t _jGLfloat33 = 0; _jGLfloat33 < _a_GLfloat33_0->values.size(); ++_jGLfloat33) {
    value[_jGLfloat33] = (*_a_GLfloat33_0->values[_jGLfloat33]).toFloat();
        }
    }

    glProgramUniformMatrix3x4fvEXT(program, location, count, transpose, value);
}

static void retrace_glProgramUniformMatrix4fvEXT(trace::Call &call) {
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

    GLint location;
    location = (call.arg(1)).toSInt();
    if (retrace::verbosity >= 2) {
        std::cout << "location " << size_t(location) << " <- " << size_t(_location_map[program].lookupUniformLocation(location)) << "\n";
    }
    location = _location_map[program].lookupUniformLocation(location);

    GLsizei count;
    count = (call.arg(2)).toSInt();

    GLboolean transpose;
    transpose = static_cast<GLboolean>((call.arg(3)).toSInt());

    GLfloat * value;
    value = _allocator.allocArray<GLfloat>(&call.arg(4));
    const trace::Array *_a_GLfloat34_0 = (call.arg(4)).toArray();
    if (_a_GLfloat34_0) {
        for (size_t _jGLfloat34 = 0; _jGLfloat34 < _a_GLfloat34_0->values.size(); ++_jGLfloat34) {
    value[_jGLfloat34] = (*_a_GLfloat34_0->values[_jGLfloat34]).toFloat();
        }
    }

    glProgramUniformMatrix4fvEXT(program, location, count, transpose, value);
}

static void retrace_glProgramUniformMatrix4x2fvEXT(trace::Call &call) {
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

    GLint location;
    location = (call.arg(1)).toSInt();
    if (retrace::verbosity >= 2) {
        std::cout << "location " << size_t(location) << " <- " << size_t(_location_map[program].lookupUniformLocation(location)) << "\n";
    }
    location = _location_map[program].lookupUniformLocation(location);

    GLsizei count;
    count = (call.arg(2)).toSInt();

    GLboolean transpose;
    transpose = static_cast<GLboolean>((call.arg(3)).toSInt());

    GLfloat * value;
    value = _allocator.allocArray<GLfloat>(&call.arg(4));
    const trace::Array *_a_GLfloat35_0 = (call.arg(4)).toArray();
    if (_a_GLfloat35_0) {
        for (size_t _jGLfloat35 = 0; _jGLfloat35 < _a_GLfloat35_0->values.size(); ++_jGLfloat35) {
    value[_jGLfloat35] = (*_a_GLfloat35_0->values[_jGLfloat35]).toFloat();
        }
    }

    glProgramUniformMatrix4x2fvEXT(program, location, count, transpose, value);
}

static void retrace_glProgramUniformMatrix4x3fvEXT(trace::Call &call) {
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

    GLint location;
    location = (call.arg(1)).toSInt();
    if (retrace::verbosity >= 2) {
        std::cout << "location " << size_t(location) << " <- " << size_t(_location_map[program].lookupUniformLocation(location)) << "\n";
    }
    location = _location_map[program].lookupUniformLocation(location);

    GLsizei count;
    count = (call.arg(2)).toSInt();

    GLboolean transpose;
    transpose = static_cast<GLboolean>((call.arg(3)).toSInt());

    GLfloat * value;
    value = _allocator.allocArray<GLfloat>(&call.arg(4));
    const trace::Array *_a_GLfloat36_0 = (call.arg(4)).toArray();
    if (_a_GLfloat36_0) {
        for (size_t _jGLfloat36 = 0; _jGLfloat36 < _a_GLfloat36_0->values.size(); ++_jGLfloat36) {
    value[_jGLfloat36] = (*_a_GLfloat36_0->values[_jGLfloat36]).toFloat();
        }
    }

    glProgramUniformMatrix4x3fvEXT(program, location, count, transpose, value);
}

static void retrace_glTextureStorage1DEXT(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    GLuint texture;
    texture = (call.arg(0)).toUInt();
    if (retrace::verbosity >= 2) {
        std::cout << "texture " << size_t(texture) << " <- " << size_t(_texture_map[texture]) << "\n";
    }
    texture = _texture_map[texture];

    GLenum target;
    target = static_cast<GLenum>((call.arg(1)).toSInt());

    GLsizei levels;
    levels = (call.arg(2)).toSInt();

    GLenum internalformat;
    internalformat = static_cast<GLenum>((call.arg(3)).toSInt());

    GLsizei width;
    width = (call.arg(4)).toSInt();

    glTextureStorage1DEXT(texture, target, levels, internalformat, width);
}

static void retrace_glTextureStorage2DEXT(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    GLuint texture;
    texture = (call.arg(0)).toUInt();
    if (retrace::verbosity >= 2) {
        std::cout << "texture " << size_t(texture) << " <- " << size_t(_texture_map[texture]) << "\n";
    }
    texture = _texture_map[texture];

    GLenum target;
    target = static_cast<GLenum>((call.arg(1)).toSInt());

    GLsizei levels;
    levels = (call.arg(2)).toSInt();

    GLenum internalformat;
    internalformat = static_cast<GLenum>((call.arg(3)).toSInt());

    GLsizei width;
    width = (call.arg(4)).toSInt();

    GLsizei height;
    height = (call.arg(5)).toSInt();

    glTextureStorage2DEXT(texture, target, levels, internalformat, width, height);
}

static void retrace_glTextureStorage3DEXT(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    GLuint texture;
    texture = (call.arg(0)).toUInt();
    if (retrace::verbosity >= 2) {
        std::cout << "texture " << size_t(texture) << " <- " << size_t(_texture_map[texture]) << "\n";
    }
    texture = _texture_map[texture];

    GLenum target;
    target = static_cast<GLenum>((call.arg(1)).toSInt());

    GLsizei levels;
    levels = (call.arg(2)).toSInt();

    GLenum internalformat;
    internalformat = static_cast<GLenum>((call.arg(3)).toSInt());

    GLsizei width;
    width = (call.arg(4)).toSInt();

    GLsizei height;
    height = (call.arg(5)).toSInt();

    GLsizei depth;
    depth = (call.arg(6)).toSInt();

    glTextureStorage3DEXT(texture, target, levels, internalformat, width, height, depth);
}

static void retrace_glDiscardFramebufferEXT(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    GLenum target;
    target = static_cast<GLenum>((call.arg(0)).toSInt());

    GLsizei numAttachments;
    numAttachments = (call.arg(1)).toSInt();

    GLenum * attachments;
    attachments = _allocator.allocArray<GLenum>(&call.arg(2));
    const trace::Array *_a_GLenum6_0 = (call.arg(2)).toArray();
    if (_a_GLenum6_0) {
        for (size_t _jGLenum6 = 0; _jGLenum6 < _a_GLenum6_0->values.size(); ++_jGLenum6) {
    attachments[_jGLenum6] = static_cast<GLenum>((*_a_GLenum6_0->values[_jGLenum6]).toSInt());
        }
    }

    glDiscardFramebufferEXT(target, numAttachments, attachments);
}

static void retrace_glDrawBuffersEXT(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    GLsizei n;
    n = (call.arg(0)).toSInt();

    GLenum * bufs;
    bufs = _allocator.allocArray<GLenum>(&call.arg(1));
    const trace::Array *_a_GLenum7_0 = (call.arg(1)).toArray();
    if (_a_GLenum7_0) {
        for (size_t _jGLenum7 = 0; _jGLenum7 < _a_GLenum7_0->values.size(); ++_jGLenum7) {
    bufs[_jGLenum7] = static_cast<GLenum>((*_a_GLenum7_0->values[_jGLenum7]).toSInt());
        }
    }

    glDrawBuffersEXT(n, bufs);
}

static void retrace_glDrawArraysInstancedEXT(trace::Call &call) {
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

    GLint start;
    start = (call.arg(1)).toSInt();

    GLsizei count;
    count = (call.arg(2)).toSInt();

    GLsizei primcount;
    primcount = (call.arg(3)).toSInt();

    if (retrace::debug) {
        _validateActiveProgram(call);
    }
    glDrawArraysInstancedEXT(mode, start, count, primcount);
    assert(call.flags & trace::CALL_FLAG_RENDER);
}

static void retrace_glDrawElementsInstancedEXT(trace::Call &call) {
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

    GLsizei primcount;
    primcount = (call.arg(4)).toSInt();

    if (retrace::debug) {
        _validateActiveProgram(call);
    }
    glDrawElementsInstancedEXT(mode, count, type, indices, primcount);
    assert(call.flags & trace::CALL_FLAG_RENDER);
}

static void retrace_glRenderbufferStorageMultisampleEXT(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    GLenum target;
    target = static_cast<GLenum>((call.arg(0)).toSInt());

    GLsizei samples;
    samples = (call.arg(1)).toSInt();
    GLint max_samples = 0;
    glGetIntegerv(GL_MAX_SAMPLES, &max_samples);
    if (samples > max_samples) {
        samples = max_samples;
    }

    GLenum internalformat;
    internalformat = static_cast<GLenum>((call.arg(2)).toSInt());

    GLsizei width;
    width = (call.arg(3)).toSInt();

    GLsizei height;
    height = (call.arg(4)).toSInt();

    glRenderbufferStorageMultisampleEXT(target, samples, internalformat, width, height);
}

static void retrace_glFramebufferTextureEXT(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    GLenum target;
    target = static_cast<GLenum>((call.arg(0)).toSInt());

    GLenum attachment;
    attachment = static_cast<GLenum>((call.arg(1)).toSInt());

    GLuint texture;
    texture = (call.arg(2)).toUInt();
    if (retrace::verbosity >= 2) {
        std::cout << "texture " << size_t(texture) << " <- " << size_t(_texture_map[texture]) << "\n";
    }
    texture = _texture_map[texture];

    GLint level;
    level = (call.arg(3)).toSInt();

    glFramebufferTextureEXT(target, attachment, texture, level);
}

static void retrace_glProgramParameteriEXT(trace::Call &call) {
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

    GLenum pname;
    pname = static_cast<GLenum>((call.arg(1)).toSInt());

    GLint value;
    value = (call.arg(2)).toSInt();

    glProgramParameteriEXT(program, pname, value);
}

static void retrace_glVertexAttribDivisorEXT(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    GLuint index;
    index = (call.arg(0)).toUInt();

    GLuint divisor;
    divisor = (call.arg(1)).toUInt();

    glVertexAttribDivisorEXT(index, divisor);
}

static void retrace_glMapBufferRangeEXT(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    GLenum target;
    target = static_cast<GLenum>((call.arg(0)).toSInt());

    GLintptr offset;
    offset = (call.arg(1)).toSInt();

    GLsizeiptr length;
    length = (call.arg(2)).toSInt();

    GLbitfield access;
    access = (call.arg(3)).toUInt();

    GLvoid * _result;
    _result = glMapBufferRangeEXT(target, offset, length, access);
    (void)_result;
    retrace::addRegion(call, (*call.ret).toUIntPtr(), _result, length);
}

static void retrace_glFlushMappedBufferRangeEXT(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    GLenum target;
    target = static_cast<GLenum>((call.arg(0)).toSInt());

    GLintptr offset;
    offset = (call.arg(1)).toSInt();

    GLsizeiptr length;
    length = (call.arg(2)).toSInt();

    glFlushMappedBufferRangeEXT(target, offset, length);
}

static void retrace_glMultiDrawArraysEXT(trace::Call &call) {
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

    GLint * first;
    first = _allocator.allocArray<GLint>(&call.arg(1));
    const trace::Array *_a_GLint30_0 = (call.arg(1)).toArray();
    if (_a_GLint30_0) {
        for (size_t _jGLint30 = 0; _jGLint30 < _a_GLint30_0->values.size(); ++_jGLint30) {
    first[_jGLint30] = (*_a_GLint30_0->values[_jGLint30]).toSInt();
        }
    }

    GLsizei * count;
    count = _allocator.allocArray<GLsizei>(&call.arg(2));
    const trace::Array *_a_GLsizei2_0 = (call.arg(2)).toArray();
    if (_a_GLsizei2_0) {
        for (size_t _jGLsizei2 = 0; _jGLsizei2 < _a_GLsizei2_0->values.size(); ++_jGLsizei2) {
    count[_jGLsizei2] = (*_a_GLsizei2_0->values[_jGLsizei2]).toSInt();
        }
    }

    GLsizei primcount;
    primcount = (call.arg(3)).toSInt();

    if (retrace::debug) {
        _validateActiveProgram(call);
    }
    glMultiDrawArraysEXT(mode, first, count, primcount);
    assert(call.flags & trace::CALL_FLAG_RENDER);
}

static void retrace_glMultiDrawElementsEXT(trace::Call &call) {
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

    GLsizei * count;
    count = _allocator.allocArray<GLsizei>(&call.arg(1));
    const trace::Array *_a_GLsizei3_0 = (call.arg(1)).toArray();
    if (_a_GLsizei3_0) {
        for (size_t _jGLsizei3 = 0; _jGLsizei3 < _a_GLsizei3_0->values.size(); ++_jGLsizei3) {
    count[_jGLsizei3] = (*_a_GLsizei3_0->values[_jGLsizei3]).toSInt();
        }
    }

    GLenum type;
    type = static_cast<GLenum>((call.arg(2)).toSInt());

    const GLvoid * * indices;
    indices = _allocator.allocArray<const GLvoid *>(&call.arg(3));
    const trace::Array *_a_constGLvoid46_0 = (call.arg(3)).toArray();
    if (_a_constGLvoid46_0) {
        for (size_t _jconstGLvoid46 = 0; _jconstGLvoid46 < _a_constGLvoid46_0->values.size(); ++_jconstGLvoid46) {
    indices[_jconstGLvoid46] = static_cast<const GLvoid *>((*_a_constGLvoid46_0->values[_jconstGLvoid46]).toPointer());
        }
    }

    GLsizei primcount;
    primcount = (call.arg(4)).toSInt();

    if (retrace::debug) {
        _validateActiveProgram(call);
    }
    glMultiDrawElementsEXT(mode, count, type, indices, primcount);
    assert(call.flags & trace::CALL_FLAG_RENDER);
}

static void retrace_glFramebufferTexture2DMultisampleEXT(trace::Call &call) {
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

    GLsizei samples;
    samples = (call.arg(5)).toSInt();
    GLint max_samples = 0;
    glGetIntegerv(GL_MAX_SAMPLES, &max_samples);
    if (samples > max_samples) {
        samples = max_samples;
    }

    glFramebufferTexture2DMultisampleEXT(target, attachment, textarget, texture, level, samples);
}

static void retrace_glGenQueriesEXT(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    GLsizei n;
    n = (call.arg(0)).toSInt();

    GLuint * ids;
    ids = _allocator.allocArray<GLuint>(&call.arg(1));

    glGenQueriesEXT(n, ids);
    const trace::Array *_aGLuint46 = (call.arg(1)).toArray();
    if (_aGLuint46) {
        for (size_t _jGLuint46 = 0; _jGLuint46 < _aGLuint46->values.size(); ++_jGLuint46) {
    GLuint _origResult;
    _origResult = (*_aGLuint46->values[_jGLuint46]).toUInt();
    _query_map[_origResult] = ids[_jGLuint46];
    if (retrace::verbosity >= 2) {
        std::cout << "query " << _origResult << " -> " << ids[_jGLuint46] << "\n";
    }
        }
    }
}

static void retrace_glDeleteQueriesEXT(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    GLsizei n;
    n = (call.arg(0)).toSInt();

    GLuint * ids;
    ids = _allocator.allocArray<GLuint>(&call.arg(1));
    const trace::Array *_a_GLuint47_0 = (call.arg(1)).toArray();
    if (_a_GLuint47_0) {
        for (size_t _jGLuint47 = 0; _jGLuint47 < _a_GLuint47_0->values.size(); ++_jGLuint47) {
    ids[_jGLuint47] = (*_a_GLuint47_0->values[_jGLuint47]).toUInt();
    if (retrace::verbosity >= 2) {
        std::cout << "query " << size_t(ids[_jGLuint47]) << " <- " << size_t(_query_map[ids[_jGLuint47]]) << "\n";
    }
    ids[_jGLuint47] = _query_map[ids[_jGLuint47]];
        }
    }

    glDeleteQueriesEXT(n, ids);
}

static void retrace_glBeginQueryEXT(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    GLenum target;
    target = static_cast<GLenum>((call.arg(0)).toSInt());

    GLuint id;
    id = (call.arg(1)).toUInt();
    if (retrace::verbosity >= 2) {
        std::cout << "query " << size_t(id) << " <- " << size_t(_query_map[id]) << "\n";
    }
    id = _query_map[id];

    glBeginQueryEXT(target, id);
}

static void retrace_glEndQueryEXT(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    GLenum target;
    target = static_cast<GLenum>((call.arg(0)).toSInt());

    glEndQueryEXT(target);
}

static void retrace_glPrimitiveBoundingBoxEXT(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    GLfloat minX;
    minX = (call.arg(0)).toFloat();

    GLfloat minY;
    minY = (call.arg(1)).toFloat();

    GLfloat minZ;
    minZ = (call.arg(2)).toFloat();

    GLfloat minW;
    minW = (call.arg(3)).toFloat();

    GLfloat maxX;
    maxX = (call.arg(4)).toFloat();

    GLfloat maxY;
    maxY = (call.arg(5)).toFloat();

    GLfloat maxZ;
    maxZ = (call.arg(6)).toFloat();

    GLfloat maxW;
    maxW = (call.arg(7)).toFloat();

    glPrimitiveBoundingBoxEXT(minX, minY, minZ, minW, maxX, maxY, maxZ, maxW);
}

static void retrace_glRasterSamplesEXT(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    GLuint samples;
    samples = (call.arg(0)).toUInt();
    GLint max_samples = 0;
    glGetIntegerv(GL_MAX_RASTER_SAMPLES_EXT, &max_samples);
    if (samples > static_cast<GLuint>(max_samples)) {
        samples = static_cast<GLuint>(max_samples);
    }

    GLboolean fixedsamplelocations;
    fixedsamplelocations = static_cast<GLboolean>((call.arg(1)).toSInt());

    glRasterSamplesEXT(samples, fixedsamplelocations);
}

static void retrace_glActiveShaderProgramEXT(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    GLuint pipeline;
    pipeline = (call.arg(0)).toUInt();
    if (retrace::verbosity >= 2) {
        std::cout << "pipeline " << size_t(pipeline) << " <- " << size_t(_pipeline_map[pipeline]) << "\n";
    }
    pipeline = _pipeline_map[pipeline];

    GLuint program;
    program = (call.arg(1)).toUInt();
    if (retrace::verbosity >= 2) {
        std::cout << "program " << size_t(program) << " <- " << size_t(_program_map[program]) << "\n";
    }
if (glretrace::supportsARBShaderObjects) {
    program = _handleARB_map[program];
} else {
    program = _program_map[program];
}

    glActiveShaderProgramEXT(pipeline, program);
}

static void retrace_glBindProgramPipelineEXT(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    GLuint pipeline;
    pipeline = (call.arg(0)).toUInt();
    if (retrace::verbosity >= 2) {
        std::cout << "pipeline " << size_t(pipeline) << " <- " << size_t(_pipeline_map[pipeline]) << "\n";
    }
    pipeline = _pipeline_map[pipeline];

    if (pipeline) {
        _pipelineHasBeenBound = true;
    }
    glBindProgramPipelineEXT(pipeline);
}

static void retrace_glCreateShaderProgramvEXT(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    GLenum type;
    type = static_cast<GLenum>((call.arg(0)).toSInt());

    GLsizei count;
    count = (call.arg(1)).toSInt();

    const GLchar * * strings;
    strings = _allocator.allocArray<const GLchar *>(&call.arg(2));
    const trace::Array *_a_constGLchar4_0 = (call.arg(2)).toArray();
    if (_a_constGLchar4_0) {
        for (size_t _jconstGLchar4 = 0; _jconstGLchar4 < _a_constGLchar4_0->values.size(); ++_jconstGLchar4) {
    strings[_jconstGLchar4] = (const GLchar *)((*_a_constGLchar4_0->values[_jconstGLchar4]).toString());
        }
    }

    GLuint _result;
    if (retrace::dumpingState) {
        GLuint _shader = glCreateShader(type);
        if (_shader) {
            glShaderSource(_shader, count, strings, NULL);
            glCompileShader(_shader);
            const GLuint _program = glCreateProgram();
            if (_program) {
                GLint compiled = GL_FALSE;
                glGetShaderiv(_shader, GL_COMPILE_STATUS, &compiled);
                glProgramParameteriEXT(_program, GL_PROGRAM_SEPARABLE, GL_TRUE);
                if (compiled) {
                    glAttachShader(_program, _shader);
                    glLinkProgram(_program);
                    if (false) glDetachShader(_program, _shader);
                }
                // TODO: append shader info log to program info log
            }
            glDeleteShader(_shader);
            _result = _program;
        } else {
            _result = 0;
        }
    } else {
    _result = glCreateShaderProgramvEXT(type, count, strings);
    (void)_result;
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

static void retrace_glDeleteProgramPipelinesEXT(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    GLsizei n;
    n = (call.arg(0)).toSInt();

    GLuint * pipelines;
    pipelines = _allocator.allocArray<GLuint>(&call.arg(1));
    const trace::Array *_a_GLuint48_0 = (call.arg(1)).toArray();
    if (_a_GLuint48_0) {
        for (size_t _jGLuint48 = 0; _jGLuint48 < _a_GLuint48_0->values.size(); ++_jGLuint48) {
    pipelines[_jGLuint48] = (*_a_GLuint48_0->values[_jGLuint48]).toUInt();
        }
    }

    glDeleteProgramPipelinesEXT(n, pipelines);
}

static void retrace_glGenProgramPipelinesEXT(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    GLsizei n;
    n = (call.arg(0)).toSInt();

    GLuint * pipelines;
    pipelines = _allocator.allocArray<GLuint>(&call.arg(1));

    glGenProgramPipelinesEXT(n, pipelines);
    const trace::Array *_aGLuint50 = (call.arg(1)).toArray();
    if (_aGLuint50) {
        for (size_t _jGLuint50 = 0; _jGLuint50 < _aGLuint50->values.size(); ++_jGLuint50) {
    GLuint _origResult;
    _origResult = (*_aGLuint50->values[_jGLuint50]).toUInt();
    _pipeline_map[_origResult] = pipelines[_jGLuint50];
    if (retrace::verbosity >= 2) {
        std::cout << "pipeline " << _origResult << " -> " << pipelines[_jGLuint50] << "\n";
    }
        }
    }
}

static void retrace_glUseProgramStagesEXT(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    GLuint pipeline;
    pipeline = (call.arg(0)).toUInt();
    if (retrace::verbosity >= 2) {
        std::cout << "pipeline " << size_t(pipeline) << " <- " << size_t(_pipeline_map[pipeline]) << "\n";
    }
    pipeline = _pipeline_map[pipeline];

    GLbitfield stages;
    stages = (call.arg(1)).toUInt();

    GLuint program;
    program = (call.arg(2)).toUInt();
    if (retrace::verbosity >= 2) {
        std::cout << "program " << size_t(program) << " <- " << size_t(_program_map[program]) << "\n";
    }
if (glretrace::supportsARBShaderObjects) {
    program = _handleARB_map[program];
} else {
    program = _program_map[program];
}

    glUseProgramStagesEXT(pipeline, stages, program);
}

static void retrace_glValidateProgramPipelineEXT(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    GLuint pipeline;
    pipeline = (call.arg(0)).toUInt();
    if (retrace::verbosity >= 2) {
        std::cout << "pipeline " << size_t(pipeline) << " <- " << size_t(_pipeline_map[pipeline]) << "\n";
    }
    pipeline = _pipeline_map[pipeline];

    glValidateProgramPipelineEXT(pipeline);
}

static void retrace_glPatchParameteriEXT(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    GLenum pname;
    pname = static_cast<GLenum>((call.arg(0)).toSInt());

    GLint value;
    value = (call.arg(1)).toSInt();

    glPatchParameteriEXT(pname, value);
}

static void retrace_glTexBufferEXT(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    GLenum target;
    target = static_cast<GLenum>((call.arg(0)).toSInt());

    GLenum internalformat;
    internalformat = static_cast<GLenum>((call.arg(1)).toSInt());

    GLuint buffer;
    buffer = (call.arg(2)).toUInt();
    if (retrace::verbosity >= 2) {
        std::cout << "buffer " << size_t(buffer) << " <- " << size_t(_buffer_map[buffer]) << "\n";
    }
    buffer = _buffer_map[buffer];

    glTexBufferEXT(target, internalformat, buffer);
}

static void retrace_glTexBufferRangeEXT(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    GLenum target;
    target = static_cast<GLenum>((call.arg(0)).toSInt());

    GLenum internalformat;
    internalformat = static_cast<GLenum>((call.arg(1)).toSInt());

    GLuint buffer;
    buffer = (call.arg(2)).toUInt();
    if (retrace::verbosity >= 2) {
        std::cout << "buffer " << size_t(buffer) << " <- " << size_t(_buffer_map[buffer]) << "\n";
    }
    buffer = _buffer_map[buffer];

    GLintptr offset;
    offset = (call.arg(3)).toSInt();

    GLsizeiptr size;
    size = (call.arg(4)).toSInt();

    glTexBufferRangeEXT(target, internalformat, buffer, offset, size);
}

static void retrace_glTexParameterIivEXT(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    GLenum target;
    target = static_cast<GLenum>((call.arg(0)).toSInt());

    GLenum pname;
    pname = static_cast<GLenum>((call.arg(1)).toSInt());

    GLint * params;
    params = _allocator.allocArray<GLint>(&call.arg(2));
    const trace::Array *_a_GLint31_0 = (call.arg(2)).toArray();
    if (_a_GLint31_0) {
        for (size_t _jGLint31 = 0; _jGLint31 < _a_GLint31_0->values.size(); ++_jGLint31) {
    params[_jGLint31] = (*_a_GLint31_0->values[_jGLint31]).toSInt();
        }
    }

    glTexParameterIivEXT(target, pname, params);
}

static void retrace_glTexParameterIuivEXT(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    GLenum target;
    target = static_cast<GLenum>((call.arg(0)).toSInt());

    GLenum pname;
    pname = static_cast<GLenum>((call.arg(1)).toSInt());

    GLuint * params;
    params = _allocator.allocArray<GLuint>(&call.arg(2));
    const trace::Array *_a_GLuint51_0 = (call.arg(2)).toArray();
    if (_a_GLuint51_0) {
        for (size_t _jGLuint51 = 0; _jGLuint51 < _a_GLuint51_0->values.size(); ++_jGLuint51) {
    params[_jGLuint51] = (*_a_GLuint51_0->values[_jGLuint51]).toUInt();
        }
    }

    glTexParameterIuivEXT(target, pname, params);
}

static void retrace_glTexStorage1DEXT(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    GLenum target;
    target = static_cast<GLenum>((call.arg(0)).toSInt());

    GLsizei levels;
    levels = (call.arg(1)).toSInt();

    GLenum internalformat;
    internalformat = static_cast<GLenum>((call.arg(2)).toSInt());

    GLsizei width;
    width = (call.arg(3)).toSInt();

    glTexStorage1DEXT(target, levels, internalformat, width);
}

static void retrace_glTexStorage2DEXT(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    GLenum target;
    target = static_cast<GLenum>((call.arg(0)).toSInt());

    GLsizei levels;
    levels = (call.arg(1)).toSInt();

    GLenum internalformat;
    internalformat = static_cast<GLenum>((call.arg(2)).toSInt());

    GLsizei width;
    width = (call.arg(3)).toSInt();

    GLsizei height;
    height = (call.arg(4)).toSInt();

    glTexStorage2DEXT(target, levels, internalformat, width, height);
}

static void retrace_glTexStorage3DEXT(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    GLenum target;
    target = static_cast<GLenum>((call.arg(0)).toSInt());

    GLsizei levels;
    levels = (call.arg(1)).toSInt();

    GLenum internalformat;
    internalformat = static_cast<GLenum>((call.arg(2)).toSInt());

    GLsizei width;
    width = (call.arg(3)).toSInt();

    GLsizei height;
    height = (call.arg(4)).toSInt();

    GLsizei depth;
    depth = (call.arg(5)).toSInt();

    glTexStorage3DEXT(target, levels, internalformat, width, height, depth);
}

static void retrace_glTextureViewEXT(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    GLuint texture;
    texture = (call.arg(0)).toUInt();
    if (retrace::verbosity >= 2) {
        std::cout << "texture " << size_t(texture) << " <- " << size_t(_texture_map[texture]) << "\n";
    }
    texture = _texture_map[texture];

    GLenum target;
    target = static_cast<GLenum>((call.arg(1)).toSInt());

    GLuint origtexture;
    origtexture = (call.arg(2)).toUInt();
    if (retrace::verbosity >= 2) {
        std::cout << "texture " << size_t(origtexture) << " <- " << size_t(_texture_map[origtexture]) << "\n";
    }
    origtexture = _texture_map[origtexture];

    GLenum internalformat;
    internalformat = static_cast<GLenum>((call.arg(3)).toSInt());

    GLuint minlevel;
    minlevel = (call.arg(4)).toUInt();

    GLuint numlevels;
    numlevels = (call.arg(5)).toUInt();

    GLuint minlayer;
    minlayer = (call.arg(6)).toUInt();

    GLuint numlayers;
    numlayers = (call.arg(7)).toUInt();

    glTextureViewEXT(texture, target, origtexture, internalformat, minlevel, numlevels, minlayer, numlayers);
}

static void retrace_glRenderbufferStorageMultisampleIMG(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    GLenum target;
    target = static_cast<GLenum>((call.arg(0)).toSInt());

    GLsizei samples;
    samples = (call.arg(1)).toSInt();
    GLint max_samples = 0;
    glGetIntegerv(GL_MAX_SAMPLES, &max_samples);
    if (samples > max_samples) {
        samples = max_samples;
    }

    GLenum internalformat;
    internalformat = static_cast<GLenum>((call.arg(2)).toSInt());

    GLsizei width;
    width = (call.arg(3)).toSInt();

    GLsizei height;
    height = (call.arg(4)).toSInt();

    glRenderbufferStorageMultisampleIMG(target, samples, internalformat, width, height);
}

static void retrace_glFramebufferTexture2DMultisampleIMG(trace::Call &call) {
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

    GLsizei samples;
    samples = (call.arg(5)).toSInt();
    GLint max_samples = 0;
    glGetIntegerv(GL_MAX_SAMPLES, &max_samples);
    if (samples > max_samples) {
        samples = max_samples;
    }

    glFramebufferTexture2DMultisampleIMG(target, attachment, textarget, texture, level, samples);
}

static void retrace_glBlendBarrierKHR(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    glBlendBarrierKHR();
}

static void retrace_glDebugMessageControlKHR(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    GLenum source;
    source = static_cast<GLenum>((call.arg(0)).toSInt());

    GLenum type;
    type = static_cast<GLenum>((call.arg(1)).toSInt());

    GLenum severity;
    severity = static_cast<GLenum>((call.arg(2)).toSInt());

    GLsizei count;
    count = (call.arg(3)).toSInt();

    GLuint * ids;
    ids = _allocator.allocArray<GLuint>(&call.arg(4));
    const trace::Array *_a_GLuint52_0 = (call.arg(4)).toArray();
    if (_a_GLuint52_0) {
        for (size_t _jGLuint52 = 0; _jGLuint52 < _a_GLuint52_0->values.size(); ++_jGLuint52) {
    ids[_jGLuint52] = (*_a_GLuint52_0->values[_jGLuint52]).toUInt();
        }
    }

    GLboolean enabled;
    enabled = static_cast<GLboolean>((call.arg(5)).toSInt());

    glDebugMessageControlKHR(source, type, severity, count, ids, enabled);
}

static void retrace_glDebugMessageInsertKHR(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    GLenum source;
    source = static_cast<GLenum>((call.arg(0)).toSInt());

    GLenum type;
    type = static_cast<GLenum>((call.arg(1)).toSInt());

    GLuint id;
    id = (call.arg(2)).toUInt();

    GLenum severity;
    severity = static_cast<GLenum>((call.arg(3)).toSInt());

    GLsizei length;
    length = (call.arg(4)).toSInt();

    const GLchar * buf;
    buf = (const GLchar *)((call.arg(5)).toString());

    glDebugMessageInsertKHR(source, type, id, severity, length, buf);
}

static void retrace_glPushDebugGroupKHR(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    GLenum source;
    source = static_cast<GLenum>((call.arg(0)).toSInt());

    GLuint id;
    id = (call.arg(1)).toUInt();

    GLsizei length;
    length = (call.arg(2)).toSInt();

    const GLchar * message;
    message = (const GLchar *)((call.arg(3)).toString());

    glPushDebugGroupKHR(source, id, length, message);
}

static void retrace_glPopDebugGroupKHR(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    glPopDebugGroupKHR();
}

static void retrace_glObjectLabelKHR(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    GLenum identifier;
    identifier = static_cast<GLenum>((call.arg(0)).toSInt());

    GLuint name;
    name = (call.arg(1)).toUInt();

    GLsizei length;
    length = (call.arg(2)).toSInt();

    const GLchar * label;
    label = (const GLchar *)((call.arg(3)).toString());

    glObjectLabelKHR(identifier, name, length, label);
}

static void retrace_glObjectPtrLabelKHR(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    const void * ptr;
    memset(&ptr, 0, sizeof ptr); // FIXME

    GLsizei length;
    length = (call.arg(1)).toSInt();

    const GLchar * label;
    label = (const GLchar *)((call.arg(2)).toString());

    if (1) {
    if (retrace::verbosity >= 0) {
        retrace::unsupported(call);
    }
    return;
    }
    glObjectPtrLabelKHR(ptr, length, label);
}

static void retrace_glGetTextureHandleNV(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    GLuint texture;
    texture = (call.arg(0)).toUInt();
    if (retrace::verbosity >= 2) {
        std::cout << "texture " << size_t(texture) << " <- " << size_t(_texture_map[texture]) << "\n";
    }
    texture = _texture_map[texture];

    GLuint64 _result;
    _result = glGetTextureHandleNV(texture);
    (void)_result;
    GLuint64 _origResult;
    _origResult = (*call.ret).toUInt();
    _textureHandle_map[_origResult] = _result;
    if (retrace::verbosity >= 2) {
        std::cout << "textureHandle " << _origResult << " -> " << _result << "\n";
    }
}

static void retrace_glGetTextureSamplerHandleNV(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    GLuint texture;
    texture = (call.arg(0)).toUInt();
    if (retrace::verbosity >= 2) {
        std::cout << "texture " << size_t(texture) << " <- " << size_t(_texture_map[texture]) << "\n";
    }
    texture = _texture_map[texture];

    GLuint sampler;
    sampler = (call.arg(1)).toUInt();
    if (retrace::verbosity >= 2) {
        std::cout << "sampler " << size_t(sampler) << " <- " << size_t(_sampler_map[sampler]) << "\n";
    }
    sampler = _sampler_map[sampler];

    GLuint64 _result;
    _result = glGetTextureSamplerHandleNV(texture, sampler);
    (void)_result;
    GLuint64 _origResult;
    _origResult = (*call.ret).toUInt();
    _textureHandle_map[_origResult] = _result;
    if (retrace::verbosity >= 2) {
        std::cout << "textureHandle " << _origResult << " -> " << _result << "\n";
    }
}

static void retrace_glMakeTextureHandleResidentNV(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    GLuint64 handle;
    handle = (call.arg(0)).toUInt();
    if (retrace::verbosity >= 2) {
        std::cout << "textureHandle " << size_t(handle) << " <- " << size_t(_textureHandle_map[handle]) << "\n";
    }
    handle = _textureHandle_map[handle];

    glMakeTextureHandleResidentNV(handle);
}

static void retrace_glMakeTextureHandleNonResidentNV(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    GLuint64 handle;
    handle = (call.arg(0)).toUInt();
    if (retrace::verbosity >= 2) {
        std::cout << "textureHandle " << size_t(handle) << " <- " << size_t(_textureHandle_map[handle]) << "\n";
    }
    handle = _textureHandle_map[handle];

    glMakeTextureHandleNonResidentNV(handle);
}

static void retrace_glGetImageHandleNV(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    GLuint texture;
    texture = (call.arg(0)).toUInt();
    if (retrace::verbosity >= 2) {
        std::cout << "texture " << size_t(texture) << " <- " << size_t(_texture_map[texture]) << "\n";
    }
    texture = _texture_map[texture];

    GLint level;
    level = (call.arg(1)).toSInt();

    GLboolean layered;
    layered = static_cast<GLboolean>((call.arg(2)).toSInt());

    GLint layer;
    layer = (call.arg(3)).toSInt();

    GLenum format;
    format = static_cast<GLenum>((call.arg(4)).toSInt());

    GLuint64 _result;
    _result = glGetImageHandleNV(texture, level, layered, layer, format);
    (void)_result;
    GLuint64 _origResult;
    _origResult = (*call.ret).toUInt();
    _textureHandle_map[_origResult] = _result;
    if (retrace::verbosity >= 2) {
        std::cout << "textureHandle " << _origResult << " -> " << _result << "\n";
    }
}

static void retrace_glMakeImageHandleResidentNV(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    GLuint64 handle;
    handle = (call.arg(0)).toUInt();
    if (retrace::verbosity >= 2) {
        std::cout << "textureHandle " << size_t(handle) << " <- " << size_t(_textureHandle_map[handle]) << "\n";
    }
    handle = _textureHandle_map[handle];

    GLenum access;
    access = static_cast<GLenum>((call.arg(1)).toSInt());

    glMakeImageHandleResidentNV(handle, access);
}

static void retrace_glMakeImageHandleNonResidentNV(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    GLuint64 handle;
    handle = (call.arg(0)).toUInt();
    if (retrace::verbosity >= 2) {
        std::cout << "textureHandle " << size_t(handle) << " <- " << size_t(_textureHandle_map[handle]) << "\n";
    }
    handle = _textureHandle_map[handle];

    glMakeImageHandleNonResidentNV(handle);
}

static void retrace_glUniformHandleui64NV(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    GLint location;
    GLint program = _getActiveProgram();
    location = (call.arg(0)).toSInt();
    if (retrace::verbosity >= 2) {
        std::cout << "location " << size_t(location) << " <- " << size_t(_location_map[program].lookupUniformLocation(location)) << "\n";
    }
    location = _location_map[program].lookupUniformLocation(location);

    GLuint64 value;
    value = (call.arg(1)).toUInt();
    if (retrace::verbosity >= 2) {
        std::cout << "textureHandle " << size_t(value) << " <- " << size_t(_textureHandle_map[value]) << "\n";
    }
    value = _textureHandle_map[value];

    glUniformHandleui64NV(location, value);
}

static void retrace_glUniformHandleui64vNV(trace::Call &call) {
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

    GLuint64 * value;
    value = _allocator.allocArray<GLuint64>(&call.arg(2));
    const trace::Array *_a_GLuint641_0 = (call.arg(2)).toArray();
    if (_a_GLuint641_0) {
        for (size_t _jGLuint641 = 0; _jGLuint641 < _a_GLuint641_0->values.size(); ++_jGLuint641) {
    value[_jGLuint641] = (*_a_GLuint641_0->values[_jGLuint641]).toUInt();
    if (retrace::verbosity >= 2) {
        std::cout << "textureHandle " << size_t(value[_jGLuint641]) << " <- " << size_t(_textureHandle_map[value[_jGLuint641]]) << "\n";
    }
    value[_jGLuint641] = _textureHandle_map[value[_jGLuint641]];
        }
    }

    glUniformHandleui64vNV(location, count, value);
}

static void retrace_glProgramUniformHandleui64NV(trace::Call &call) {
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

    GLint location;
    location = (call.arg(1)).toSInt();
    if (retrace::verbosity >= 2) {
        std::cout << "location " << size_t(location) << " <- " << size_t(_location_map[program].lookupUniformLocation(location)) << "\n";
    }
    location = _location_map[program].lookupUniformLocation(location);

    GLuint64 value;
    value = (call.arg(2)).toUInt();
    if (retrace::verbosity >= 2) {
        std::cout << "textureHandle " << size_t(value) << " <- " << size_t(_textureHandle_map[value]) << "\n";
    }
    value = _textureHandle_map[value];

    glProgramUniformHandleui64NV(program, location, value);
}

static void retrace_glProgramUniformHandleui64vNV(trace::Call &call) {
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

    GLint location;
    location = (call.arg(1)).toSInt();
    if (retrace::verbosity >= 2) {
        std::cout << "location " << size_t(location) << " <- " << size_t(_location_map[program].lookupUniformLocation(location)) << "\n";
    }
    location = _location_map[program].lookupUniformLocation(location);

    GLsizei count;
    count = (call.arg(2)).toSInt();

    GLuint64 * values;
    values = _allocator.allocArray<GLuint64>(&call.arg(3));
    const trace::Array *_a_GLuint642_0 = (call.arg(3)).toArray();
    if (_a_GLuint642_0) {
        for (size_t _jGLuint642 = 0; _jGLuint642 < _a_GLuint642_0->values.size(); ++_jGLuint642) {
    values[_jGLuint642] = (*_a_GLuint642_0->values[_jGLuint642]).toUInt();
    if (retrace::verbosity >= 2) {
        std::cout << "textureHandle " << size_t(values[_jGLuint642]) << " <- " << size_t(_textureHandle_map[values[_jGLuint642]]) << "\n";
    }
    values[_jGLuint642] = _textureHandle_map[values[_jGLuint642]];
        }
    }

    glProgramUniformHandleui64vNV(program, location, count, values);
}

static void retrace_glBlendParameteriNV(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    GLenum pname;
    pname = static_cast<GLenum>((call.arg(0)).toSInt());

    GLint value;
    value = (call.arg(1)).toSInt();

    glBlendParameteriNV(pname, value);
}

static void retrace_glBlendBarrierNV(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    glBlendBarrierNV();
}

static void retrace_glBeginConditionalRenderNV(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    GLuint id;
    id = (call.arg(0)).toUInt();
    if (retrace::verbosity >= 2) {
        std::cout << "query " << size_t(id) << " <- " << size_t(_query_map[id]) << "\n";
    }
    id = _query_map[id];

    GLenum mode;
    mode = static_cast<GLenum>((call.arg(1)).toSInt());

    glBeginConditionalRenderNV(id, mode);
}

static void retrace_glEndConditionalRenderNV(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    glEndConditionalRenderNV();
}

static void retrace_glCoverageMaskNV(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    GLboolean mask;
    mask = static_cast<GLboolean>((call.arg(0)).toSInt());

    glCoverageMaskNV(mask);
}

static void retrace_glCoverageOperationNV(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    GLenum operation;
    operation = static_cast<GLenum>((call.arg(0)).toSInt());

    glCoverageOperationNV(operation);
}

static void retrace_glDrawBuffersNV(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    GLsizei n;
    n = (call.arg(0)).toSInt();

    GLenum * bufs;
    bufs = _allocator.allocArray<GLenum>(&call.arg(1));
    const trace::Array *_a_GLenum8_0 = (call.arg(1)).toArray();
    if (_a_GLenum8_0) {
        for (size_t _jGLenum8 = 0; _jGLenum8 < _a_GLenum8_0->values.size(); ++_jGLenum8) {
    bufs[_jGLenum8] = static_cast<GLenum>((*_a_GLenum8_0->values[_jGLenum8]).toSInt());
        }
    }

    glDrawBuffersNV(n, bufs);
}

static void retrace_glDeleteFencesNV(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    GLsizei n;
    n = (call.arg(0)).toSInt();

    GLuint * fences;
    fences = _allocator.allocArray<GLuint>(&call.arg(1));
    const trace::Array *_a_GLuint53_0 = (call.arg(1)).toArray();
    if (_a_GLuint53_0) {
        for (size_t _jGLuint53 = 0; _jGLuint53 < _a_GLuint53_0->values.size(); ++_jGLuint53) {
    fences[_jGLuint53] = (*_a_GLuint53_0->values[_jGLuint53]).toUInt();
    if (retrace::verbosity >= 2) {
        std::cout << "fence " << size_t(fences[_jGLuint53]) << " <- " << size_t(_fence_map[fences[_jGLuint53]]) << "\n";
    }
    fences[_jGLuint53] = _fence_map[fences[_jGLuint53]];
        }
    }

    glDeleteFencesNV(n, fences);
}

static void retrace_glGenFencesNV(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    GLsizei n;
    n = (call.arg(0)).toSInt();

    GLuint * fences;
    fences = _allocator.allocArray<GLuint>(&call.arg(1));

    glGenFencesNV(n, fences);
    const trace::Array *_aGLuint55 = (call.arg(1)).toArray();
    if (_aGLuint55) {
        for (size_t _jGLuint55 = 0; _jGLuint55 < _aGLuint55->values.size(); ++_jGLuint55) {
    GLuint _origResult;
    _origResult = (*_aGLuint55->values[_jGLuint55]).toUInt();
    _fence_map[_origResult] = fences[_jGLuint55];
    if (retrace::verbosity >= 2) {
        std::cout << "fence " << _origResult << " -> " << fences[_jGLuint55] << "\n";
    }
        }
    }
}

static void retrace_glTestFenceNV(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    GLuint fence;
    fence = (call.arg(0)).toUInt();
    if (retrace::verbosity >= 2) {
        std::cout << "fence " << size_t(fence) << " <- " << size_t(_fence_map[fence]) << "\n";
    }
    fence = _fence_map[fence];

    GLboolean _result;
    _result = glTestFenceNV(fence);
    (void)_result;
}

static void retrace_glFinishFenceNV(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    GLuint fence;
    fence = (call.arg(0)).toUInt();
    if (retrace::verbosity >= 2) {
        std::cout << "fence " << size_t(fence) << " <- " << size_t(_fence_map[fence]) << "\n";
    }
    fence = _fence_map[fence];

    glFinishFenceNV(fence);
}

static void retrace_glSetFenceNV(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    GLuint fence;
    fence = (call.arg(0)).toUInt();
    if (retrace::verbosity >= 2) {
        std::cout << "fence " << size_t(fence) << " <- " << size_t(_fence_map[fence]) << "\n";
    }
    fence = _fence_map[fence];

    GLenum condition;
    condition = static_cast<GLenum>((call.arg(1)).toSInt());

    glSetFenceNV(fence, condition);
}

static void retrace_glBlitFramebufferNV(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    GLint srcX0;
    srcX0 = (call.arg(0)).toSInt();

    GLint srcY0;
    srcY0 = (call.arg(1)).toSInt();

    GLint srcX1;
    srcX1 = (call.arg(2)).toSInt();

    GLint srcY1;
    srcY1 = (call.arg(3)).toSInt();

    GLint dstX0;
    dstX0 = (call.arg(4)).toSInt();

    GLint dstY0;
    dstY0 = (call.arg(5)).toSInt();

    GLint dstX1;
    dstX1 = (call.arg(6)).toSInt();

    GLint dstY1;
    dstY1 = (call.arg(7)).toSInt();

    GLbitfield mask;
    mask = (call.arg(8)).toUInt();

    GLenum filter;
    filter = static_cast<GLenum>((call.arg(9)).toSInt());

    glBlitFramebufferNV(srcX0, srcY0, srcX1, srcY1, dstX0, dstY0, dstX1, dstY1, mask, filter);
    assert(call.flags & trace::CALL_FLAG_RENDER);
}

static void retrace_glCoverageModulationTableNV(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    GLsizei n;
    n = (call.arg(0)).toSInt();

    GLfloat * v;
    v = _allocator.allocArray<GLfloat>(&call.arg(1));
    const trace::Array *_a_GLfloat37_0 = (call.arg(1)).toArray();
    if (_a_GLfloat37_0) {
        for (size_t _jGLfloat37 = 0; _jGLfloat37 < _a_GLfloat37_0->values.size(); ++_jGLfloat37) {
    v[_jGLfloat37] = (*_a_GLfloat37_0->values[_jGLfloat37]).toFloat();
        }
    }

    glCoverageModulationTableNV(n, v);
}

static void retrace_glCoverageModulationNV(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    GLenum components;
    components = static_cast<GLenum>((call.arg(0)).toSInt());

    glCoverageModulationNV(components);
}

static void retrace_glGenPathsNV(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    GLsizei range;
    range = (call.arg(0)).toSInt();

    GLuint _result;
    _result = glGenPathsNV(range);
    (void)_result;
}

static void retrace_glDeletePathsNV(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    GLuint path;
    path = (call.arg(0)).toUInt();

    GLsizei range;
    range = (call.arg(1)).toSInt();

    glDeletePathsNV(path, range);
}

static void retrace_glIsPathNV(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    GLuint path;
    path = (call.arg(0)).toUInt();

    GLboolean _result;
    _result = glIsPathNV(path);
    (void)_result;
}

static void retrace_glPathCommandsNV(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    GLuint path;
    path = (call.arg(0)).toUInt();

    GLsizei numCommands;
    numCommands = (call.arg(1)).toSInt();

    GLubyte * commands;
    commands = _allocator.allocArray<GLubyte>(&call.arg(2));
    const trace::Array *_a_GLubyte1_0 = (call.arg(2)).toArray();
    if (_a_GLubyte1_0) {
        for (size_t _jGLubyte1 = 0; _jGLubyte1 < _a_GLubyte1_0->values.size(); ++_jGLubyte1) {
    commands[_jGLubyte1] = (*_a_GLubyte1_0->values[_jGLubyte1]).toUInt();
        }
    }

    GLsizei numCoords;
    numCoords = (call.arg(3)).toSInt();

    GLenum coordType;
    coordType = static_cast<GLenum>((call.arg(4)).toSInt());

    GLvoid * coords;
    coords = static_cast<GLvoid *>((call.arg(5)).toPointer());

    glPathCommandsNV(path, numCommands, commands, numCoords, coordType, coords);
}

static void retrace_glPathCoordsNV(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    GLuint path;
    path = (call.arg(0)).toUInt();

    GLsizei numCoords;
    numCoords = (call.arg(1)).toSInt();

    GLenum coordType;
    coordType = static_cast<GLenum>((call.arg(2)).toSInt());

    GLvoid * coords;
    coords = static_cast<GLvoid *>((call.arg(3)).toPointer());

    glPathCoordsNV(path, numCoords, coordType, coords);
}

static void retrace_glPathSubCommandsNV(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    GLuint path;
    path = (call.arg(0)).toUInt();

    GLsizei commandStart;
    commandStart = (call.arg(1)).toSInt();

    GLsizei commandsToDelete;
    commandsToDelete = (call.arg(2)).toSInt();

    GLsizei numCommands;
    numCommands = (call.arg(3)).toSInt();

    GLubyte * commands;
    commands = _allocator.allocArray<GLubyte>(&call.arg(4));
    const trace::Array *_a_GLubyte2_0 = (call.arg(4)).toArray();
    if (_a_GLubyte2_0) {
        for (size_t _jGLubyte2 = 0; _jGLubyte2 < _a_GLubyte2_0->values.size(); ++_jGLubyte2) {
    commands[_jGLubyte2] = (*_a_GLubyte2_0->values[_jGLubyte2]).toUInt();
        }
    }

    GLsizei numCoords;
    numCoords = (call.arg(5)).toSInt();

    GLenum coordType;
    coordType = static_cast<GLenum>((call.arg(6)).toSInt());

    GLvoid * coords;
    coords = static_cast<GLvoid *>((call.arg(7)).toPointer());

    glPathSubCommandsNV(path, commandStart, commandsToDelete, numCommands, commands, numCoords, coordType, coords);
}

static void retrace_glPathSubCoordsNV(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    GLuint path;
    path = (call.arg(0)).toUInt();

    GLsizei coordStart;
    coordStart = (call.arg(1)).toSInt();

    GLsizei numCoords;
    numCoords = (call.arg(2)).toSInt();

    GLenum coordType;
    coordType = static_cast<GLenum>((call.arg(3)).toSInt());

    GLvoid * coords;
    coords = static_cast<GLvoid *>((call.arg(4)).toPointer());

    glPathSubCoordsNV(path, coordStart, numCoords, coordType, coords);
}

static void retrace_glPathStringNV(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    GLuint path;
    path = (call.arg(0)).toUInt();

    GLenum format;
    format = static_cast<GLenum>((call.arg(1)).toSInt());

    GLsizei length;
    length = (call.arg(2)).toSInt();

    GLvoid * pathString;
    pathString = static_cast<GLvoid *>((call.arg(3)).toPointer());

    glPathStringNV(path, format, length, pathString);
}

static void retrace_glPathGlyphsNV(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    GLuint firstPathName;
    firstPathName = (call.arg(0)).toUInt();

    GLenum fontTarget;
    fontTarget = static_cast<GLenum>((call.arg(1)).toSInt());

    GLvoid * fontName;
    fontName = static_cast<GLvoid *>((call.arg(2)).toPointer());

    GLbitfield fontStyle;
    fontStyle = (call.arg(3)).toUInt();

    GLsizei numGlyphs;
    numGlyphs = (call.arg(4)).toSInt();

    GLenum type;
    type = static_cast<GLenum>((call.arg(5)).toSInt());

    GLvoid * charcodes;
    charcodes = static_cast<GLvoid *>((call.arg(6)).toPointer());

    GLenum handleMissingGlyphs;
    handleMissingGlyphs = static_cast<GLenum>((call.arg(7)).toSInt());

    GLuint pathParameterTemplate;
    pathParameterTemplate = (call.arg(8)).toUInt();

    GLfloat emScale;
    emScale = (call.arg(9)).toFloat();

    glPathGlyphsNV(firstPathName, fontTarget, fontName, fontStyle, numGlyphs, type, charcodes, handleMissingGlyphs, pathParameterTemplate, emScale);
}

static void retrace_glPathGlyphRangeNV(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    GLuint firstPathName;
    firstPathName = (call.arg(0)).toUInt();

    GLenum fontTarget;
    fontTarget = static_cast<GLenum>((call.arg(1)).toSInt());

    GLvoid * fontName;
    fontName = static_cast<GLvoid *>((call.arg(2)).toPointer());

    GLbitfield fontStyle;
    fontStyle = (call.arg(3)).toUInt();

    GLuint firstGlyph;
    firstGlyph = (call.arg(4)).toUInt();

    GLsizei numGlyphs;
    numGlyphs = (call.arg(5)).toSInt();

    GLenum handleMissingGlyphs;
    handleMissingGlyphs = static_cast<GLenum>((call.arg(6)).toSInt());

    GLuint pathParameterTemplate;
    pathParameterTemplate = (call.arg(7)).toUInt();

    GLfloat emScale;
    emScale = (call.arg(8)).toFloat();

    glPathGlyphRangeNV(firstPathName, fontTarget, fontName, fontStyle, firstGlyph, numGlyphs, handleMissingGlyphs, pathParameterTemplate, emScale);
}

static void retrace_glWeightPathsNV(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    GLuint resultPath;
    resultPath = (call.arg(0)).toUInt();

    GLsizei numPaths;
    numPaths = (call.arg(1)).toSInt();

    GLuint * paths;
    paths = _allocator.allocArray<GLuint>(&call.arg(2));
    const trace::Array *_a_GLuint56_0 = (call.arg(2)).toArray();
    if (_a_GLuint56_0) {
        for (size_t _jGLuint56 = 0; _jGLuint56 < _a_GLuint56_0->values.size(); ++_jGLuint56) {
    paths[_jGLuint56] = (*_a_GLuint56_0->values[_jGLuint56]).toUInt();
        }
    }

    GLfloat * weights;
    weights = _allocator.allocArray<GLfloat>(&call.arg(3));
    const trace::Array *_a_GLfloat38_0 = (call.arg(3)).toArray();
    if (_a_GLfloat38_0) {
        for (size_t _jGLfloat38 = 0; _jGLfloat38 < _a_GLfloat38_0->values.size(); ++_jGLfloat38) {
    weights[_jGLfloat38] = (*_a_GLfloat38_0->values[_jGLfloat38]).toFloat();
        }
    }

    glWeightPathsNV(resultPath, numPaths, paths, weights);
}

static void retrace_glCopyPathNV(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    GLuint resultPath;
    resultPath = (call.arg(0)).toUInt();

    GLuint srcPath;
    srcPath = (call.arg(1)).toUInt();

    glCopyPathNV(resultPath, srcPath);
}

static void retrace_glInterpolatePathsNV(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    GLuint resultPath;
    resultPath = (call.arg(0)).toUInt();

    GLuint pathA;
    pathA = (call.arg(1)).toUInt();

    GLuint pathB;
    pathB = (call.arg(2)).toUInt();

    GLfloat weight;
    weight = (call.arg(3)).toFloat();

    glInterpolatePathsNV(resultPath, pathA, pathB, weight);
}

static void retrace_glTransformPathNV(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    GLuint resultPath;
    resultPath = (call.arg(0)).toUInt();

    GLuint srcPath;
    srcPath = (call.arg(1)).toUInt();

    GLenum transformType;
    transformType = static_cast<GLenum>((call.arg(2)).toSInt());

    GLfloat * transformValues;
    transformValues = _allocator.allocArray<GLfloat>(&call.arg(3));
    const trace::Array *_a_GLfloat39_0 = (call.arg(3)).toArray();
    if (_a_GLfloat39_0) {
        for (size_t _jGLfloat39 = 0; _jGLfloat39 < _a_GLfloat39_0->values.size(); ++_jGLfloat39) {
    transformValues[_jGLfloat39] = (*_a_GLfloat39_0->values[_jGLfloat39]).toFloat();
        }
    }

    glTransformPathNV(resultPath, srcPath, transformType, transformValues);
}

static void retrace_glPathParameterivNV(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    GLuint path;
    path = (call.arg(0)).toUInt();

    GLenum pname;
    pname = static_cast<GLenum>((call.arg(1)).toSInt());

    GLint * value;
    value = _allocator.allocArray<GLint>(&call.arg(2));
    const trace::Array *_a_GLint32_0 = (call.arg(2)).toArray();
    if (_a_GLint32_0) {
        for (size_t _jGLint32 = 0; _jGLint32 < _a_GLint32_0->values.size(); ++_jGLint32) {
    value[_jGLint32] = (*_a_GLint32_0->values[_jGLint32]).toSInt();
        }
    }

    glPathParameterivNV(path, pname, value);
}

static void retrace_glPathParameteriNV(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    GLuint path;
    path = (call.arg(0)).toUInt();

    GLenum pname;
    pname = static_cast<GLenum>((call.arg(1)).toSInt());

    GLint value;
    value = (call.arg(2)).toSInt();

    glPathParameteriNV(path, pname, value);
}

static void retrace_glPathParameterfvNV(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    GLuint path;
    path = (call.arg(0)).toUInt();

    GLenum pname;
    pname = static_cast<GLenum>((call.arg(1)).toSInt());

    GLfloat * value;
    value = _allocator.allocArray<GLfloat>(&call.arg(2));
    const trace::Array *_a_GLfloat40_0 = (call.arg(2)).toArray();
    if (_a_GLfloat40_0) {
        for (size_t _jGLfloat40 = 0; _jGLfloat40 < _a_GLfloat40_0->values.size(); ++_jGLfloat40) {
    value[_jGLfloat40] = (*_a_GLfloat40_0->values[_jGLfloat40]).toFloat();
        }
    }

    glPathParameterfvNV(path, pname, value);
}

static void retrace_glPathParameterfNV(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    GLuint path;
    path = (call.arg(0)).toUInt();

    GLenum pname;
    pname = static_cast<GLenum>((call.arg(1)).toSInt());

    GLfloat value;
    value = (call.arg(2)).toFloat();

    glPathParameterfNV(path, pname, value);
}

static void retrace_glPathDashArrayNV(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    GLuint path;
    path = (call.arg(0)).toUInt();

    GLsizei dashCount;
    dashCount = (call.arg(1)).toSInt();

    GLfloat * dashArray;
    dashArray = _allocator.allocArray<GLfloat>(&call.arg(2));
    const trace::Array *_a_GLfloat41_0 = (call.arg(2)).toArray();
    if (_a_GLfloat41_0) {
        for (size_t _jGLfloat41 = 0; _jGLfloat41 < _a_GLfloat41_0->values.size(); ++_jGLfloat41) {
    dashArray[_jGLfloat41] = (*_a_GLfloat41_0->values[_jGLfloat41]).toFloat();
        }
    }

    glPathDashArrayNV(path, dashCount, dashArray);
}

static void retrace_glPathStencilFuncNV(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    GLenum func;
    func = static_cast<GLenum>((call.arg(0)).toSInt());

    GLint ref;
    ref = (call.arg(1)).toSInt();

    GLuint mask;
    mask = (call.arg(2)).toUInt();

    glPathStencilFuncNV(func, ref, mask);
}

static void retrace_glPathStencilDepthOffsetNV(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    GLfloat factor;
    factor = (call.arg(0)).toFloat();

    GLfloat units;
    units = (call.arg(1)).toFloat();

    glPathStencilDepthOffsetNV(factor, units);
}

static void retrace_glStencilFillPathNV(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    GLuint path;
    path = (call.arg(0)).toUInt();

    GLenum fillMode;
    fillMode = static_cast<GLenum>((call.arg(1)).toSInt());

    GLuint mask;
    mask = (call.arg(2)).toUInt();

    glStencilFillPathNV(path, fillMode, mask);
}

static void retrace_glStencilStrokePathNV(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    GLuint path;
    path = (call.arg(0)).toUInt();

    GLint reference;
    reference = (call.arg(1)).toSInt();

    GLuint mask;
    mask = (call.arg(2)).toUInt();

    glStencilStrokePathNV(path, reference, mask);
}

static void retrace_glStencilFillPathInstancedNV(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    GLsizei numPaths;
    numPaths = (call.arg(0)).toSInt();

    GLenum pathNameType;
    pathNameType = static_cast<GLenum>((call.arg(1)).toSInt());

    GLvoid * paths;
    paths = static_cast<GLvoid *>((call.arg(2)).toPointer());

    GLuint pathBase;
    pathBase = (call.arg(3)).toUInt();

    GLenum fillMode;
    fillMode = static_cast<GLenum>((call.arg(4)).toSInt());

    GLuint mask;
    mask = (call.arg(5)).toUInt();

    GLenum transformType;
    transformType = static_cast<GLenum>((call.arg(6)).toSInt());

    GLfloat * transformValues;
    transformValues = _allocator.allocArray<GLfloat>(&call.arg(7));
    const trace::Array *_a_GLfloat42_0 = (call.arg(7)).toArray();
    if (_a_GLfloat42_0) {
        for (size_t _jGLfloat42 = 0; _jGLfloat42 < _a_GLfloat42_0->values.size(); ++_jGLfloat42) {
    transformValues[_jGLfloat42] = (*_a_GLfloat42_0->values[_jGLfloat42]).toFloat();
        }
    }

    glStencilFillPathInstancedNV(numPaths, pathNameType, paths, pathBase, fillMode, mask, transformType, transformValues);
}

static void retrace_glStencilStrokePathInstancedNV(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    GLsizei numPaths;
    numPaths = (call.arg(0)).toSInt();

    GLenum pathNameType;
    pathNameType = static_cast<GLenum>((call.arg(1)).toSInt());

    GLvoid * paths;
    paths = static_cast<GLvoid *>((call.arg(2)).toPointer());

    GLuint pathBase;
    pathBase = (call.arg(3)).toUInt();

    GLint reference;
    reference = (call.arg(4)).toSInt();

    GLuint mask;
    mask = (call.arg(5)).toUInt();

    GLenum transformType;
    transformType = static_cast<GLenum>((call.arg(6)).toSInt());

    GLfloat * transformValues;
    transformValues = _allocator.allocArray<GLfloat>(&call.arg(7));
    const trace::Array *_a_GLfloat43_0 = (call.arg(7)).toArray();
    if (_a_GLfloat43_0) {
        for (size_t _jGLfloat43 = 0; _jGLfloat43 < _a_GLfloat43_0->values.size(); ++_jGLfloat43) {
    transformValues[_jGLfloat43] = (*_a_GLfloat43_0->values[_jGLfloat43]).toFloat();
        }
    }

    glStencilStrokePathInstancedNV(numPaths, pathNameType, paths, pathBase, reference, mask, transformType, transformValues);
}

static void retrace_glPathCoverDepthFuncNV(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    GLenum func;
    func = static_cast<GLenum>((call.arg(0)).toSInt());

    glPathCoverDepthFuncNV(func);
}

static void retrace_glCoverFillPathNV(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    GLuint path;
    path = (call.arg(0)).toUInt();

    GLenum coverMode;
    coverMode = static_cast<GLenum>((call.arg(1)).toSInt());

    glCoverFillPathNV(path, coverMode);
}

static void retrace_glCoverStrokePathNV(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    GLuint path;
    path = (call.arg(0)).toUInt();

    GLenum coverMode;
    coverMode = static_cast<GLenum>((call.arg(1)).toSInt());

    glCoverStrokePathNV(path, coverMode);
}

static void retrace_glCoverFillPathInstancedNV(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    GLsizei numPaths;
    numPaths = (call.arg(0)).toSInt();

    GLenum pathNameType;
    pathNameType = static_cast<GLenum>((call.arg(1)).toSInt());

    GLvoid * paths;
    paths = static_cast<GLvoid *>((call.arg(2)).toPointer());

    GLuint pathBase;
    pathBase = (call.arg(3)).toUInt();

    GLenum coverMode;
    coverMode = static_cast<GLenum>((call.arg(4)).toSInt());

    GLenum transformType;
    transformType = static_cast<GLenum>((call.arg(5)).toSInt());

    GLfloat * transformValues;
    transformValues = _allocator.allocArray<GLfloat>(&call.arg(6));
    const trace::Array *_a_GLfloat44_0 = (call.arg(6)).toArray();
    if (_a_GLfloat44_0) {
        for (size_t _jGLfloat44 = 0; _jGLfloat44 < _a_GLfloat44_0->values.size(); ++_jGLfloat44) {
    transformValues[_jGLfloat44] = (*_a_GLfloat44_0->values[_jGLfloat44]).toFloat();
        }
    }

    glCoverFillPathInstancedNV(numPaths, pathNameType, paths, pathBase, coverMode, transformType, transformValues);
}

static void retrace_glCoverStrokePathInstancedNV(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    GLsizei numPaths;
    numPaths = (call.arg(0)).toSInt();

    GLenum pathNameType;
    pathNameType = static_cast<GLenum>((call.arg(1)).toSInt());

    GLvoid * paths;
    paths = static_cast<GLvoid *>((call.arg(2)).toPointer());

    GLuint pathBase;
    pathBase = (call.arg(3)).toUInt();

    GLenum coverMode;
    coverMode = static_cast<GLenum>((call.arg(4)).toSInt());

    GLenum transformType;
    transformType = static_cast<GLenum>((call.arg(5)).toSInt());

    GLfloat * transformValues;
    transformValues = _allocator.allocArray<GLfloat>(&call.arg(6));
    const trace::Array *_a_GLfloat45_0 = (call.arg(6)).toArray();
    if (_a_GLfloat45_0) {
        for (size_t _jGLfloat45 = 0; _jGLfloat45 < _a_GLfloat45_0->values.size(); ++_jGLfloat45) {
    transformValues[_jGLfloat45] = (*_a_GLfloat45_0->values[_jGLfloat45]).toFloat();
        }
    }

    glCoverStrokePathInstancedNV(numPaths, pathNameType, paths, pathBase, coverMode, transformType, transformValues);
}

static void retrace_glGetPathSpacingNV(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    GLenum pathListMode;
    pathListMode = static_cast<GLenum>((call.arg(0)).toSInt());

    GLsizei numPaths;
    numPaths = (call.arg(1)).toSInt();

    GLenum pathNameType;
    pathNameType = static_cast<GLenum>((call.arg(2)).toSInt());

    GLvoid * paths;
    paths = static_cast<GLvoid *>((call.arg(3)).toPointer());

    GLuint pathBase;
    pathBase = (call.arg(4)).toUInt();

    GLfloat advanceScale;
    advanceScale = (call.arg(5)).toFloat();

    GLfloat kerningScale;
    kerningScale = (call.arg(6)).toFloat();

    GLenum transformType;
    transformType = static_cast<GLenum>((call.arg(7)).toSInt());

    GLfloat * returnedSpacing;
    returnedSpacing = _allocator.allocArray<GLfloat>(&call.arg(8));

    glGetPathSpacingNV(pathListMode, numPaths, pathNameType, paths, pathBase, advanceScale, kerningScale, transformType, returnedSpacing);
    const trace::Array *_aGLfloat47 = (call.arg(8)).toArray();
    if (_aGLfloat47) {
        for (size_t _jGLfloat47 = 0; _jGLfloat47 < _aGLfloat47->values.size(); ++_jGLfloat47) {
        }
    }
}

static void retrace_glGetPathLengthNV(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    GLuint path;
    path = (call.arg(0)).toUInt();

    GLsizei startSegment;
    startSegment = (call.arg(1)).toSInt();

    GLsizei numSegments;
    numSegments = (call.arg(2)).toSInt();

    GLfloat _result;
    _result = glGetPathLengthNV(path, startSegment, numSegments);
    (void)_result;
}

static void retrace_glMatrixLoad3x2fNV(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    GLenum matrixMode;
    matrixMode = static_cast<GLenum>((call.arg(0)).toSInt());

    GLfloat * m;
    m = _allocator.allocArray<GLfloat>(&call.arg(1));
    const trace::Array *_a_GLfloat48_0 = (call.arg(1)).toArray();
    if (_a_GLfloat48_0) {
        for (size_t _jGLfloat48 = 0; _jGLfloat48 < _a_GLfloat48_0->values.size(); ++_jGLfloat48) {
    m[_jGLfloat48] = (*_a_GLfloat48_0->values[_jGLfloat48]).toFloat();
        }
    }

    glMatrixLoad3x2fNV(matrixMode, m);
}

static void retrace_glMatrixLoad3x3fNV(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    GLenum matrixMode;
    matrixMode = static_cast<GLenum>((call.arg(0)).toSInt());

    GLfloat * m;
    m = _allocator.allocArray<GLfloat>(&call.arg(1));
    const trace::Array *_a_GLfloat49_0 = (call.arg(1)).toArray();
    if (_a_GLfloat49_0) {
        for (size_t _jGLfloat49 = 0; _jGLfloat49 < _a_GLfloat49_0->values.size(); ++_jGLfloat49) {
    m[_jGLfloat49] = (*_a_GLfloat49_0->values[_jGLfloat49]).toFloat();
        }
    }

    glMatrixLoad3x3fNV(matrixMode, m);
}

static void retrace_glMatrixLoadTranspose3x3fNV(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    GLenum matrixMode;
    matrixMode = static_cast<GLenum>((call.arg(0)).toSInt());

    GLfloat * m;
    m = _allocator.allocArray<GLfloat>(&call.arg(1));
    const trace::Array *_a_GLfloat50_0 = (call.arg(1)).toArray();
    if (_a_GLfloat50_0) {
        for (size_t _jGLfloat50 = 0; _jGLfloat50 < _a_GLfloat50_0->values.size(); ++_jGLfloat50) {
    m[_jGLfloat50] = (*_a_GLfloat50_0->values[_jGLfloat50]).toFloat();
        }
    }

    glMatrixLoadTranspose3x3fNV(matrixMode, m);
}

static void retrace_glMatrixMult3x2fNV(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    GLenum matrixMode;
    matrixMode = static_cast<GLenum>((call.arg(0)).toSInt());

    GLfloat * m;
    m = _allocator.allocArray<GLfloat>(&call.arg(1));
    const trace::Array *_a_GLfloat51_0 = (call.arg(1)).toArray();
    if (_a_GLfloat51_0) {
        for (size_t _jGLfloat51 = 0; _jGLfloat51 < _a_GLfloat51_0->values.size(); ++_jGLfloat51) {
    m[_jGLfloat51] = (*_a_GLfloat51_0->values[_jGLfloat51]).toFloat();
        }
    }

    glMatrixMult3x2fNV(matrixMode, m);
}

static void retrace_glMatrixMult3x3fNV(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    GLenum matrixMode;
    matrixMode = static_cast<GLenum>((call.arg(0)).toSInt());

    GLfloat * m;
    m = _allocator.allocArray<GLfloat>(&call.arg(1));
    const trace::Array *_a_GLfloat52_0 = (call.arg(1)).toArray();
    if (_a_GLfloat52_0) {
        for (size_t _jGLfloat52 = 0; _jGLfloat52 < _a_GLfloat52_0->values.size(); ++_jGLfloat52) {
    m[_jGLfloat52] = (*_a_GLfloat52_0->values[_jGLfloat52]).toFloat();
        }
    }

    glMatrixMult3x3fNV(matrixMode, m);
}

static void retrace_glMatrixMultTranspose3x3fNV(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    GLenum matrixMode;
    matrixMode = static_cast<GLenum>((call.arg(0)).toSInt());

    GLfloat * m;
    m = _allocator.allocArray<GLfloat>(&call.arg(1));
    const trace::Array *_a_GLfloat53_0 = (call.arg(1)).toArray();
    if (_a_GLfloat53_0) {
        for (size_t _jGLfloat53 = 0; _jGLfloat53 < _a_GLfloat53_0->values.size(); ++_jGLfloat53) {
    m[_jGLfloat53] = (*_a_GLfloat53_0->values[_jGLfloat53]).toFloat();
        }
    }

    glMatrixMultTranspose3x3fNV(matrixMode, m);
}

static void retrace_glStencilThenCoverFillPathNV(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    GLuint path;
    path = (call.arg(0)).toUInt();

    GLenum fillMode;
    fillMode = static_cast<GLenum>((call.arg(1)).toSInt());

    GLuint mask;
    mask = (call.arg(2)).toUInt();

    GLenum coverMode;
    coverMode = static_cast<GLenum>((call.arg(3)).toSInt());

    glStencilThenCoverFillPathNV(path, fillMode, mask, coverMode);
}

static void retrace_glStencilThenCoverStrokePathNV(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    GLuint path;
    path = (call.arg(0)).toUInt();

    GLint reference;
    reference = (call.arg(1)).toSInt();

    GLuint mask;
    mask = (call.arg(2)).toUInt();

    GLenum coverMode;
    coverMode = static_cast<GLenum>((call.arg(3)).toSInt());

    glStencilThenCoverStrokePathNV(path, reference, mask, coverMode);
}

static void retrace_glStencilThenCoverFillPathInstancedNV(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    GLsizei numPaths;
    numPaths = (call.arg(0)).toSInt();

    GLenum pathNameType;
    pathNameType = static_cast<GLenum>((call.arg(1)).toSInt());

    GLvoid * paths;
    paths = static_cast<GLvoid *>((call.arg(2)).toPointer());

    GLuint pathBase;
    pathBase = (call.arg(3)).toUInt();

    GLenum fillMode;
    fillMode = static_cast<GLenum>((call.arg(4)).toSInt());

    GLuint mask;
    mask = (call.arg(5)).toUInt();

    GLenum coverMode;
    coverMode = static_cast<GLenum>((call.arg(6)).toSInt());

    GLenum transformType;
    transformType = static_cast<GLenum>((call.arg(7)).toSInt());

    GLfloat * transformValues;
    transformValues = _allocator.allocArray<GLfloat>(&call.arg(8));
    const trace::Array *_a_GLfloat54_0 = (call.arg(8)).toArray();
    if (_a_GLfloat54_0) {
        for (size_t _jGLfloat54 = 0; _jGLfloat54 < _a_GLfloat54_0->values.size(); ++_jGLfloat54) {
    transformValues[_jGLfloat54] = (*_a_GLfloat54_0->values[_jGLfloat54]).toFloat();
        }
    }

    glStencilThenCoverFillPathInstancedNV(numPaths, pathNameType, paths, pathBase, fillMode, mask, coverMode, transformType, transformValues);
}

static void retrace_glStencilThenCoverStrokePathInstancedNV(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    GLsizei numPaths;
    numPaths = (call.arg(0)).toSInt();

    GLenum pathNameType;
    pathNameType = static_cast<GLenum>((call.arg(1)).toSInt());

    GLvoid * paths;
    paths = static_cast<GLvoid *>((call.arg(2)).toPointer());

    GLuint pathBase;
    pathBase = (call.arg(3)).toUInt();

    GLint reference;
    reference = (call.arg(4)).toSInt();

    GLuint mask;
    mask = (call.arg(5)).toUInt();

    GLenum coverMode;
    coverMode = static_cast<GLenum>((call.arg(6)).toSInt());

    GLenum transformType;
    transformType = static_cast<GLenum>((call.arg(7)).toSInt());

    GLfloat * transformValues;
    transformValues = _allocator.allocArray<GLfloat>(&call.arg(8));
    const trace::Array *_a_GLfloat55_0 = (call.arg(8)).toArray();
    if (_a_GLfloat55_0) {
        for (size_t _jGLfloat55 = 0; _jGLfloat55 < _a_GLfloat55_0->values.size(); ++_jGLfloat55) {
    transformValues[_jGLfloat55] = (*_a_GLfloat55_0->values[_jGLfloat55]).toFloat();
        }
    }

    glStencilThenCoverStrokePathInstancedNV(numPaths, pathNameType, paths, pathBase, reference, mask, coverMode, transformType, transformValues);
}

static void retrace_glPathGlyphIndexRangeNV(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    GLenum fontTarget;
    fontTarget = static_cast<GLenum>((call.arg(0)).toSInt());

    const GLvoid * fontName;
    fontName = (const GLvoid *)((call.arg(1)).toString());

    GLbitfield fontStyle;
    fontStyle = (call.arg(2)).toUInt();

    GLuint pathParameterTemplate;
    pathParameterTemplate = (call.arg(3)).toUInt();

    GLfloat emScale;
    emScale = (call.arg(4)).toFloat();

    GLuint * baseAndCount;
    baseAndCount = _allocator.allocArray<GLuint>(&call.arg(5));
    const trace::Array *_a_GLuint57_0 = (call.arg(5)).toArray();
    if (_a_GLuint57_0) {
        for (size_t _jGLuint57 = 0; _jGLuint57 < _a_GLuint57_0->values.size(); ++_jGLuint57) {
    baseAndCount[_jGLuint57] = (*_a_GLuint57_0->values[_jGLuint57]).toUInt();
        }
    }

    GLenum _result;
    _result = glPathGlyphIndexRangeNV(fontTarget, fontName, fontStyle, pathParameterTemplate, emScale, baseAndCount);
    (void)_result;
}

static void retrace_glPathGlyphIndexArrayNV(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    GLuint firstPathName;
    firstPathName = (call.arg(0)).toUInt();

    GLenum fontTarget;
    fontTarget = static_cast<GLenum>((call.arg(1)).toSInt());

    const GLvoid * fontName;
    fontName = (const GLvoid *)((call.arg(2)).toString());

    GLbitfield fontStyle;
    fontStyle = (call.arg(3)).toUInt();

    GLuint firstGlyphIndex;
    firstGlyphIndex = (call.arg(4)).toUInt();

    GLsizei numGlyphs;
    numGlyphs = (call.arg(5)).toSInt();

    GLuint pathParameterTemplate;
    pathParameterTemplate = (call.arg(6)).toUInt();

    GLfloat emScale;
    emScale = (call.arg(7)).toFloat();

    GLenum _result;
    _result = glPathGlyphIndexArrayNV(firstPathName, fontTarget, fontName, fontStyle, firstGlyphIndex, numGlyphs, pathParameterTemplate, emScale);
    (void)_result;
}

static void retrace_glPathMemoryGlyphIndexArrayNV(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    GLuint firstPathName;
    firstPathName = (call.arg(0)).toUInt();

    GLenum fontTarget;
    fontTarget = static_cast<GLenum>((call.arg(1)).toSInt());

    GLsizeiptr fontSize;
    fontSize = (call.arg(2)).toSInt();

    void * fontData;
    fontData = static_cast<void *>((call.arg(3)).toPointer());

    GLsizei faceIndex;
    faceIndex = (call.arg(4)).toSInt();

    GLuint firstGlyphIndex;
    firstGlyphIndex = (call.arg(5)).toUInt();

    GLsizei numGlyphs;
    numGlyphs = (call.arg(6)).toSInt();

    GLuint pathParameterTemplate;
    pathParameterTemplate = (call.arg(7)).toUInt();

    GLfloat emScale;
    emScale = (call.arg(8)).toFloat();

    GLenum _result;
    _result = glPathMemoryGlyphIndexArrayNV(firstPathName, fontTarget, fontSize, fontData, faceIndex, firstGlyphIndex, numGlyphs, pathParameterTemplate, emScale);
    (void)_result;
}

static void retrace_glProgramPathFragmentInputGenNV(trace::Call &call) {
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

    GLint location;
    location = (call.arg(1)).toSInt();
    if (retrace::verbosity >= 2) {
        std::cout << "location " << size_t(location) << " <- " << size_t(_location_map[program].lookupUniformLocation(location)) << "\n";
    }
    location = _location_map[program].lookupUniformLocation(location);

    GLenum genMode;
    genMode = static_cast<GLenum>((call.arg(2)).toSInt());

    GLint components;
    components = (call.arg(3)).toSInt();

    GLfloat * coeffs;
    coeffs = _allocator.allocArray<GLfloat>(&call.arg(4));
    const trace::Array *_a_GLfloat56_0 = (call.arg(4)).toArray();
    if (_a_GLfloat56_0) {
        for (size_t _jGLfloat56 = 0; _jGLfloat56 < _a_GLfloat56_0->values.size(); ++_jGLfloat56) {
    coeffs[_jGLfloat56] = (*_a_GLfloat56_0->values[_jGLfloat56]).toFloat();
        }
    }

    glProgramPathFragmentInputGenNV(program, location, genMode, components, coeffs);
}

static void retrace_glReadBufferNV(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    GLenum mode;
    mode = static_cast<GLenum>((call.arg(0)).toSInt());

    glReadBufferNV(mode);
}

static void retrace_glProgramBinaryOES(trace::Call &call) {
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

    GLenum binaryFormat;
    binaryFormat = static_cast<GLenum>((call.arg(1)).toSInt());

    GLvoid * binary;
    binary = static_cast<GLvoid *>((call.arg(2)).toPointer());

    GLsizei length;
    length = (call.arg(3)).toSInt();

    glProgramBinaryOES(program, binaryFormat, binary, length);
}

static void retrace_glMapBufferOES(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    GLenum target;
    target = static_cast<GLenum>((call.arg(0)).toSInt());

    GLenum access;
    access = static_cast<GLenum>((call.arg(1)).toSInt());

    GLvoid * _result;
    _result = glMapBufferOES(target, access);
    (void)_result;
    GLint length = 0;
    glGetBufferParameteriv(target, GL_BUFFER_SIZE, &length);
    retrace::addRegion(call, (*call.ret).toUIntPtr(), _result, length);
}

static void retrace_glUnmapBufferOES(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    GLenum target;
    target = static_cast<GLenum>((call.arg(0)).toSInt());

    GLboolean _result;
        GLvoid *ptr = NULL;
            glGetBufferPointervOES(target, GL_BUFFER_MAP_POINTER_OES, &ptr);
        if (ptr) {
            retrace::delRegionByPointer(ptr);
        } else {
            retrace::warning(call) << "failed to get mapped pointer\n";
        }
    _result = glUnmapBufferOES(target);
    (void)_result;
}

static void retrace_glTexImage3DOES(trace::Call &call) {
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

    GLsizei depth;
    depth = (call.arg(5)).toSInt();

    GLint border;
    border = (call.arg(6)).toSInt();

    GLenum format;
    format = static_cast<GLenum>((call.arg(7)).toSInt());

    GLenum type;
    type = static_cast<GLenum>((call.arg(8)).toSInt());

    GLvoid * pixels;
    pixels = static_cast<GLvoid *>((call.arg(9)).toPointer());

    glTexImage3DOES(target, level, internalformat, width, height, depth, border, format, type, pixels);
}

static void retrace_glTexSubImage3DOES(trace::Call &call) {
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

    GLint zoffset;
    zoffset = (call.arg(4)).toSInt();

    GLsizei width;
    width = (call.arg(5)).toSInt();

    GLsizei height;
    height = (call.arg(6)).toSInt();

    GLsizei depth;
    depth = (call.arg(7)).toSInt();

    GLenum format;
    format = static_cast<GLenum>((call.arg(8)).toSInt());

    GLenum type;
    type = static_cast<GLenum>((call.arg(9)).toSInt());

    GLvoid * pixels;
    pixels = static_cast<GLvoid *>((call.arg(10)).toPointer());

    glTexSubImage3DOES(target, level, xoffset, yoffset, zoffset, width, height, depth, format, type, pixels);
}

static void retrace_glCopyTexSubImage3DOES(trace::Call &call) {
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

    GLint zoffset;
    zoffset = (call.arg(4)).toSInt();

    GLint x;
    x = (call.arg(5)).toSInt();

    GLint y;
    y = (call.arg(6)).toSInt();

    GLsizei width;
    width = (call.arg(7)).toSInt();

    GLsizei height;
    height = (call.arg(8)).toSInt();

    glCopyTexSubImage3DOES(target, level, xoffset, yoffset, zoffset, x, y, width, height);
}

static void retrace_glCompressedTexImage3DOES(trace::Call &call) {
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

    GLsizei depth;
    depth = (call.arg(5)).toSInt();

    GLint border;
    border = (call.arg(6)).toSInt();

    GLsizei imageSize;
    imageSize = (call.arg(7)).toSInt();

    GLvoid * data;
    data = static_cast<GLvoid *>((call.arg(8)).toPointer());

    glCompressedTexImage3DOES(target, level, internalformat, width, height, depth, border, imageSize, data);
}

static void retrace_glCompressedTexSubImage3DOES(trace::Call &call) {
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

    GLint zoffset;
    zoffset = (call.arg(4)).toSInt();

    GLsizei width;
    width = (call.arg(5)).toSInt();

    GLsizei height;
    height = (call.arg(6)).toSInt();

    GLsizei depth;
    depth = (call.arg(7)).toSInt();

    GLenum format;
    format = static_cast<GLenum>((call.arg(8)).toSInt());

    GLsizei imageSize;
    imageSize = (call.arg(9)).toSInt();

    GLvoid * data;
    data = static_cast<GLvoid *>((call.arg(10)).toPointer());

    glCompressedTexSubImage3DOES(target, level, xoffset, yoffset, zoffset, width, height, depth, format, imageSize, data);
}

static void retrace_glFramebufferTexture3DOES(trace::Call &call) {
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

    GLint zoffset;
    zoffset = (call.arg(5)).toSInt();

    glFramebufferTexture3DOES(target, attachment, textarget, texture, level, zoffset);
}

static void retrace_glBindVertexArrayOES(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    GLuint array;
    array = (call.arg(0)).toUInt();
    if (retrace::verbosity >= 2) {
        std::cout << "array " << size_t(array) << " <- " << size_t(_array_map[reinterpret_cast<uintptr_t>(glretrace::getCurrentContext())][array]) << "\n";
    }
    array = _array_map[reinterpret_cast<uintptr_t>(glretrace::getCurrentContext())][array];

    glBindVertexArrayOES(array);
}

static void retrace_glDeleteVertexArraysOES(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    GLsizei n;
    n = (call.arg(0)).toSInt();

    GLuint * arrays;
    arrays = _allocator.allocArray<GLuint>(&call.arg(1));
    const trace::Array *_a_GLuint58_0 = (call.arg(1)).toArray();
    if (_a_GLuint58_0) {
        for (size_t _jGLuint58 = 0; _jGLuint58 < _a_GLuint58_0->values.size(); ++_jGLuint58) {
    arrays[_jGLuint58] = (*_a_GLuint58_0->values[_jGLuint58]).toUInt();
    if (retrace::verbosity >= 2) {
        std::cout << "array " << size_t(arrays[_jGLuint58]) << " <- " << size_t(_array_map[reinterpret_cast<uintptr_t>(glretrace::getCurrentContext())][arrays[_jGLuint58]]) << "\n";
    }
    arrays[_jGLuint58] = _array_map[reinterpret_cast<uintptr_t>(glretrace::getCurrentContext())][arrays[_jGLuint58]];
        }
    }

    glDeleteVertexArraysOES(n, arrays);
}

static void retrace_glGenVertexArraysOES(trace::Call &call) {
    retrace::ScopedAllocator _allocator;
    (void)_allocator;
    GLsizei n;
    n = (call.arg(0)).toSInt();

    GLuint * arrays;
    arrays = _allocator.allocArray<GLuint>(&call.arg(1));

    glGenVertexArraysOES(n, arrays);
    const trace::Array *_aGLuint60 = (call.arg(1)).toArray();
    if (_aGLuint60) {
        for (size_t _jGLuint60 = 0; _jGLuint60 < _aGLuint60->values.size(); ++_jGLuint60) {
    GLuint _origResult;
    _origResult = (*_aGLuint60->values[_jGLuint60]).toUInt();
    _array_map[reinterpret_cast<uintptr_t>(glretrace::getCurrentContext())][_origResult] = arrays[_jGLuint60];
    if (retrace::verbosity >= 2) {
        std::cout << "array " << _origResult << " -> " << arrays[_jGLuint60] << "\n";
    }
        }
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
    {"glGetPerfMonitorGroupsAMD", &retrace::ignore},
    {"glGetPerfMonitorCountersAMD", &retrace::ignore},
    {"glGetPerfMonitorGroupStringAMD", &retrace::ignore},
    {"glGetPerfMonitorCounterStringAMD", &retrace::ignore},
    {"glGetPerfMonitorCounterInfoAMD", &retrace::ignore},
    {"glGenPerfMonitorsAMD", &retrace_glGenPerfMonitorsAMD},
    {"glDeletePerfMonitorsAMD", &retrace_glDeletePerfMonitorsAMD},
    {"glSelectPerfMonitorCountersAMD", &retrace_glSelectPerfMonitorCountersAMD},
    {"glBeginPerfMonitorAMD", &retrace_glBeginPerfMonitorAMD},
    {"glEndPerfMonitorAMD", &retrace_glEndPerfMonitorAMD},
    {"glGetPerfMonitorCounterDataAMD", &retrace::ignore},
    {"glBlitFramebufferANGLE", &retrace_glBlitFramebufferANGLE},
    {"glRenderbufferStorageMultisampleANGLE", &retrace_glRenderbufferStorageMultisampleANGLE},
    {"glDrawArraysInstancedANGLE", &retrace_glDrawArraysInstancedANGLE},
    {"glDrawElementsInstancedANGLE", &retrace_glDrawElementsInstancedANGLE},
    {"glVertexAttribDivisorANGLE", &retrace_glVertexAttribDivisorANGLE},
    {"glGetTranslatedShaderSourceANGLE", &retrace::ignore},
    {"glCopyTextureLevelsAPPLE", &retrace_glCopyTextureLevelsAPPLE},
    {"glRenderbufferStorageMultisampleAPPLE", &retrace_glRenderbufferStorageMultisampleAPPLE},
    {"glResolveMultisampleFramebufferAPPLE", &retrace_glResolveMultisampleFramebufferAPPLE},
    {"glFenceSyncAPPLE", &retrace_glFenceSyncAPPLE},
    {"glIsSyncAPPLE", &retrace::ignore},
    {"glDeleteSyncAPPLE", &retrace_glDeleteSyncAPPLE},
    {"glClientWaitSyncAPPLE", &retrace_glClientWaitSyncAPPLE},
    {"glWaitSyncAPPLE", &retrace_glWaitSyncAPPLE},
    {"glGetInteger64vAPPLE", &retrace::ignore},
    {"glGetSyncivAPPLE", &retrace::ignore},
    {"glTexPageCommitmentARB", &retrace_glTexPageCommitmentARB},
    {"glCopyImageSubDataEXT", &retrace_glCopyImageSubDataEXT},
    {"glLabelObjectEXT", &retrace_glLabelObjectEXT},
    {"glGetObjectLabelEXT", &retrace::ignore},
    {"glInsertEventMarkerEXT", &retrace_glInsertEventMarkerEXT},
    {"glPushGroupMarkerEXT", &retrace_glPushGroupMarkerEXT},
    {"glPopGroupMarkerEXT", &retrace_glPopGroupMarkerEXT},
    {"glProgramUniform1fEXT", &retrace_glProgramUniform1fEXT},
    {"glProgramUniform1fvEXT", &retrace_glProgramUniform1fvEXT},
    {"glProgramUniform1iEXT", &retrace_glProgramUniform1iEXT},
    {"glProgramUniform1ivEXT", &retrace_glProgramUniform1ivEXT},
    {"glProgramUniform1uiEXT", &retrace_glProgramUniform1uiEXT},
    {"glProgramUniform1uivEXT", &retrace_glProgramUniform1uivEXT},
    {"glProgramUniform2fEXT", &retrace_glProgramUniform2fEXT},
    {"glProgramUniform2fvEXT", &retrace_glProgramUniform2fvEXT},
    {"glProgramUniform2iEXT", &retrace_glProgramUniform2iEXT},
    {"glProgramUniform2ivEXT", &retrace_glProgramUniform2ivEXT},
    {"glProgramUniform2uiEXT", &retrace_glProgramUniform2uiEXT},
    {"glProgramUniform2uivEXT", &retrace_glProgramUniform2uivEXT},
    {"glProgramUniform3fEXT", &retrace_glProgramUniform3fEXT},
    {"glProgramUniform3fvEXT", &retrace_glProgramUniform3fvEXT},
    {"glProgramUniform3iEXT", &retrace_glProgramUniform3iEXT},
    {"glProgramUniform3ivEXT", &retrace_glProgramUniform3ivEXT},
    {"glProgramUniform3uiEXT", &retrace_glProgramUniform3uiEXT},
    {"glProgramUniform3uivEXT", &retrace_glProgramUniform3uivEXT},
    {"glProgramUniform4fEXT", &retrace_glProgramUniform4fEXT},
    {"glProgramUniform4fvEXT", &retrace_glProgramUniform4fvEXT},
    {"glProgramUniform4iEXT", &retrace_glProgramUniform4iEXT},
    {"glProgramUniform4ivEXT", &retrace_glProgramUniform4ivEXT},
    {"glProgramUniform4uiEXT", &retrace_glProgramUniform4uiEXT},
    {"glProgramUniform4uivEXT", &retrace_glProgramUniform4uivEXT},
    {"glProgramUniformMatrix2fvEXT", &retrace_glProgramUniformMatrix2fvEXT},
    {"glProgramUniformMatrix2x3fvEXT", &retrace_glProgramUniformMatrix2x3fvEXT},
    {"glProgramUniformMatrix2x4fvEXT", &retrace_glProgramUniformMatrix2x4fvEXT},
    {"glProgramUniformMatrix3fvEXT", &retrace_glProgramUniformMatrix3fvEXT},
    {"glProgramUniformMatrix3x2fvEXT", &retrace_glProgramUniformMatrix3x2fvEXT},
    {"glProgramUniformMatrix3x4fvEXT", &retrace_glProgramUniformMatrix3x4fvEXT},
    {"glProgramUniformMatrix4fvEXT", &retrace_glProgramUniformMatrix4fvEXT},
    {"glProgramUniformMatrix4x2fvEXT", &retrace_glProgramUniformMatrix4x2fvEXT},
    {"glProgramUniformMatrix4x3fvEXT", &retrace_glProgramUniformMatrix4x3fvEXT},
    {"glTextureStorage1DEXT", &retrace_glTextureStorage1DEXT},
    {"glTextureStorage2DEXT", &retrace_glTextureStorage2DEXT},
    {"glTextureStorage3DEXT", &retrace_glTextureStorage3DEXT},
    {"glDiscardFramebufferEXT", &retrace_glDiscardFramebufferEXT},
    {"glDrawBuffersEXT", &retrace_glDrawBuffersEXT},
    {"glDrawArraysInstancedEXT", &retrace_glDrawArraysInstancedEXT},
    {"glDrawElementsInstancedEXT", &retrace_glDrawElementsInstancedEXT},
    {"glRenderbufferStorageMultisampleEXT", &retrace_glRenderbufferStorageMultisampleEXT},
    {"glFramebufferTextureEXT", &retrace_glFramebufferTextureEXT},
    {"glProgramParameteriEXT", &retrace_glProgramParameteriEXT},
    {"glVertexAttribDivisorEXT", &retrace_glVertexAttribDivisorEXT},
    {"glMapBufferRangeEXT", &retrace_glMapBufferRangeEXT},
    {"glFlushMappedBufferRangeEXT", &retrace_glFlushMappedBufferRangeEXT},
    {"glMultiDrawArraysEXT", &retrace_glMultiDrawArraysEXT},
    {"glMultiDrawElementsEXT", &retrace_glMultiDrawElementsEXT},
    {"glFramebufferTexture2DMultisampleEXT", &retrace_glFramebufferTexture2DMultisampleEXT},
    {"glGenQueriesEXT", &retrace_glGenQueriesEXT},
    {"glDeleteQueriesEXT", &retrace_glDeleteQueriesEXT},
    {"glIsQueryEXT", &retrace::ignore},
    {"glBeginQueryEXT", &retrace_glBeginQueryEXT},
    {"glEndQueryEXT", &retrace_glEndQueryEXT},
    {"glGetQueryivEXT", &retrace::ignore},
    {"glGetQueryObjectuivEXT", &retrace::ignore},
    {"glPrimitiveBoundingBoxEXT", &retrace_glPrimitiveBoundingBoxEXT},
    {"glRasterSamplesEXT", &retrace_glRasterSamplesEXT},
    {"glActiveShaderProgramEXT", &retrace_glActiveShaderProgramEXT},
    {"glBindProgramPipelineEXT", &retrace_glBindProgramPipelineEXT},
    {"glCreateShaderProgramvEXT", &retrace_glCreateShaderProgramvEXT},
    {"glDeleteProgramPipelinesEXT", &retrace_glDeleteProgramPipelinesEXT},
    {"glGenProgramPipelinesEXT", &retrace_glGenProgramPipelinesEXT},
    {"glGetProgramPipelineInfoLogEXT", &retrace::ignore},
    {"glGetProgramPipelineivEXT", &retrace::ignore},
    {"glIsProgramPipelineEXT", &retrace::ignore},
    {"glUseProgramStagesEXT", &retrace_glUseProgramStagesEXT},
    {"glValidateProgramPipelineEXT", &retrace_glValidateProgramPipelineEXT},
    {"glPatchParameteriEXT", &retrace_glPatchParameteriEXT},
    {"glTexBufferEXT", &retrace_glTexBufferEXT},
    {"glTexBufferRangeEXT", &retrace_glTexBufferRangeEXT},
    {"glTexParameterIivEXT", &retrace_glTexParameterIivEXT},
    {"glTexParameterIuivEXT", &retrace_glTexParameterIuivEXT},
    {"glGetTexParameterIivEXT", &retrace::ignore},
    {"glGetTexParameterIuivEXT", &retrace::ignore},
    {"glTexStorage1DEXT", &retrace_glTexStorage1DEXT},
    {"glTexStorage2DEXT", &retrace_glTexStorage2DEXT},
    {"glTexStorage3DEXT", &retrace_glTexStorage3DEXT},
    {"glTextureViewEXT", &retrace_glTextureViewEXT},
    {"glGetQueryObjecti64vEXT", &retrace::ignore},
    {"glGetQueryObjectui64vEXT", &retrace::ignore},
    {"glRenderbufferStorageMultisampleIMG", &retrace_glRenderbufferStorageMultisampleIMG},
    {"glFramebufferTexture2DMultisampleIMG", &retrace_glFramebufferTexture2DMultisampleIMG},
    {"glBeginPerfQueryINTEL", &retrace::ignore},
    {"glCreatePerfQueryINTEL", &retrace::ignore},
    {"glDeletePerfQueryINTEL", &retrace::ignore},
    {"glEndPerfQueryINTEL", &retrace::ignore},
    {"glGetFirstPerfQueryIdINTEL", &retrace::ignore},
    {"glGetNextPerfQueryIdINTEL", &retrace::ignore},
    {"glGetPerfCounterInfoINTEL", &retrace::ignore},
    {"glGetPerfQueryDataINTEL", &retrace::ignore},
    {"glGetPerfQueryIdByNameINTEL", &retrace::ignore},
    {"glGetPerfQueryInfoINTEL", &retrace::ignore},
    {"glBlendBarrierKHR", &retrace_glBlendBarrierKHR},
    {"glDebugMessageControlKHR", &retrace_glDebugMessageControlKHR},
    {"glDebugMessageInsertKHR", &retrace_glDebugMessageInsertKHR},
    {"glDebugMessageCallbackKHR", &retrace::ignore},
    {"glGetDebugMessageLogKHR", &retrace::ignore},
    {"glPushDebugGroupKHR", &retrace_glPushDebugGroupKHR},
    {"glPopDebugGroupKHR", &retrace_glPopDebugGroupKHR},
    {"glObjectLabelKHR", &retrace_glObjectLabelKHR},
    {"glGetObjectLabelKHR", &retrace::ignore},
    {"glObjectPtrLabelKHR", &retrace_glObjectPtrLabelKHR},
    {"glGetObjectPtrLabelKHR", &retrace::ignore},
    {"glGetPointervKHR", &retrace::ignore},
    {"glGetTextureHandleNV", &retrace_glGetTextureHandleNV},
    {"glGetTextureSamplerHandleNV", &retrace_glGetTextureSamplerHandleNV},
    {"glMakeTextureHandleResidentNV", &retrace_glMakeTextureHandleResidentNV},
    {"glMakeTextureHandleNonResidentNV", &retrace_glMakeTextureHandleNonResidentNV},
    {"glGetImageHandleNV", &retrace_glGetImageHandleNV},
    {"glMakeImageHandleResidentNV", &retrace_glMakeImageHandleResidentNV},
    {"glMakeImageHandleNonResidentNV", &retrace_glMakeImageHandleNonResidentNV},
    {"glUniformHandleui64NV", &retrace_glUniformHandleui64NV},
    {"glUniformHandleui64vNV", &retrace_glUniformHandleui64vNV},
    {"glProgramUniformHandleui64NV", &retrace_glProgramUniformHandleui64NV},
    {"glProgramUniformHandleui64vNV", &retrace_glProgramUniformHandleui64vNV},
    {"glIsTextureHandleResidentNV", &retrace::ignore},
    {"glIsImageHandleResidentNV", &retrace::ignore},
    {"glBlendParameteriNV", &retrace_glBlendParameteriNV},
    {"glBlendBarrierNV", &retrace_glBlendBarrierNV},
    {"glBeginConditionalRenderNV", &retrace_glBeginConditionalRenderNV},
    {"glEndConditionalRenderNV", &retrace_glEndConditionalRenderNV},
    {"glCoverageMaskNV", &retrace_glCoverageMaskNV},
    {"glCoverageOperationNV", &retrace_glCoverageOperationNV},
    {"glDrawBuffersNV", &retrace_glDrawBuffersNV},
    {"glDeleteFencesNV", &retrace_glDeleteFencesNV},
    {"glGenFencesNV", &retrace_glGenFencesNV},
    {"glIsFenceNV", &retrace::ignore},
    {"glTestFenceNV", &retrace_glTestFenceNV},
    {"glGetFenceivNV", &retrace::ignore},
    {"glFinishFenceNV", &retrace_glFinishFenceNV},
    {"glSetFenceNV", &retrace_glSetFenceNV},
    {"glBlitFramebufferNV", &retrace_glBlitFramebufferNV},
    {"glCoverageModulationTableNV", &retrace_glCoverageModulationTableNV},
    {"glGetCoverageModulationTableNV", &retrace::ignore},
    {"glCoverageModulationNV", &retrace_glCoverageModulationNV},
    {"glGenPathsNV", &retrace_glGenPathsNV},
    {"glDeletePathsNV", &retrace_glDeletePathsNV},
    {"glIsPathNV", &retrace_glIsPathNV},
    {"glPathCommandsNV", &retrace_glPathCommandsNV},
    {"glPathCoordsNV", &retrace_glPathCoordsNV},
    {"glPathSubCommandsNV", &retrace_glPathSubCommandsNV},
    {"glPathSubCoordsNV", &retrace_glPathSubCoordsNV},
    {"glPathStringNV", &retrace_glPathStringNV},
    {"glPathGlyphsNV", &retrace_glPathGlyphsNV},
    {"glPathGlyphRangeNV", &retrace_glPathGlyphRangeNV},
    {"glWeightPathsNV", &retrace_glWeightPathsNV},
    {"glCopyPathNV", &retrace_glCopyPathNV},
    {"glInterpolatePathsNV", &retrace_glInterpolatePathsNV},
    {"glTransformPathNV", &retrace_glTransformPathNV},
    {"glPathParameterivNV", &retrace_glPathParameterivNV},
    {"glPathParameteriNV", &retrace_glPathParameteriNV},
    {"glPathParameterfvNV", &retrace_glPathParameterfvNV},
    {"glPathParameterfNV", &retrace_glPathParameterfNV},
    {"glPathDashArrayNV", &retrace_glPathDashArrayNV},
    {"glPathStencilFuncNV", &retrace_glPathStencilFuncNV},
    {"glPathStencilDepthOffsetNV", &retrace_glPathStencilDepthOffsetNV},
    {"glStencilFillPathNV", &retrace_glStencilFillPathNV},
    {"glStencilStrokePathNV", &retrace_glStencilStrokePathNV},
    {"glStencilFillPathInstancedNV", &retrace_glStencilFillPathInstancedNV},
    {"glStencilStrokePathInstancedNV", &retrace_glStencilStrokePathInstancedNV},
    {"glPathCoverDepthFuncNV", &retrace_glPathCoverDepthFuncNV},
    {"glCoverFillPathNV", &retrace_glCoverFillPathNV},
    {"glCoverStrokePathNV", &retrace_glCoverStrokePathNV},
    {"glCoverFillPathInstancedNV", &retrace_glCoverFillPathInstancedNV},
    {"glCoverStrokePathInstancedNV", &retrace_glCoverStrokePathInstancedNV},
    {"glGetPathParameterivNV", &retrace::ignore},
    {"glGetPathParameterfvNV", &retrace::ignore},
    {"glGetPathCommandsNV", &retrace::ignore},
    {"glGetPathCoordsNV", &retrace::ignore},
    {"glGetPathDashArrayNV", &retrace::ignore},
    {"glGetPathMetricsNV", &retrace::ignore},
    {"glGetPathMetricRangeNV", &retrace::ignore},
    {"glGetPathSpacingNV", &retrace_glGetPathSpacingNV},
    {"glIsPointInFillPathNV", &retrace::ignore},
    {"glIsPointInStrokePathNV", &retrace::ignore},
    {"glGetPathLengthNV", &retrace_glGetPathLengthNV},
    {"glPointAlongPathNV", &retrace::ignore},
    {"glMatrixLoad3x2fNV", &retrace_glMatrixLoad3x2fNV},
    {"glMatrixLoad3x3fNV", &retrace_glMatrixLoad3x3fNV},
    {"glMatrixLoadTranspose3x3fNV", &retrace_glMatrixLoadTranspose3x3fNV},
    {"glMatrixMult3x2fNV", &retrace_glMatrixMult3x2fNV},
    {"glMatrixMult3x3fNV", &retrace_glMatrixMult3x3fNV},
    {"glMatrixMultTranspose3x3fNV", &retrace_glMatrixMultTranspose3x3fNV},
    {"glStencilThenCoverFillPathNV", &retrace_glStencilThenCoverFillPathNV},
    {"glStencilThenCoverStrokePathNV", &retrace_glStencilThenCoverStrokePathNV},
    {"glStencilThenCoverFillPathInstancedNV", &retrace_glStencilThenCoverFillPathInstancedNV},
    {"glStencilThenCoverStrokePathInstancedNV", &retrace_glStencilThenCoverStrokePathInstancedNV},
    {"glPathGlyphIndexRangeNV", &retrace_glPathGlyphIndexRangeNV},
    {"glPathGlyphIndexArrayNV", &retrace_glPathGlyphIndexArrayNV},
    {"glPathMemoryGlyphIndexArrayNV", &retrace_glPathMemoryGlyphIndexArrayNV},
    {"glProgramPathFragmentInputGenNV", &retrace_glProgramPathFragmentInputGenNV},
    {"glGetProgramResourcefvNV", &retrace::ignore},
    {"glReadBufferNV", &retrace_glReadBufferNV},
    {"glGetProgramBinaryOES", &retrace::ignore},
    {"glProgramBinaryOES", &retrace_glProgramBinaryOES},
    {"glGetBufferPointervOES", &retrace::ignore},
    {"glMapBufferOES", &retrace_glMapBufferOES},
    {"glUnmapBufferOES", &retrace_glUnmapBufferOES},
    {"glTexImage3DOES", &retrace_glTexImage3DOES},
    {"glTexSubImage3DOES", &retrace_glTexSubImage3DOES},
    {"glCopyTexSubImage3DOES", &retrace_glCopyTexSubImage3DOES},
    {"glCompressedTexImage3DOES", &retrace_glCompressedTexImage3DOES},
    {"glCompressedTexSubImage3DOES", &retrace_glCompressedTexSubImage3DOES},
    {"glFramebufferTexture3DOES", &retrace_glFramebufferTexture3DOES},
    {"glBindVertexArrayOES", &retrace_glBindVertexArrayOES},
    {"glDeleteVertexArraysOES", &retrace_glDeleteVertexArraysOES},
    {"glGenVertexArraysOES", &retrace_glGenVertexArraysOES},
    {"glIsVertexArrayOES", &retrace::ignore},
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


