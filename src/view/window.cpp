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
    connect(ui->scaleSldr, &QSlider::valueChanged,
        [this](const int& val)->void{ui->widget->scale_val = val; ui->widget->update();});
    RestoreSettings();
}

Window::~Window()
{
    SaveSettings();
    delete ui;
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
    ui->xRotSldr->setValue(rotateX);
    ui->xRotEdit->setText(locale().toString(rotateX));
}

void Window::SetRotateY(QSettings *settings) {
    int rotateY = settings->value("rotateY").toInt();
    ui->yRotSldr->setValue(rotateY);
    ui->yRotEdit->setText(locale().toString(rotateY));
}

void Window::SetRotateZ(QSettings *settings) {
    int rotateZ = settings->value("rotateZ").toInt();
    ui->zRotSldr->setValue(rotateZ);
    ui->zRotEdit->setText(locale().toString(rotateZ));
}

void Window::SetMoveX(QSettings *settings) {
    int moveX = settings->value("moveX").toInt();
    ui->xMoveSldr->setValue(moveX);
    ui->xMoveEdit->setText(locale().toString(moveX));
}

void Window::SetMoveY(QSettings *settings) {
    int moveY = settings->value("moveY").toInt();
    ui->yMoveSldr->setValue(moveY);
    ui->yMoveEdit->setText(locale().toString(moveY));
}

void Window::SetMoveZ(QSettings *settings) {
    int moveZ = settings->value("moveZ").toInt();
    ui->zMoveSldr->setValue(moveZ);
    ui->zMoveEdit->setText(locale().toString(moveZ));
}

void Window::on_chooseFileButton_clicked()
{
    QString old_filename = ui->widget->filename;
    ui->widget->filename = QFileDialog::getOpenFileName(
        this, tr("Choose File"),
        "Desktop",
        "All files (*.*)"
        );
    if (ui->widget->filename.size() > 0) {
      ui->statusbar->showMessage(ui->widget->filename);
      if (old_filename != ui->widget->filename) {
        ui->widget->file_load = 1;
      }
    }
}

void Window::oneGif() {
  if (startTime == tmpTime) {
    ui->widget->grab().scaled(640, 480, Qt::IgnoreAspectRatio).save(QDir::homePath() + "/screenshots/gif_obj/" + QString::number(counter) +".bmp");
    counter++;
    tmpTime += 1000 / GifFps;
  }
  if (startTime == 1000 * GifLength) {
    createGif();
    timer->stop();
    counter = 1;
  }
  startTime += 1000 / GifFps;
}

void Window::createGif() {
  QDir pathFile;
  QDateTime dateTime = dateTime.currentDateTime();
  QString currentDateTime = dateTime.toString("yyyy_MM_dd_HHmmss_zzz");
  QString gif_name = QDir::homePath() + "/screenshots/" + currentDateTime + ".gif";
  QByteArray ga = gif_name.toLocal8Bit();
  GifWriter writer = {};
  int err = 0;

  if (GifBegin(&writer, ga.data(), 640, 480, 10, 8, false)) {
    for (int i = 1; i <= 50; i++) {
      if (err == 1) {
        break;
      }
      QImage img(QDir::homePath() + "/screenshots/gif_obj/" + QString::number(i) +
                 ".bmp");
      if (!img.isNull()) {
        if (GifWriteFrame(&writer,
                          img.convertToFormat(QImage::Format_Indexed8)
                              .convertToFormat(QImage::Format_RGBA8888)
                              .constBits(),
                          640, 480, 10, 8, false)) {
        } else {
          QMessageBox::critical(0, "Error", "Gif file can not be created...");
          err = 1;
        }
      } else {
        QMessageBox::critical(0, "Error", "Gif file can not be created...");
        err = 1;
      }
    }
    if (err == 0) {
      GifEnd(&writer);
    }
  } else {
    err = 1;
    QMessageBox::critical(0, "Error", "Gif file can not be created...");
  }

  if (err == 1) {
    if (QFile::exists(gif_name)) {
      QFile::remove(gif_name);
    }
  }

  pathFile.setPath(QDir::homePath() + "/screenshots/gif_obj/");
  pathFile.removeRecursively();
  ui->makeGIFButton->setEnabled(true);
}
