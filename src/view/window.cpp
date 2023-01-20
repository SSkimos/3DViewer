#include "window.h"
#include "ui_window.h"
#include "../model/s21_parse_obj.h"

Window::Window(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Window)
{
    ui->setupUi(this);
    ui->widget->filename.clear();
    ui->widget->filename_const = NULL;
    ConnectSliders();
    ConnectLabels();
    // connect(ui->xRotSldr, &QSlider::valueChanged,
    //     [this](const int& val)->void{ui->xRotEdit->setText(locale().toString(val)); ui->widget->rotateX = val; ui->widget->update();});
    // connect(ui->yRotSldr, &QSlider::valueChanged,
    //     [this](const int& val)->void{ui->yRotEdit->setText(locale().toString(val)); ui->widget->rotateY = val; ui->widget->update();});
    // connect(ui->zRotSldr, &QSlider::valueChanged,
    //     [this](const int& val)->void{ui->zRotEdit->setText(locale().toString(val)); ui->widget->rotateZ = val; ui->widget->update();});
    // connect(ui->xMoveSldr, &QSlider::valueChanged,
    //     [this](const int& val)->void{ui->xMoveEdit->setText(locale().toString(val)); ui->widget->moveX = val; ui->widget->update();});
    // connect(ui->yMoveSldr, &QSlider::valueChanged,
    //     [this](const int& val)->void{ui->yMoveEdit->setText(locale().toString(val)); ui->widget->moveY = val; ui->widget->update();});
    // connect(ui->zMoveSldr, &QSlider::valueChanged,
    //     [this](const int& val)->void{ui->zMoveEdit->setText(locale().toString(val)); ui->widget->moveZ = val; ui->widget->update();});
    // connect(ui->scaleSldr, &QSlider::valueChanged,
    //     [this](const int& val)->void{ui->widget->scale_val = val; ui->widget->update();});
    RestoreSettings();
}

Window::~Window()
{
    SaveSettings();
    delete ui;
}

void Window::ScaleChange(int val) {
  ui->widget->scale_val = val;
  ui->widget->update();
}

void Window::ConnectSliders() {
  connect(ui->xMoveSldr, &QSlider::valueChanged, this,  &Window::setMoveX);
  connect(ui->yMoveSldr, &QSlider::valueChanged, this,  &Window::setMoveY);
  connect(ui->zMoveSldr, &QSlider::valueChanged, this,  &Window::setMoveZ);
  connect(ui->xRotSldr, &QSlider::valueChanged,  this,  &Window::setRotateX);
  connect(ui->yRotSldr, &QSlider::valueChanged,  this, &Window::setRotateY);
  connect(ui->zRotSldr, &QSlider::valueChanged,  this, &Window::setRotateZ);
  connect(ui->scaleSldr, &QSlider::valueChanged, this, &Window::ScaleChange);

  connect(ui->xMoveEdit, &QLineEdit::textChanged, this, &Window::xRotateTextEdit);
  // connect(ui->xMoveEdit, SIGNAL(textChanged(const QString &text)), ui->widget, SLOT(xRotateTextEdit()));
}

void Window::setMoveX(int newValue) {
  ui->widget->moveX = newValue;
  ui->widget->update();
}

void Window::setMoveY(int newValue) {
  ui->widget->moveY = newValue;
  ui->widget->update();
}

void Window::setMoveZ(int newValue) {
  ui->widget->moveZ = newValue;
  ui->widget->update();
}

void Window::setRotateX(int newValue) {
  ui->widget->rotateX = newValue;
  ui->widget->update();
}

void Window::setRotateY(int newValue) {
  ui->widget->rotateY = newValue;
  ui->widget->update();
}

void Window::setRotateZ(int newValue) {
  ui->widget->rotateZ = newValue;
  ui->widget->update();
}

void Window::xMoveEdit(double value) {
  ui->xMoveEdit->setText(QString::number(value));
}

void Window::xRotateTextEdit(const QString & val) {
  int value = val.toInt();
  ui->xMoveSldr->setValue(value);
}

void Window::xMoveSldr(double value) {
  ui->xMoveSldr->setValue(value);
}

void Window::ConnectLabels() {
  // connect(ui->xMoveEdit, SIGNAL(valueChanged()), (this), SLOT(xMoveSetText()));
}

void Window::xMoveSetText(double value) {
  ui->xMoveEdit->setText(locale().toString(value));
}

void Window::SaveSettings() {
  QSettings settings("settings.conf", QSettings::IniFormat);
  SaveSldrGroupSettings(&settings);
}

