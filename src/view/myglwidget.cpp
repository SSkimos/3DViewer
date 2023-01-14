#include "myglwidget.h"
#include <QDebug>
#include <string>
#include "../model/s21_data_structure.h"
#include "../model/s21_parse_obj.h"
#include "../model/s21_affin_p.h"
#include <iostream>

MyGLWidget::MyGLWidget(QWidget *parent) : QOpenGLWidget(parent)
{
    setGeometry(400, 200, 800, 600);
}

void MyGLWidget::initializeGL(void) {
  glEnable(GL_DEPTH_TEST);
  prog = compileShaders();
}

QOpenGLShaderProgram *MyGLWidget::compileShaders() {
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

void MyGLWidget::paintGL(void) {
  glClearColor(0, 0, 0, 1); // настраиваю цвет окна
  prog->bind();
  // std::cout << moveX << std::endl;
  // TODO: функция, для получения массива из файла
  // TODO: набор функций, в результате выполнения которых мы получаем буффер матрицу, которую загрузим в файл
  // TODO: удалить add_example()
  int data = GetData();
  if (data > 0) {
     initBuffers();
  }
}

int MyGLWidget::GetData() {
  int ret_code = 0;
  // vertex_count = 8;
  // vertex_array = new float[3 * vertex_count]; // CALLOC

  // data_t* s = ParseCountObj("model/obj/cube.obj");
  int debug = 1;
  if (debug == 1 || filename.size() > 0) {
    affine_t* v = (affine_t*) malloc(1*sizeof(*v));
    v->rotateX = rotateX;
    v->rotateY = rotateY;
    v->rotateZ = rotateZ;
    std::cout << v->rotateX << std::endl;
    v->moveX = moveX / 100.0;
    v->moveY = moveY / 100.0;
    v->moveZ = moveZ / 100.0;
    printf("%f = F\n", v->moveZ);
    const char *c_str2 =  "model/obj/cube.obj";
    if (c_str2 && strlen(c_str2) > 1) { 
      data_t* s = ParseCountObj(c_str2);
      MoveAndRotateModel(&s, v);
      vertex_count = s->vertices_count;
      lines_count = s->facets_count;
      vertex_array = s->vertex_array;
      lines_array = s->lines_array;
    }
    free(v);
    ret_code = 1;
  } else {
    ret_code = 0;
  }
  return ret_code;
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

void MyGLWidget::initBuffers() {
  clearBuffers();

  // TODO: попробовать вынести VAO 
  vao.create();
  vao.bind();

  // TODO: вынести? createVBO()
  QOpenGLBuffer vbo(QOpenGLBuffer::VertexBuffer);
  vbo.create();
  vbo.bind();
  vbo.setUsagePattern(QOpenGLBuffer::DynamicDraw);
  vbo.allocate(vertex_array, vertex_count * 3 * sizeof(float));

  prog->setAttributeBuffer(0, GL_FLOAT, 0, 3, 0);
  prog->enableAttributeArray(0);

  // TODO: вынести? createIBO()
  QOpenGLBuffer ibo(QOpenGLBuffer::IndexBuffer);
  ibo.create();
  ibo.bind();
  ibo.setUsagePattern(QOpenGLBuffer::DynamicDraw);
  ibo.allocate(lines_array, sizeof(unsigned int) * 2 * lines_count);

  glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_TEST);

  lineColorV = {1, 0, 0};

  prog->setUniformValue(prog->uniformLocation("color"), lineColorV);

  glLineWidth(0.5);
  glDrawElementsBaseVertex(GL_LINES, 2 * lines_count, GL_UNSIGNED_INT, 0, 0);

  vao.release();
}

void MyGLWidget::clearBuffers() {
  clearVAO();
  // clearVBO();
  // clearIBO();
}

void MyGLWidget::clearVAO() {
  if (vao.isCreated()) {
    vao.destroy();
  }
}

void MyGLWidget::clearVBO() {
  // if (vbo->isCreated()) {
  //   vbo->destroy();
  // }
}

void MyGLWidget::clearIBO() {
  // if (ibo->isCreated()) {
  //   ibo->destroy();
  // }
}

void MyGLWidget::resizeGL(int width, int height) {

}

void MyGLWidget::mousePressEvent(QMouseEvent * mo) {
  mPos = mo->pos();
}

void MyGLWidget::mouseMoveEvent(QMouseEvent * mo) {
  xRot = 1 / M_PI * (mo->pos().y() - mPos.y());
  yRot = 1 / M_PI * (mo->pos().x() - mPos.x());
  update();
}
