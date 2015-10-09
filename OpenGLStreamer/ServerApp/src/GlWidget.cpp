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
    glClearColor (0.0, 0.0, 0.0, 0.0);
    glClear (GL_COLOR_BUFFER_BIT);
    glColor3f (0.0, 0.0, 1.0);
    glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);
}

void GlWidget::resizeGL(int width, int height)
{

}

void GlWidget::paintGL()
{
    glBegin(GL_POLYGON);
    glVertex3f (0.25, 0.25, 0.0);
    glVertex3f (0.75, 0.25, 0.0);
    glVertex3f (0.75, 0.75, 0.0);
    glVertex3f (0.25, 0.75, 0.0);
    glEnd();
    glFlush();

}
