#ifndef WINDOW_H
#define WINDOW_H

#include <QOpenGLWidget>
#include <QtOpenGL>
#include <QTimer>
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class Window; }
QT_END_NAMESPACE

class Window : public QMainWindow
{
    Q_OBJECT

public:
    Window(QWidget *parent = nullptr);
    ~Window();

private slots:
    

private:
    Ui::Window *ui;
};
#endif // WINDOW_H
