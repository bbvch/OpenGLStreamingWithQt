#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QOpenGLShaderProgram>
#include <QOpenGLWidget>
#include <QWidget>

class GlWidget : public QOpenGLWidget
{
    Q_OBJECT

public:
    GlWidget(QWidget *parent = 0);
    ~GlWidget();
    QSize sizeHint() const;

protected:
    void initializeGL();
    void resizeGL(int width, int height);
    void paintGL();
    void mousePressEvent(QMouseEvent* event);
	void mouseMoveEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent *event);

private:
    QMatrix4x4 mMatrix;
    QOpenGLShaderProgram mShaderProgram;
    QVector<QVector3D> mVertices;
    QVector<QVector3D> colors;

	double alpha;
	double beta;
	double distance;
	QPoint lastMousePosition;
};

#endif // GLWIDGET_H
