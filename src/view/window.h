#ifndef WINDOW_H
#define WINDOW_H

#include <QOpenGLWidget>
#include <QtOpenGL>
#include <QTimer>
#include <QMainWindow>
#include <QFileDialog>
#include <QSettings>
#include "../gif/gif.h"

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
    void SaveSettings();
    void SaveSldrGroupSettings(QSettings *settings);
    void RestoreSettings();
    void InitSldrGroupSettings(QSettings *settings);

    void SetRotateX(QSettings *settings); //TODO: не нравится нейминг
    void SetRotateY(QSettings *settings);
    void SetRotateZ(QSettings *settings);

    void SetMoveX(QSettings *settings); //TODO: не нравится нейминг
    void SetMoveY(QSettings *settings);
    void SetMoveZ(QSettings *settings);

    void oneGif();
    void createGif();

    const int GifFps = 10, GifLength = 5;
    QTimer *timer;
    int startTime, tmpTime;
    int counter = 1;

};
#endif // WINDOW_H
