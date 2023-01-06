#ifndef MYGLWIDGET_H_
#define MYGLWIDGET_H_

#include <QColorDialog>
#include <QMouseEvent>
#include <QOpenGLWidget>
#include <QTimer>
#include <QtOpenGL>


#include <QGraphicsSceneMouseEvent>

#include <iostream>
#include <fstream>

#include <QMessageBox>
#include <QMouseEvent>
#include <QOpenGLBuffer>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLVertexArrayObject>
#include <glu.h>

class MyGLWidget: public QOpenGLWidget
{
    Q_OBJECT
public :
    MyGLWidget(QWidget *parent = nullptr);

protected:
    void initializeGL() override;
    void paintGL() override;
    void resizeGL(int width, int height) override;

    void mousePressEvent(QMouseEvent *) override; // вызывается при нажатии мышки
    void mouseMoveEvent(QMouseEvent *) override; // вызывается при движении мышки

private:
    float xRot, yRot, zRot;
    QPoint mPos;
    QTimer tmr;
    void drawCube(float a);

 public:
    double scale;
    QOpenGLShaderProgram *prog = nullptr;
    QOpenGLShaderProgram *initialize_shaders();
    void add_example();
    int vertex_count;
    int lines_count;
    float *vertex_array;
    unsigned int *lines_array;
    QVector3D lineColorV = {1, 1, 1};
    QVector3D verticleColorV = {1, 0, 0};
    int m_coeffMatrixLoc = 0;

};




#endif // MYGLWIDGET_H_
