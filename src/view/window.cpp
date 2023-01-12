#include "window.h"
#include "ui_window.h"

Window::Window(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Window)
{
    ui->setupUi(this);
    connect(ui->xRotSldr, &QSlider::valueChanged,
        [this](const int& val)->void{ui->xRotEdit->setText(locale().toString(val)); ui->widget->rotateX = val; ui->widget->update();});
    connect(ui->yRotSldr, &QSlider::valueChanged,
        [this](const int& val)->void{ui->yRotEdit->setText(locale().toString(val)); ui->widget->rotateY = val; ui->widget->update();});
    connect(ui->zRotSldr, &QSlider::valueChanged,
        [this](const int& val)->void{ui->zRotEdit->setText(locale().toString(val)); ui->widget->rotateZ = val; ui->widget->update();});
    connect(ui->xMoveSldr, &QSlider::valueChanged,
        [this](const int& val)->void{ui->xMoveEdit->setText(locale().toString(val)); ui->widget->moveX = val; ui->widget->update();});
    connect(ui->yMoveSldr, &QSlider::valueChanged,
        [this](const int& val)->void{ui->yMoveEdit->setText(locale().toString(val)); ui->widget->moveY = val; ui->widget->update();});
    connect(ui->zMoveSldr, &QSlider::valueChanged,
        [this](const int& val)->void{ui->zMoveEdit->setText(locale().toString(val)); ui->widget->moveZ = val; ui->widget->update();});
}

void Window::on_chooseFileButton_clicked()
{
    ui->widget->filename = QFileDialog::getOpenFileName(
                this, tr("Choose File"),
                "Desktop",
                "All files (*.*)"
    );
    if (ui->widget->filename.size() > 0) ui->statusbar->showMessage(ui->widget->filename);
}

Window::~Window()
{
    delete ui;
}
