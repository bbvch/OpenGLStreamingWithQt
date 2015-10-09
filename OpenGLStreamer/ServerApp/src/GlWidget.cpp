#include  <QMouseEvent>
#include <QOpenGLFunctions>
#include "GlWidget.h"

GlWidget::GlWidget(QWidget *parent)
    : QOpenGLWidget(parent)
{
    alpha    =  25;
    beta     = -25;
    distance =  2.5;
}

GlWidget::~GlWidget()
{

}

void GlWidget::mousePressEvent(QMouseEvent* event)
{
    lastMousePosition = event->pos();
    event->accept();
}

void GlWidget::mouseMoveEvent(QMouseEvent *event)
{
    int deltaX = event->x() - lastMousePosition.x();
    int deltaY = event->y() - lastMousePosition.y();
    if (event->buttons() & Qt::LeftButton) {
        alpha -= deltaX;

        while (alpha < 0) {
            alpha += 360;
        }
        while (alpha >= 360) {
            alpha -= 360;
        }

        beta -= deltaY;

        if (beta < -90) {
            beta = -90;
        }
        if (beta > 90) {
            beta = 90;
        }
        update();
    }
    lastMousePosition = event->pos();
    event->accept();
}

void GlWidget::wheelEvent(QWheelEvent *event)
{
    int delta = event->delta();
    if (event->orientation() == Qt::Vertical) {
        if (delta < 0) {
            distance *= 1.1;
        } else if (delta > 0) {
            distance *= 0.9;
        }
        update();
    }
    event->accept();
}

QSize GlWidget::sizeHint() const
{
    return QSize(640, 480);
}

void GlWidget::initializeGL()
{
    QOpenGLFunctions *f = QOpenGLContext::currentContext()->functions();
    f->glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    mShaderProgram.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/vertexShader.vsh");
    mShaderProgram.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/fragmentShader.fsh");

    mVertices << QVector3D(-0.5, -0.5, 0.5)   << QVector3D( 0.5, -0.5, 0.5)   << QVector3D( 0.5, 0.5, 0.5) // Front
    << QVector3D( 0.5, 0.5, 0.5)    << QVector3D(-0.5, 0.5, 0.5)    << QVector3D(-0.5, -0.5, 0.5)
    << QVector3D( 0.5, -0.5, -0.5)  << QVector3D(-0.5, -0.5, -0.5)  << QVector3D(-0.5, 0.5, -0.5) // Back
    << QVector3D(-0.5, 0.5, -0.5)   << QVector3D( 0.5, 0.5, -0.5)   << QVector3D( 0.5, -0.5, -0.5)
    << QVector3D(-0.5, -0.5, -0.5)  << QVector3D(-0.5, -0.5, 0.5)   << QVector3D(-0.5, 0.5, 0.5) // Left
    << QVector3D(-0.5, 0.5, 0.5)    << QVector3D(-0.5, 0.5, -0.5)   << QVector3D(-0.5, -0.5, -0.5)
    << QVector3D( 0.5, -0.5, 0.5)   << QVector3D( 0.5, -0.5, -0.5)  << QVector3D( 0.5, 0.5, -0.5) // Right
    << QVector3D( 0.5, 0.5, -0.5)   << QVector3D( 0.5, 0.5, 0.5)    << QVector3D( 0.5, -0.5, 0.5)
    << QVector3D(-0.5, 0.5, 0.5)    << QVector3D( 0.5, 0.5, 0.5)    << QVector3D( 0.5, 0.5, -0.5) // Top
    << QVector3D( 0.5, 0.5, -0.5)   << QVector3D(-0.5, 0.5, -0.5)   << QVector3D(-0.5, 0.5, 0.5)
    << QVector3D(-0.5, -0.5, -0.5)  << QVector3D( 0.5, -0.5, -0.5)  << QVector3D( 0.5, -0.5, 0.5) // Bottom
    << QVector3D( 0.5, -0.5, 0.5)   << QVector3D(-0.5, -0.5, 0.5)   << QVector3D(-0.5, -0.5, -0.5);

}

void GlWidget::resizeGL(int width, int height)
{
    if( height == 0 )
        height = 1;

    // Update projection matrix and other size related settings:
     mMatrix.setToIdentity();
     mMatrix.perspective(60.0f, width / float(height), 0.01f, 100.0f);

    glViewport(0, 0, width, height);
}

void GlWidget::paintGL()
{
    // Draw the scene:
    QOpenGLFunctions *f = QOpenGLContext::currentContext()->functions();
    f->glClear(GL_COLOR_BUFFER_BIT);
    QMatrix4x4 m_Matrix;
    QMatrix4x4 p_Matrix;

    QMatrix4x4 cameraTransformation;
    cameraTransformation.rotate(alpha, 0, 1, 0);
    cameraTransformation.rotate(beta, 0, 1, 0);

    QVector3D cameraPostion     = cameraTransformation * QVector3D(0, 0, distance);
    QVector3D cameraUpDirection = cameraTransformation * QVector3D(0, 1, 0);

    p_Matrix.lookAt(cameraPostion, QVector3D(0,0,0), cameraUpDirection);

    mShaderProgram.bind();
    mShaderProgram.setUniformValue("qt_ModelViewProjectionMatrix", mMatrix*p_Matrix*m_Matrix);
    mShaderProgram.setUniformValue("color", QColor(Qt::white));
    mShaderProgram.setAttributeArray("vertex", mVertices.constData());
    mShaderProgram.enableAttributeArray("vertex");

    glDrawArrays(GL_TRIANGLES, 0, mVertices.size());

    mShaderProgram.disableAttributeArray("vertex");
    mShaderProgram.release();
}
