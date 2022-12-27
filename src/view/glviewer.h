#ifndef GLVIEWER_H
#define GLVIEWER_H
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLContext>

class GLViewer: public QOpenGLWidget, public QOpenGLFunctions
{
    Q_OBJECT
public :
    GLViewer(QWidget *parent) : QOpenGLWidget(parent) { };

protected:
    void initializeGL() override;
    void paintGL() override ;
    void resizeGL(int width, int height) override;

};




#endif // GLVIEWER_H
