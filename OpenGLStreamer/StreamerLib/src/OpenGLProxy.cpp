#include "OpenGLProxy.h"
#include <cassert>

OpenGLProxy::OpenGLProxy(QObject *parent) :
    QObject(parent),
    mpOpenGLServer(new OpenGLServer(1234, true))
{
}

void OpenGLProxy::initialize()
{
    mpOpenGLFunctions = QOpenGLContext::currentContext()->functions();
    assert(mpOpenGLFunctions != nullptr);
    mpOpenGLFunctions->initializeOpenGLFunctions();
}
