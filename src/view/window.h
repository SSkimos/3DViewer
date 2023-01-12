#ifndef WINDOW_H
#define WINDOW_H

#include <QOpenGLWidget>
#include <QtOpenGL>
#include <QTimer>
#include <QMainWindow>
#include <QFileDialog>

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
    void on_chooseFileButton_clicked();
    

private:
    Ui::Window *ui;
};
#endif // WINDOW_H
