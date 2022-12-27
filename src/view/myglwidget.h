#ifndef MYGLWIDGET_H_
#define MYGLWIDGET_H_

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLContext>
#include <QColor>

class MyGLWidget: public QOpenGLWidget, public QOpenGLFunctions
{
    Q_OBJECT
public :
    MyGLWidget(QWidget *parent = nullptr);

protected:
    void initializeGL() override;
    void paintGL() override;
    void resizeGL(int width, int height) override;

private:
    void qColorToRGB(const QColor &c, float &r, float &g, float &b) const;
    float normaliza_0_1(float val, float min, float max) const;
};




#endif // MYGLWIDGET_H_
