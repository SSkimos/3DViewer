#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

// connect from sliders to labels
void MainWindow::on_xMove_sldr_valueChanged(int value)
{
    ui->xMove_lbl->setText(QString::number(value));
}
void MainWindow::on_zMove_sldr_valueChanged(int value)
{
    ui->zMove_lbl->setText(QString::number(value));
}
void MainWindow::on_yMove_sldr_valueChanged(int value)
{
    ui->yMove_lbl->setText(QString::number(value));
}
void MainWindow::on_xRotate_sldr_valueChanged(int value)
{
    ui->xRotate_lbl->setText(QString::number(value));
}
void MainWindow::on_zRotate_sldr_valueChanged(int value)
{
    ui->zRotate_lbl->setText(QString::number(value));
}
void MainWindow::on_yRotate_sldr_valueChanged(int value)
{
    ui->yRotate_lbl->setText(QString::number(value));
}

// connect from labels to sliders
void MainWindow::on_xMove_lbl_textChanged(const QString &arg1)
{
    if (arg1.toInt() >= 0 && arg1.toInt() <= 360) {
        ui->xMove_sldr->setValue(arg1.toInt());
    }
}
void MainWindow::on_yMove_lbl_textChanged(const QString &arg1)
{
    if (arg1.toInt() >= 0 && arg1.toInt() <= 360) {
        ui->yMove_sldr->setValue(arg1.toInt());
    }
}
void MainWindow::on_zMove_lbl_textChanged(const QString &arg1)
{
    if (arg1.toInt() >= 0 && arg1.toInt() <= 360) {
        ui->zMove_sldr->setValue(arg1.toInt());
    }
}
void MainWindow::on_xRotate_lbl_textChanged(const QString &arg1)
{
    if (arg1.toInt() >= 0 && arg1.toInt() <= 360) {
        ui->xRotate_sldr->setValue(arg1.toInt());
    }
}
void MainWindow::on_yRotate_lbl_textChanged(const QString &arg1)
{
    if (arg1.toInt() >= 0 && arg1.toInt() <= 360) {
        ui->yRotate_sldr->setValue(arg1.toInt());
    }
}
void MainWindow::on_zRotate_lbl_textChanged(const QString &arg1)
{
    if (arg1.toInt() >= 0 && arg1.toInt() <= 360) {
        ui->zRotate_sldr->setValue(arg1.toInt());
    }
}


// open file
void MainWindow::on_pushButton_clicked()
{
    QString filename = QFileDialog::getOpenFileName(
                this, tr("Choose File"),
                "Desktop",
                "All files (*.*)"
    );
    ui->statusbar->showMessage(filename);
}

// ==================================================
//! [0]
void MainWindow::mousePressEvent(QMouseEvent *e)
{
    // Save mouse press position
    mousePressPosition = QVector2D(e->position());
}

void MainWindow::mouseReleaseEvent(QMouseEvent *e)
{
    // Mouse release position - mouse press position
    QVector2D diff = QVector2D(e->position()) - mousePressPosition;

    // Rotation axis is perpendicular to the mouse position difference
    // vector
    QVector3D n = QVector3D(diff.y(), diff.x(), 0.0).normalized();

    // Accelerate angular speed relative to the length of the mouse sweep
    qreal acc = diff.length() / 100.0;

    // Calculate new rotation axis as weighted sum
    rotationAxis = (rotationAxis * angularSpeed + n * acc).normalized();

    // Increase angular speed
    angularSpeed += acc;
}
//! [0]

//! [1]
void MainWindow::timerEvent(QTimerEvent *)
{
    // Decrease angular speed (friction)
    angularSpeed *= 0.99;

    // Stop rotation when speed goes below threshold
    if (angularSpeed < 0.01) {
        angularSpeed = 0.0;
    } else {
        // Update rotation
        rotation = QQuaternion::fromAxisAndAngle(rotationAxis, angularSpeed) * rotation;

        // Request an update
        update();
    }
}
//! [1]

void MainWindow::initializeGL()
{
    initializeOpenGLFunctions();

    glClearColor(0, 0, 0, 1);

    initShaders();
    initTextures();

//! [2]
    // Enable depth buffer
    glEnable(GL_DEPTH_TEST);

    // Enable back face culling
    glEnable(GL_CULL_FACE);
//! [2]

    geometries = new GeometryEngine;

    // Use QBasicTimer because its faster than QTimer
    timer.start(12, this);
}

//! [3]
void MainWindow::initShaders()
{
    // Compile vertex shader
    if (!program.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/vshader.glsl"))
        close();

    // Compile fragment shader
    if (!program.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/fshader.glsl"))
        close();

    // Link shader pipeline
    if (!program.link())
        close();

    // Bind shader pipeline for use
    if (!program.bind())
        close();
}
//! [3]

//! [4]
void MainWindow::initTextures()
{
    // Load cube.png image
    texture = new QOpenGLTexture(QImage(":/cube.png").mirrored());

    // Set nearest filtering mode for texture minification
    texture->setMinificationFilter(QOpenGLTexture::Nearest);

    // Set bilinear filtering mode for texture magnification
    texture->setMagnificationFilter(QOpenGLTexture::Linear);

    // Wrap texture coordinates by repeating
    // f.ex. texture coordinate (1.1, 1.2) is same as (0.1, 0.2)
    texture->setWrapMode(QOpenGLTexture::Repeat);
}
//! [4]

//! [5]
void MainWindow::resizeGL(int w, int h)
{
    // Calculate aspect ratio
    qreal aspect = qreal(w) / qreal(h ? h : 1);

    // Set near plane to 3.0, far plane to 7.0, field of view 45 degrees
    const qreal zNear = 3.0, zFar = 7.0, fov = 45.0;

    // Reset projection
    projection.setToIdentity();

    // Set perspective projection
    projection.perspective(fov, aspect, zNear, zFar);
}
//! [5]

void MainWindow::paintGL()
{
    // Clear color and depth buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    texture->bind();

//! [6]
    // Calculate model view transformation
    QMatrix4x4 matrix;
    matrix.translate(0.0, 0.0, -5.0);
    matrix.rotate(rotation);

    // Set modelview-projection matrix
    program.setUniformValue("mvp_matrix", projection * matrix);
//! [6]

    // Use texture unit 0 which contains cube.png
    program.setUniformValue("texture", 0);

    // Draw cube geometry
    geometries->drawCubeGeometry(&program);
}

