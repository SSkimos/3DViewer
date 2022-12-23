#include "mainwindow.h"
#include "./ui_mainwindow.h"

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



