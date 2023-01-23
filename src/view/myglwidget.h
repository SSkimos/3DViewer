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
#include <QColorDialog>

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
  void mousePressEvent(QMouseEvent *) override;
  void mouseMoveEvent(QMouseEvent *) override;

 private:
  float xRot, yRot, zRot;
  QPoint mPos;
  QTimer tmr;
  void drawCube(float a);
  QOpenGLShaderProgram *compileShaders(void);
  QOpenGLVertexArrayObject vao;
  QOpenGLBuffer InitVertexBuffer(void);
  QOpenGLBuffer InitIndexBuffer(data_t *object);
  void clearVAO(QOpenGLVertexArrayObject &vao);
  void clearVBO(QOpenGLBuffer &vbo);
  void clearIBO(QOpenGLBuffer &ibo);
  void CopyVertexFromBase(data_t** object);
  void CopyIndexFromBase(data_t** object);
  affine_t* LoadAffineData(affine_t* v);
  void SaveNewVertexArray(data_t* object);
  void SaveNewIndexArray(data_t* object);
  void InitProjection(int width, int height);

 public:
  void clearBuffers(QOpenGLVertexArrayObject &vao, QOpenGLBuffer &vbo,
      QOpenGLBuffer &ibo);
  void initBuffers();
  QOpenGLShaderProgram *prog = nullptr;
  int GetData(const char* filename_const);
  int ModifyData();
  int DrawData();
  data_t *object;
  char *filename_const;
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
  int ProjectionViewMatrix= 0;
  int projectionNeeded = 1;

  double rotateX;
  double rotateY;
  double rotateZ;

  double moveX;
  double moveY;
  double moveZ;

  int projType;

  double scale_val;
  double moveMod;

  QString filename;
  QColor backgroundColor = QColorConstants::White;
  QColor peaksColor = QColorConstants::White;
  QColor linesColor = QColorConstants::White;
};

#endif  // MYGLWIDGET_H_
