#include "GlWidget.h"

#include <QMouseEvent>

#include <math.h>

GlWidget::GlWidget(QWidget *parent) :
    QOpenGLWidget(parent),
    mpGeometries(0),
    texture(0),
    angularSpeed(0),
    mpOpenGLProxy(new OpenGLProxy())
{}

GlWidget::~GlWidget()
{
    // Make sure the context is current when deleting the texture
    // and the buffers.
    makeCurrent();
    delete texture;
    delete mpGeometries;
    doneCurrent();
}

void GlWidget::mousePressEvent(QMouseEvent* event)
{
    // Save mouse press position
    mousePressPosition = QVector2D(event->localPos());
}


void GlWidget::mouseReleaseEvent(QMouseEvent *e)
{
    // Mouse release position - mouse press position
    QVector2D diff = QVector2D(e->localPos()) - mousePressPosition;

    // Rotation axis is perpendicular to the mouse position difference
    // vector
    QVector3D n = QVector3D(diff.y(), diff.x(), 0.0).normalized();

    // Accelerate angular speed relative to the length of the mouse sweep
    qreal acc = diff.length() / 100.0;

    // Calculate new rotation axis as weighted sum
    rotationAxis = (rotationAxis * angularSpeed + n * acc).normalized();

    // Increase angular speed
    angularSpeed += acc;
}


void GlWidget::timerEvent(QTimerEvent *)
{
    // Decrease angular speed (friction)
    angularSpeed *= 0.99;

    // Stop rotation when speed goes below threshold
    if (angularSpeed < 0.01) {
        angularSpeed = 0.0;
    } else {
        // Update rotation
        rotation = QQuaternion::fromAxisAndAngle(rotationAxis, angularSpeed) * rotation;

        // Request an update
        update();
    }
}

QSize GlWidget::sizeHint() const
{
    return QSize(640, 480);
}

void GlWidget::initializeGL()
{
    mpOpenGLProxy->initialize();

    OPENGL_CALL(glClearColor, 0, 0, 0, 1);

    initShaders();
    initTextures();

    // Enable depth buffer
    OPENGL_CALL(glEnable, GL_DEPTH_TEST);

    // Enable back face culling
    OPENGL_CALL(glEnable, GL_CULL_FACE);

    mpGeometries = new GeometryEngine(mpOpenGLProxy.get());

    // Use QBasicTimer because its faster than QTimer
    timer.start(12, this);
}

void GlWidget::resizeGL(int width, int height)
{
    // Calculate aspect ratio
    qreal aspect = qreal(width) / qreal(height ? height : 1);

    // Set near plane to 3.0, far plane to 7.0, field of view 45 degrees
    const qreal zNear = 3.0, zFar = 7.0, fov = 45.0;

    // Reset projection
    projection.setToIdentity();

    // Set perspective projection
    projection.perspective(fov, aspect, zNear, zFar);
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
    // Clear color and depth buffer
    OPENGL_CALL(glClear, GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    texture->bind();

    // Calculate model view transformation
    QMatrix4x4 matrix;
    matrix.translate(0.0, 0.0, -5.0);
    matrix.rotate(rotation);

    // Set modelview-projection matrix
    //program.setUniformValue("mvp_matrix", projection * matrix);
    OPENGL_CALL_V(glUniformMatrix, 4, f, OPENGL_CALL(glGetUniformLocation, program.programId(), "mvp_matrix"),
                1, GL_FALSE, (projection * matrix).constData());

    // Use texture unit 0 which contains cube.png
    //program.setUniformValue("texture", 0);
    OPENGL_CALL(glUniform1i, OPENGL_CALL(glGetUniformLocation, program.programId(), "texture"), 0);

    // Draw cube geometry
    mpGeometries->drawCubeGeometry(&program);
}
