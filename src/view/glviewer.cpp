#include "glviewer.h"

void GLViewer::initializeGL(void) {
    QOpenGLFunctions *f = QOpenGLContext::currentContext()->functions();
    f->glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
}
void GLViewer::paintGL(void) {
    QOpenGLFunctions *f = QOpenGLContext::currentContext()->functions();
   // f->glClear(GL_COLOR_BUFFER_BIT);
}
void GLViewer:: resizeGL(int width, int height) {
    //m_projection.setToIdentity();
   // m_projection.perspective(45.0f, width / float(height), 0.01f, 100.0f);

}



