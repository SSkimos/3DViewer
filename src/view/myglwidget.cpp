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
  file_load = 1;
  object = NULL;
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
  if (file_load == 1) {
    RemoveObject(object);
    GetData();
    file_load = 0;
  }
  if (object) {
    ModifyData();
    initBuffers();
  }
}

int MyGLWidget::ModifyData(void) {
    affine_t* v = (affine_t*) malloc(1*sizeof(*v));
    v->rotateX = rotateX;
    v->rotateY = rotateY;
    v->rotateZ = rotateZ;
    v->scale = scale_val;
    v->moveX = moveX / 100.0;
    v->moveY = moveY / 100.0;
    v->moveZ = moveZ / 100.0;
    for (int i = 0; i != object->vertices_count; ++i) {
      object->vertex_array[i] = object->base_vertex_array[i];
    }
    for (int i = 0; i != object->size_f; ++i) {
      object->lines_array[i] = object->base_lines_array[i];
    }
    MoveAndRotateModel(&object, v);
    vertex_array = object->vertex_array;
    lines_array = object->lines_array;
}

int MyGLWidget::GetData() {
  int ret_code = 0;
  int debug = 1;
  if (filename.size() > 0) {
    const char *c_str2 =  qPrintable(filename);
    if (c_str2 && strlen(c_str2) > 1 || debug == 1) { 
      object = ParseCountObj(c_str2);
      vertex_count = object->vertices_count / 3;
      lines_count = object->facets_count;
    }
  } else {
    ret_code = 1;
  }
  return ret_code;
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
  ibo.allocate(lines_array, sizeof(unsigned int) * object->size_f);

  glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_TEST);

  lineColorV = {1, 0, 0};

  prog->setUniformValue(prog->uniformLocation("color"), lineColorV);

  glLineWidth(0.5);
  glDrawElementsBaseVertex(GL_LINES, object->size_f, GL_UNSIGNED_INT, 0, 0);

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
