#include "myglwidget.h"
// #include "../model/s21_data_structure.h"
// #include "../model/s21_parse_obj.h"
// #include "../model/s21_affin_p.h"
#include <iostream>

MyGLWidget::MyGLWidget(QWidget *parent) : QOpenGLWidget(parent)
{
    setGeometry(400, 200, 800, 600);
}

QOpenGLShaderProgram *MyGLWidget::initialize_shaders() {
    const char *vertexShaderSource =
        "attribute vec3 position;\n"
        "void main()\n"
        "{\n"
        "gl_Position = vec4(position.x, position.y, "
        "position.z, "
        "1.0);\n"
        "}\0";

    const char *fragmentShaderSource =
        "uniform vec3 color;\n"
        "void main()\n"
        "{\n"
        "gl_FragColor = vec4(color.x, color.y, color.z, 1);\n"
        "}\n\0";

    QOpenGLShaderProgram *prog = new QOpenGLShaderProgram;
    prog->addShaderFromSourceCode(QOpenGLShader::Vertex, vertexShaderSource);
    prog->addShaderFromSourceCode(QOpenGLShader::Fragment,
                                  fragmentShaderSource);
    prog->bindAttributeLocation("position", 0);
    prog->link();

    return prog;
}

void MyGLWidget::initializeGL(void) {
    glEnable(GL_DEPTH_TEST); // включаю буффер глубины (хранит в себе расстояние от камеры до отрисовки)
    prog =  initialize_shaders();
    add_example() ;
}

void MyGLWidget::add_example() {
    vertex_count = 4;
    vertex_array = new float[3 * vertex_count];
    float buff_vertex[] = {-0.5, 0,   -0.5, 0.5, 0,    -0.5,
                           0,    0.5, -0.5, 0,   -0.5, -1};
    for (int i = 0; i < vertex_count * 3; i++) {
        vertex_array[i] = buff_vertex[i];
    }

    lines_count = 6;
    unsigned int buff_lines[] = {0, 1, 1, 2, 2, 0, 0, 3, 1, 3, 2, 3};
    lines_array = new unsigned int[2 * lines_count];
    for (int i = 0; i < 2 * lines_count; i++) {
        lines_array[i] = buff_lines[i];
    }
}

void MyGLWidget::paintGL(void) {

    glClearColor(0, 0, 0, 1); // настраиваю цвет окна
    prog->bind();

    QOpenGLBuffer vbo(QOpenGLBuffer::VertexBuffer);
    vbo.create();
    vbo.bind();
    vbo.setUsagePattern(QOpenGLBuffer::DynamicDraw);
    vbo.allocate(vertex_array, vertex_count * 3 * sizeof(float));

    prog->setAttributeBuffer(0, GL_FLOAT, 0, 3, 0);
    prog->enableAttributeArray(0);

    QOpenGLBuffer ibo(QOpenGLBuffer::IndexBuffer);
    ibo.create();
    ibo.bind();
    ibo.setUsagePattern(QOpenGLBuffer::DynamicDraw);
    ibo.allocate(lines_array, sizeof(unsigned int) * 2 * lines_count);

    glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_TEST);

    lineColorV = {1, 0, 0};

    prog->setUniformValue(prog->uniformLocation("color"), lineColorV);

    glLineWidth(0.5);
    glDrawElements(GL_LINES, 2 * lines_count, GL_UNSIGNED_INT, 0);

//    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_TEST); // очищаю буффер цвета и буффер глубины (каждый тик)
////    long double *f = RemakeMatrix(s);

//    glMatrixMode(GL_MODELVIEW); // указываю тип матрицы
//    glLoadIdentity(); // загружаю матрицу в стек
//    glFrustum(-1, 1, -1, 1, 1, 10);

//    //glRotatef(90, 0, 0, 1); // вращаю матрицу 90 - угол, остльное это оси
//    glTranslatef(0, 0, -3);
//    glRotatef(xRot, 1, 0, 0);
//    glRotatef(yRot, 0, 1, 0);
//    drawCube(0.5);
}

void MyGLWidget::resizeGL(int width, int height) {

/*    glViewport(0, 0, width, height); // задаю размер окна

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity(); */// загружаю едининчную матрицу
    // (-1 1 по x) (-1 1 по y) (1 расстояние от камеры до передней плоскости) (2 растоняние от камеры до задней плоскости)
    // glOrtho(-1, 1, -1, 1, 1, 2); // преобразую матрицу в ортогональную проекцию

}

void MyGLWidget::drawCube(float a) {
//     float ver_cub[] = {
//         -a, -a, a,     a, -a, a,        a, a, a,     -a, a, a, // передняя
//         a, -a, -a,    -a, -a, -a,     -a, a, -a,     a, a, -a, // задняя
//         -a, -a, -a,    -a, -a, a,     -a, a, a,     -a, a, -a, // левая
//         a, -a, a,    a, -a, -a,     a, a, -a,     a, a, a, // правая
//         -a, -a, a,    a, -a, a,     a, -a, -a,     -a, -a, -a, // нижняя
//         -a, a, a,    a, a, a,     a, a, -a,     -a, a, -a, // верхняя
//     };
//     float color_arr[] {
//         1, 0, 0,    1, 0, 0,    1, 0, 0,    1, 0, 0,
//         0, 0, 1,    0, 0, 1,    0, 0, 1,    0, 0, 1,
//         1, 1, 0,    1, 1, 0,    1, 1, 0,    1, 1, 0,
//         0, 1, 1,    0, 1, 1,    0, 1, 1,    0, 1, 1,
//         1, 0, 1,    1, 0, 1,    1, 0, 1,    1, 0, 1,
//         1, 0.5, 0.5,    1, 0.5, 0.5,    1, 0.5, 0.5,    1, 0.5, 0.5
//     };
//     data_t* s = ParseCountObj("../../../../model/obj/cube.obj");
//     int *size = NULL;
//    // long double* f = RemakeFacets(s, size);
//    // std::cout << f[0] << " SSSS" << std::endl;
//     glVertexPointer(3, GL_DOUBLE, 0, s->v_array);
//     glEnableClientState(GL_VERTEX_ARRAY);

//    //glColorPointer(3, GL_FLOAT, 0, &color_arr);
//    //glEnableClientState(GL_COLOR_ARRAY);

//   // glDrawElements(GL_LINES, 0, s->size_v, s->v_array);
//     glDrawArrays(GL_LINES, 0, s->size);
//     // glDrawArrays(GL_PATCHES, 0, 24);

//    // glDisableClientState(GL_COLOR_ARRAY);
//     glDisableClientState(GL_VERTEX_ARRAY);
}

void MyGLWidget::mousePressEvent(QMouseEvent * mo) {
    mPos = mo->pos();
}

void MyGLWidget::mouseMoveEvent(QMouseEvent * mo) {
    xRot = 1 / M_PI * (mo->pos().y() - mPos.y());
    yRot = 1 / M_PI * (mo->pos().x() - mPos.x());
    update();
}
