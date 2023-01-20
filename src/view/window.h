#ifndef WINDOW_H
#define WINDOW_H

#include <QApplication>
#include <QFileDialog>
#include <QMainWindow>
#include <QOpenGLWidget>
#include <QSettings>
#include <QTimer>
#include <QtOpenGL>

#include "ima/qgifimage_p.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class Window;
}
QT_END_NAMESPACE

class Window : public QMainWindow {
  Q_OBJECT

 public:
  Window(QWidget *parent = nullptr);
  ~Window();

 private slots:
  void on_chooseFileButton_clicked();
  void on_makeGIFButton_clicked();
  void timer_grab();
  void xRotateTextEdit(const QString & val);
  // void xRotateTextEdit();

 private:
  Ui::Window *ui;
  void ConnectSliders();
  void ScaleChange(int val);
  void ConnectLabels();
  void SaveSettings();
  void SaveSldrGroupSettings(QSettings *settings);
  void RestoreSettings();
  void InitSldrGroupSettings(QSettings *settings);

  void xMoveSetText(double value);
  void xMoveEdit(double value);
  void xMoveSldr(double value);

  void SetRotateX(QSettings *settings);  // TODO: не нравится нейминг
  void SetRotateY(QSettings *settings);
  void SetRotateZ(QSettings *settings);

  void SetMoveX(QSettings *settings);  // TODO: не нравится нейминг
  void SetMoveY(QSettings *settings);
  void SetMoveZ(QSettings *settings);

  void print_grab();

  QTimer *timer_gif;
  int check;
  QGifImage gif;
  QImage mp[50];
};
#endif  // WINDOW_H
