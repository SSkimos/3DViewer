#ifndef MYGLWIDGET_H_
#define MYGLWIDGET_H_

#include <QColorDialog>
#include <QGraphicsSceneMouseEvent>
#include <QMessageBox>
#include <QMouseEvent>
#include <QOpenGLBuffer>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLWidget>
#include <QTimer>
#include <QtOpenGL>
#include <fstream>
#include <iostream>

#include "../model/s21_data_structure.h"
// #include <glu.h>

class MyGLWidget : public QOpenGLWidget {
  Q_OBJECT
 public:
  MyGLWidget(QWidget *parent = nullptr);

 protected:
  void initializeGL() override;
  void paintGL() override;
  void resizeGL(int width, int height) override;

  void mousePressEvent(QMouseEvent *) override;  // вызывается при нажатии мышки
  void mouseMoveEvent(QMouseEvent *) override;  // вызывается при движении мышки

 private:
  float xRot, yRot, zRot;
  QPoint mPos;
  QTimer tmr;
  void drawCube(float a);
  QOpenGLShaderProgram *compileShaders();
  QOpenGLVertexArrayObject vao;
  //  QOpenGLVertexArrayObject *ibo;
  //  QOpenGLVertexArrayObject *vbo;
  QOpenGLBuffer InitVertexBuffer();
  void clearVAO();
  void clearVBO();
  void clearIBO();

 public:
  void clearBuffers();
  void initBuffers();
  QOpenGLShaderProgram *prog = nullptr;
  int GetData();
  int ModifyData();
  int DrawData();
  data_t *object;
  char* filename_const;
  int file_load;
  int vertex_count;
  int lines_count;
  float *vertex_array;
  unsigned int *lines_array;
  float *base_vertex_array;
  unsigned int *base_lines_array;
  QVector3D lineColorV = {1, 1, 1};
  QVector3D verticleColorV = {1, 0, 0};
  QMatrix4x4 camera;
  QMatrix4x4 projection;
  int m_coeffMatrixLoc = 0;
  void InitProjection(int width, int height);
  int projectionNeeded = 1;

  double rotateX;
  double rotateY;
  double rotateZ;

  double moveX;
  double moveY;
  double moveZ;

  double scale_val;
  double moveMod;

  QString filename;
};

#endif  // MYGLWIDGET_H_
