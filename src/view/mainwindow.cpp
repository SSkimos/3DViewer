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

