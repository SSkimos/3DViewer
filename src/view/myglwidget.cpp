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
  qDebug() << "Nullify";
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
    std::cout << "maybe object" << std::endl;
  if (!object) {
    if (file_load == 0) RemoveObject(object);
    std::cout << "no object" << std::endl;
    file_load = GetData();
  }
  if (object && file_load == 0) {
    ModifyData();
    initBuffers();
  }
}

int inad = 0;

int MyGLWidget::ModifyData(void) {
  affine_t* v = (affine_t*) malloc(1*sizeof(*v));
  for (size_t i = 0; i != object->vertices_count; ++i) {
    object->vertex_array[i] = object->base_vertex_array[i];
  }
  for (size_t i = 0; i != object->size_f; ++i) {
    object->lines_array[i] = object->base_vertex_array[i];
  }
  if (v) {
    v->rotateX = rotateX;
    v->rotateY = rotateY;
    v->rotateZ = rotateZ;
    v->scale = scale_val;
    v->moveX = moveX / 100.0;
    v->moveY = moveY / 100.0;
    v->moveZ = moveZ / 100.0;
    std::cout << "tryng object" << std::endl;
    MoveAndRotateModel(&object, v);
  }
  free(v);
  vertex_array = object->vertex_array;
  lines_array = object->lines_array;
  std::cout << vertex_count << ' ' << (++inad) << std::endl;
}

int MyGLWidget::GetData() {
  int ret_code = 0;
  int debug = 1;
  // if max == 4000
  // scale = 1/4000
  if (filename.size() > 0) {
    const char *c_str2 =  qPrintable(filename);
    if (c_str2 && strlen(c_str2) > 0) { 
      if (!debug) object = ParseCountObj(c_str2);
      else object = ParseCountObj("obj/cube.obj");
      vertex_count = object->vertices_count / 3;
      lines_count = object->facets_count;
      base_vertex_array = object->vertex_array;
      base_lines_array = object->lines_array;
    }
  } else {
    ret_code = 1;
  }
  return ret_code;
}

/* void MyGLWidget::add_example() {
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
   } */

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
  ibo.allocate(lines_array, sizeof(unsigned int) * 5 * lines_count);

  glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_TEST);

  lineColorV = {1, 4, 0};

  prog->setUniformValue(prog->uniformLocation("color"), lineColorV);

  glLineWidth(0.5);
  glDrawElementsBaseVertex(GL_LINES, 5 * lines_count, GL_UNSIGNED_INT, 0, 0);

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
