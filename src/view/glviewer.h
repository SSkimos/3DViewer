#ifndef GLVIEWER_H
#define GLVIEWER_H
#include <QOpenGLWidget>

class GLViewer: public QOpenGLWidget
{
public :
    GLViewer(QWidget *parent) : QOpenGLWidget(parent) { };

protected:
    void initializeGL();
    void paintGL();
    void resizeGL(int width, int height);

};




#endif // GLVIEWER_H