void Window::SaveSldrGroupSettings(QSettings *settings) {
  settings->beginGroup("sldrs");
  settings->setValue("rotateX", ui->xRotSldr->value());
  settings->setValue("rotateY", ui->yRotSldr->value());
  settings->setValue("rotateZ", ui->zRotSldr->value());
  settings->setValue("moveX", ui->xMoveSldr->value());
  settings->setValue("moveY", ui->yMoveSldr->value());
  settings->setValue("moveZ", ui->zMoveSldr->value());
  settings->endGroup();
}

void Window::RestoreSettings() {
  QSettings settings("settings.conf", QSettings::IniFormat);
  InitSldrGroupSettings(&settings);
}

void Window::InitSldrGroupSettings(QSettings *settings) {
  settings->beginGroup("sldrs");
  SetRotateX(settings);
  SetRotateY(settings);
  SetRotateZ(settings);

  SetMoveX(settings);
  SetMoveY(settings);
  SetMoveZ(settings);
  settings->endGroup();
}

void Window::SetRotateX(QSettings *settings) {
  int rotateX = settings->value("rotateX").toInt();
  setRotateX(rotateX);
  ui->xRotSldr->setValue(rotateX);
  ui->xRotEdit->setText(locale().toString(rotateX));
}

void Window::SetRotateY(QSettings *settings) {
  int rotateY = settings->value("rotateY").toInt();
  setRotateY(rotateY);
  ui->yRotSldr->setValue(rotateY);
  ui->yRotEdit->setText(locale().toString(rotateY));
}

void Window::SetRotateZ(QSettings *settings) {
  int rotateZ = settings->value("rotateZ").toInt();
  setRotateZ(rotateZ);
  ui->zRotSldr->setValue(rotateZ);
  ui->zRotEdit->setText(locale().toString(rotateZ));
}

void Window::SetMoveX(QSettings *settings) {
  int moveX = settings->value("moveX").toInt();
  setMoveX(moveX);
  ui->xMoveSldr->setValue(moveX);
  ui->xMoveEdit->setText(locale().toString(moveX));
}

void Window::SetMoveY(QSettings *settings) {
  int moveY = settings->value("moveY").toInt();
  setMoveY(moveY);
  ui->yMoveSldr->setValue(moveY);
  ui->yMoveEdit->setText(locale().toString(moveY));
}

void Window::SetMoveZ(QSettings *settings) {
  int moveZ = settings->value("moveZ").toInt();
  setMoveZ(moveZ);
  ui->zMoveSldr->setValue(moveZ);
  ui->zMoveEdit->setText(locale().toString(moveZ));
}

void Window::on_chooseFileButton_clicked()
{
  QString old_filename = ui->widget->filename;
  ui->widget->filename = QFileDialog::getOpenFileName(
      this, tr("Choose File"),
      "Desktop",
      "Object files (*.obj)"
      );
  if (ui->widget->filename.size() > 0) {
    int size = 256; 
    char* filesave = (char*) calloc(size + 1, sizeof(*filesave));
    int i = 0;
    if (filesave) {
      for (auto c: ui->widget->filename) {
        filesave[i++] = c.toLatin1();
      }
      if (ui->widget->filename_const) free(ui->widget->filename_const);
      ui->widget->filename_const = filesave;
      ui->statusbar->showMessage(ui->widget->filename);
    }
    if (old_filename != ui->widget->filename) {
      ui->widget->file_load = 1;
    }
  }
}

void Window::on_makeGIFButton_clicked() {
  check = 0;
  timer_gif = new QTimer();
  connect(timer_gif, SIGNAL(timeout()), this, SLOT(timer_grab()));
  timer_gif->start(100);
  ui->makeGIFButton->setEnabled(0);
}

void Window::timer_grab() {
  if (check > 49) {
    timer_gif->stop();
    disconnect(timer_gif);
    check = 0;
    for (int i = 0; i < 50; gif.addFrame(mp[i++], 200)) {
    }
    QString str =
      QFileDialog::getSaveFileName(0, "Сохранить файл как", "", "*.gif");
    gif.save(str);
    ui->makeGIFButton->setText("GIF");
    ui->makeGIFButton->setEnabled(1);
  } else {
    mp[check] = ui->widget->grab().toImage();
    check += 1;
    ui->makeGIFButton->setText(QString::number(check / 10));
  }
}

void Window::print_grab() {
  if (check > 49) {
    timer_gif->stop();
    disconnect(timer_gif);
  } else {
    gif.addFrame(mp[check]);
    check += 1;
  }
}
