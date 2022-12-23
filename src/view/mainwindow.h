#ifndef MAINWINDOW_H
#define MAINWINDOW_H

//#include <QGLWidget>
#include <QOpenGLWidget>
#include <QtOpenGL>
#include <QTimer>
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_xMove_sldr_valueChanged(int value);
    void on_zMove_sldr_valueChanged(int value);
    void on_yMove_sldr_valueChanged(int value);

    void on_xRotate_sldr_valueChanged(int value);
    void on_zRotate_sldr_valueChanged(int value);
    void on_yRotate_sldr_valueChanged(int value);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
