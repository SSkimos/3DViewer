#include "myglwidget.h"
#include "../model/s21_data_structure.h"
#include "../model/s21_parse_obj.h"
#include "../model/s21_affin_p.h"
#include <iostream>

MyGLWidget::MyGLWidget(QWidget *parent) : QOpenGLWidget(parent)
{

}

void MyGLWidget::initializeGL(void) {
    float r, g, b, a = 1.0f;
    initializeOpenGLFunctions();
    qColorToRGB(Qt::white, r, g, b);
    glClearColor(r, g, b, a);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHTING);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);
}

void MyGLWidget::paintGL(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    data_t* s = ParseCountObj("../../../../model/obj/cube.obj");
    glLoadIdentity();
    // MatrixMove(&(s->matrix_3d), 10, kX);
//    MatrixScale(&(s->matrix_3d), 0.1);
    glEnableClientState(GL_VERTEX_ARRAY);
    RotationX(&(s->matrix_3d), 2);
    for (int i = 1; i < s->matrix_3d.rows; i++) {
        glVertexPointer(3, GL_FLOAT, 0, s->matrix_3d.matrix[i]);
        // glVertex3f(s->matrix_3d.matrix[i][0], s->matrix_3d.matrix[i][1], s->matrix_3d.matrix[i][2]);
        std::string a = std::to_string(s->matrix_3d.matrix[0][i]) + " " + std::to_string(s->matrix_3d.matrix[1][i]) + " " + std::to_string(s->matrix_3d.matrix[2][i]);
        std::cout << a  << "cycle" << std::endl;
        glColor3ub(255,0,0);
    }
    glDrawArrays(GL_TRIANGLES,0,3);
    //QTextStream(stdout) << "\n\n\nSSASDASdasddsfdfsdaf";



    // Сначала расставляем точки на нашей поверхности. Для этого идём по matrix_3d  и выставляем точки в значениях x и y.
    // Данная отрисовка точек будет иметь параллельную проекцию (вы можете данный пункт пропустить, но он необходим для бонусной части).
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



