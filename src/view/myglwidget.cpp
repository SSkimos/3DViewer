#include "myglwidget.h"
#include <QDebug> 
#include <QSize>
#include <string>
#include "../model/s21_data_structure.h"
#include "../model/s21_parse_obj.h"
#include "../model/s21_affin_p.h"
#include <iostream>

MyGLWidget::MyGLWidget(QWidget *parent) : QOpenGLWidget(parent)
{
  setGeometry(400, 200, 800, 600);
  projType = 0;
  scale_val = 1;
}

void MyGLWidget::initializeGL(void) {
  glEnable(GL_DEPTH_TEST);
  prog = compileShaders();
  file_load = 1;
  object = NULL;
  ProjectionViewMatrix= prog->uniformLocation("coeffMatrix");
}

QOpenGLShaderProgram *MyGLWidget::compileShaders() {
  const char *vertexShaderSource =
    "attribute vec3 position;\n"
    "uniform mat4 coeffMatrix;\n" 
    "void main()\n"
    "{\n"
    "gl_Position = coeffMatrix * vec4(position.x, position.y, "
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
  if (backgroundColor.isValid()) {
    int r = backgroundColor.redF();
    int g = backgroundColor.greenF();
    int b = backgroundColor.blueF();
    int a = backgroundColor.alphaF();
    glClearColor(r, g, b, a);
  } else {
    glClearColor(0, 0, 0, 1);
  }
  prog->bind();
  if (file_load == 1) {
    RemoveObject(object);
    GetData(filename_const);
    file_load = 0;
  }
  if (object) {
    ModifyData();
    initBuffers();
  }
}

void MyGLWidget::resizeGL(int width, int height) {
  InitProjection(width, height);
}


int MyGLWidget::ModifyData(void) {
  affine_t* ui_data = InitAffine();
  if (ui_data) {
    LoadAffineData(ui_data);
    CopyVertexFromBase(&object);
    CopyIndexFromBase(&object);
    MoveAndRotateModel(&object, ui_data);
    SaveNewIndexArray(object);
    SaveNewVertexArray(object);
    free(ui_data);
  }
  return 0;
}

int MyGLWidget::GetData(const char* filename_const) {
  int ret_code = 0;
  if (filename_const) {
    object = LoadObjFile(filename_const);
    if (object) {
      vertex_count = object->vertices_count / 3;
      lines_count = object->facets_count;
    }
  } else {
    ret_code = 1;
  }
  return ret_code;
}

affine_t* MyGLWidget::LoadAffineData(affine_t* v) {
  v->rotateX = rotateX;
  v->rotateY = rotateY;
  v->rotateZ = rotateZ;
  v->scale = scale_val * 10;
  v->modMove = moveMod;
  v->moveX = moveX / 100.0;
  v->moveY = moveY / 100.0;
  v->moveZ = moveZ / 100.0;
  return v;
}

void MyGLWidget::CopyVertexFromBase(data_t** object) {
  for (int i = 0; i != (*object)->vertices_count; ++i) {
    (*object)->vertex_array[i] = (*object)->base_vertex_array[i];
  }
}
void MyGLWidget::CopyIndexFromBase(data_t** object) {
  for (int i = 0; i != (*object)->size_f; ++i) {
    (*object)->lines_array[i] = (*object)->base_lines_array[i];
  }
}

void MyGLWidget::SaveNewVertexArray(data_t* object) {
  vertex_array = object->vertex_array;
}

void MyGLWidget::SaveNewIndexArray(data_t* object) {
  lines_array = object->lines_array;
}


QOpenGLBuffer MyGLWidget::InitVertexBuffer() {
  QOpenGLBuffer vbo(QOpenGLBuffer::VertexBuffer);
  vbo.create();
  vbo.bind();
  vbo.setUsagePattern(QOpenGLBuffer::DynamicDraw);
  vbo.allocate(vertex_array, vertex_count * 3 * sizeof(float));
  return vbo;
}

QOpenGLBuffer MyGLWidget::InitIndexBuffer(data_t* object) {
  QOpenGLBuffer ibo(QOpenGLBuffer::IndexBuffer);
  ibo.create();
  ibo.bind();
  ibo.setUsagePattern(QOpenGLBuffer::DynamicDraw);
  ibo.allocate(lines_array, sizeof(unsigned int) * object->size_f);
  return ibo;
}

void MyGLWidget::initBuffers() {

  vao.create();
  vao.bind();

  QOpenGLBuffer vbo;
  QOpenGLBuffer ibo;
  vbo = InitVertexBuffer();
  ibo = InitIndexBuffer(object);
  InitProjection(0, 0);

  prog->setAttributeBuffer(0, GL_FLOAT, 0, 3, 0);
  prog->enableAttributeArray(0);
  prog->setUniformValue(ProjectionViewMatrix
      , projection*camera);


  glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_TEST);
  float r = linesColor.redF();
  float g = linesColor.greenF();
  float b = linesColor.blueF();
 if (linesColor.isValid() || (r && g && b)) {
   lineColorV.setX(r);
   lineColorV.setY(g);
   lineColorV.setZ(b);
  // lineColorV = {r, g, b};
 }

  prog->setUniformValue(prog->uniformLocation("color"), lineColorV);

  glLineWidth(0.5);
  glDrawElementsBaseVertex(GL_LINES, object->size_f, GL_UNSIGNED_INT, 0, 0);

  vao.release();
  clearBuffers(vao, vbo, ibo);
}

void MyGLWidget::clearBuffers(QOpenGLVertexArrayObject &vao, QOpenGLBuffer &vbo, QOpenGLBuffer &ibo) {
  clearVAO(vao);
  clearVBO(vbo);
  clearIBO(ibo);
}

void MyGLWidget::InitProjection(int w, int h) {
  if (w < 1 || h < 1) {
    w = width();
    h = height();
  }
  camera.setToIdentity();
  projection.setToIdentity();
  if (projType) {
    projection.perspective(45.0f, GLfloat(w) / h, 0.01f, 100.0f);
    camera.translate(0, 0, -25);
    moveMod = 1;
  } else {
    float top, bottom, right,left, aspect;
    aspect = (GLfloat)w/h;
    if (w > h) {
      top = 1.5f;
      bottom = -top;
      right = top * aspect;
      left = -right;
    } else {
      right = 1.5f;
      left = -right;
      top = right/aspect;
      bottom = -top;
    }
    camera.ortho(left*10, right*10, bottom*10, top*10, -100.0f, 100.0f);
    moveMod = 10;
  }
}

void MyGLWidget::clearVAO(QOpenGLVertexArrayObject &vao) {
  if (vao.isCreated()) vao.destroy();
}

void MyGLWidget::clearVBO(QOpenGLBuffer &vbo){
  if (vbo.isCreated()) vbo.destroy();
}

void MyGLWidget::clearIBO(QOpenGLBuffer &ibo){
  if (ibo.isCreated()) ibo.destroy();
}

void MyGLWidget::mousePressEvent(QMouseEvent * mo) {
  mPos = mo->pos();
}

void MyGLWidget::mouseMoveEvent(QMouseEvent * mo) {
  xRot = 1 / M_PI * (mo->pos().y() - mPos.y());
  yRot = 1 / M_PI * (mo->pos().x() - mPos.x());
  update();
}
