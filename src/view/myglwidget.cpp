#include "myglwidget.h"

MyGLWidget::MyGLWidget(QWidget *parent) : QOpenGLWidget(parent)
{

}

void MyGLWidget::initializeGL(void) {
    float r, g, b, a = 1.0f;
    initializeOpenGLFunctions();
    qColorToRGB(Qt::red, r, g, b);
    glClearColor(r, g, b, a);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHTING);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);
}

void MyGLWidget::paintGL(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

}

void MyGLWidget::resizeGL(int width, int height) {
//    glViewport(0, 0, width, height);
//    glMatrixMode(GL_PROJECTION);
//    glLoadIdentity();
//    glMatrixMode(GL_MODELVIEW);
//    glLoadIdentity();
}

void MyGLWidget::qColorToRGB(const QColor &C, float &r, float &g, float &b) const
{
    r = normaliza_0_1(C.red(), 1.0f, 255.0f);
    g = normaliza_0_1(C.green(), 1.0f, 255.0f);
    b = normaliza_0_1(C.blue(), 1.0f, 255.0f);
}

float MyGLWidget::normaliza_0_1(float val, float min, float max) const
{
    return (val - min) / (max - min);
}



