#include "window.h"
#include "ui_window.h"
#include "../controller/controller.h"

Window::Window(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Window)
{
    ui->setupUi(this);
    controller = new Controller();
}

Window::~Window()
{
    delete ui;
    delete controller;
}


void Window::on_xRotSldr_valueChanged(int value)
{
    controller->updateValue(value);
}

