/*#include "GlWidget.h"

#include <QMouseEvent>

#include <math.h>

#include "openglclient.h"

GlWidget::GlWidget(QWidget *parent) :
    QOpenGLWidget(parent),
    texture(0)
{
    OpenGLClient::get().registerOpenGLWidget(this);
}

GlWidget::~GlWidget()
{
    // Make sure the context is current when deleting the texture
    // and the buffers.
    makeCurrent();
    delete texture;
    doneCurrent();
}

void GlWidget::timerEvent(QTimerEvent *)
{
    if (OpenGLClient::get().updatedNeeded())
    {
        setUpdatesEnabled(true);
        update();
    }
}

QSize GlWidget::sizeHint() const
{
    return QSize(640, 480);
}

void GlWidget::initializeGL()
{
    OpenGLClient::get().initialize();

    glClearColor(0, 0, 0, 1);

    initShaders();
    initTextures();

    // Enable depth buffer
    glEnable(GL_DEPTH_TEST);

    // Enable back face culling
    glEnable(GL_CULL_FACE);

    // Use QBasicTimer because its faster than QTimer
    timer.start(12, this);
}

void GlWidget::initShaders()
{
    // Compile vertex shader
    if (!program.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/vshader.glsl"))
        close();

    // Compile fragment shader
    if (!program.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/fshader.glsl"))
        close();

    // Link shader pipeline
    if (!program.link())
        close();

    // Bind shader pipeline for use
    if (!program.bind())
        close();
}

void GlWidget::initTextures()
{
    // Load cube.png image
    texture = new QOpenGLTexture(QImage(":/cube.png").mirrored());

    // Set nearest filtering mode for texture minification
    texture->setMinificationFilter(QOpenGLTexture::Nearest);

    // Set bilinear filtering mode for texture magnification
    texture->setMagnificationFilter(QOpenGLTexture::Linear);

    // Wrap texture coordinates by repeating
    // f.ex. texture coordinate (1.1, 1.2) is same as (0.1, 0.2)
    texture->setWrapMode(QOpenGLTexture::Repeat);
}

void GlWidget::paintGL()
{
    OpenGLClient::get().update();
    setUpdatesEnabled(false);
}*/
