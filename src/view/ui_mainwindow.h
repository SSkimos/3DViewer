/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtOpenGLWidgets/QOpenGLWidget>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout_3;
    QPushButton *pushButton;
    QLabel *label;
    QSpacerItem *horizontalSpacer_3;
    QLabel *label_2;
    QVBoxLayout *verticalLayout_5;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_3;
    QSlider *horizontalSlider;
    QLineEdit *lineEdit;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_5;
    QSlider *horizontalSlider_3;
    QLineEdit *lineEdit_3;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_4;
    QSlider *horizontalSlider_2;
    QLineEdit *lineEdit_2;
    QSpacerItem *horizontalSpacer_2;
    QLabel *label_6;
    QVBoxLayout *verticalLayout_6;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_7;
    QSlider *horizontalSlider_4;
    QLineEdit *lineEdit_4;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_8;
    QSlider *horizontalSlider_5;
    QLineEdit *lineEdit_5;
    QHBoxLayout *horizontalLayout_7;
    QLabel *label_9;
    QSlider *horizontalSlider_6;
    QLineEdit *lineEdit_6;
    QSpacerItem *horizontalSpacer;
    QLabel *label_10;
    QHBoxLayout *horizontalLayout_8;
    QSlider *horizontalSlider_7;
    QLineEdit *lineEdit_7;
    QSpacerItem *horizontalSpacer_4;
    QLabel *label_12;
    QHBoxLayout *horizontalLayout_9;
    QRadioButton *radioButton;
    QRadioButton *radioButton_2;
    QSpacerItem *horizontalSpacer_6;
    QHBoxLayout *horizontalLayout_12;
    QLabel *label_11;
    QLabel *label_13;
    QHBoxLayout *horizontalLayout_13;
    QVBoxLayout *verticalLayout;
    QRadioButton *radioButton_3;
    QRadioButton *radioButton_4;
    QRadioButton *radioButton_5;
    QHBoxLayout *horizontalLayout_14;
    QRadioButton *radioButton_7;
    QRadioButton *radioButton_6;
    QHBoxLayout *horizontalLayout_15;
    QVBoxLayout *verticalLayout_8;
    QHBoxLayout *horizontalLayout_11;
    QSlider *horizontalSlider_9;
    QPushButton *pushButton_3;
    QVBoxLayout *verticalLayout_7;
    QSlider *horizontalSlider_8;
    QPushButton *pushButton_2;
    QHBoxLayout *horizontalLayout_10;
    QSpacerItem *horizontalSpacer_5;
    QLabel *label_14;
    QPushButton *pushButton_4;
    QOpenGLWidget *openGLWidget;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1773, 1374);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName("gridLayout");
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        verticalLayout_3 = new QVBoxLayout();
#ifndef Q_OS_MAC
        verticalLayout_3->setSpacing(-1);
#endif
        verticalLayout_3->setObjectName("verticalLayout_3");
        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName("pushButton");
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(pushButton->sizePolicy().hasHeightForWidth());
        pushButton->setSizePolicy(sizePolicy);
        pushButton->setMinimumSize(QSize(400, 50));

        verticalLayout_3->addWidget(pushButton);

        label = new QLabel(centralwidget);
        label->setObjectName("label");
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);
        label->setMinimumSize(QSize(400, 25));
        QFont font;
        font.setPointSize(13);
        label->setFont(font);
        label->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        verticalLayout_3->addWidget(label);

        horizontalSpacer_3 = new QSpacerItem(400, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);

        verticalLayout_3->addItem(horizontalSpacer_3);

        label_2 = new QLabel(centralwidget);
        label_2->setObjectName("label_2");
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy1);
        label_2->setMinimumSize(QSize(400, 50));
        QFont font1;
        font1.setPointSize(25);
        label_2->setFont(font1);
        label_2->setAlignment(Qt::AlignCenter);

        verticalLayout_3->addWidget(label_2);

        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setObjectName("verticalLayout_5");
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName("label_3");
        sizePolicy.setHeightForWidth(label_3->sizePolicy().hasHeightForWidth());
        label_3->setSizePolicy(sizePolicy);
        label_3->setMinimumSize(QSize(50, 0));
        QFont font2;
        font2.setPointSize(18);
        label_3->setFont(font2);

        horizontalLayout_2->addWidget(label_3);

        horizontalSlider = new QSlider(centralwidget);
        horizontalSlider->setObjectName("horizontalSlider");
        sizePolicy.setHeightForWidth(horizontalSlider->sizePolicy().hasHeightForWidth());
        horizontalSlider->setSizePolicy(sizePolicy);
        horizontalSlider->setMinimumSize(QSize(200, 0));
        horizontalSlider->setOrientation(Qt::Horizontal);

        horizontalLayout_2->addWidget(horizontalSlider);

        lineEdit = new QLineEdit(centralwidget);
        lineEdit->setObjectName("lineEdit");
        sizePolicy.setHeightForWidth(lineEdit->sizePolicy().hasHeightForWidth());
        lineEdit->setSizePolicy(sizePolicy);
        lineEdit->setMinimumSize(QSize(150, 25));

        horizontalLayout_2->addWidget(lineEdit);


        verticalLayout_5->addLayout(horizontalLayout_2);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        label_5 = new QLabel(centralwidget);
        label_5->setObjectName("label_5");
        sizePolicy.setHeightForWidth(label_5->sizePolicy().hasHeightForWidth());
        label_5->setSizePolicy(sizePolicy);
        label_5->setMinimumSize(QSize(50, 0));
        label_5->setFont(font2);

        horizontalLayout_4->addWidget(label_5);

        horizontalSlider_3 = new QSlider(centralwidget);
        horizontalSlider_3->setObjectName("horizontalSlider_3");
        sizePolicy.setHeightForWidth(horizontalSlider_3->sizePolicy().hasHeightForWidth());
        horizontalSlider_3->setSizePolicy(sizePolicy);
        horizontalSlider_3->setMinimumSize(QSize(200, 0));
        horizontalSlider_3->setOrientation(Qt::Horizontal);

        horizontalLayout_4->addWidget(horizontalSlider_3);

        lineEdit_3 = new QLineEdit(centralwidget);
        lineEdit_3->setObjectName("lineEdit_3");
        sizePolicy.setHeightForWidth(lineEdit_3->sizePolicy().hasHeightForWidth());
        lineEdit_3->setSizePolicy(sizePolicy);
        lineEdit_3->setMinimumSize(QSize(150, 25));

        horizontalLayout_4->addWidget(lineEdit_3);


        verticalLayout_5->addLayout(horizontalLayout_4);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        label_4 = new QLabel(centralwidget);
        label_4->setObjectName("label_4");
        sizePolicy.setHeightForWidth(label_4->sizePolicy().hasHeightForWidth());
        label_4->setSizePolicy(sizePolicy);
        label_4->setMinimumSize(QSize(50, 0));
        label_4->setFont(font2);

        horizontalLayout_3->addWidget(label_4);

        horizontalSlider_2 = new QSlider(centralwidget);
        horizontalSlider_2->setObjectName("horizontalSlider_2");
        sizePolicy.setHeightForWidth(horizontalSlider_2->sizePolicy().hasHeightForWidth());
        horizontalSlider_2->setSizePolicy(sizePolicy);
        horizontalSlider_2->setMinimumSize(QSize(200, 0));
        horizontalSlider_2->setOrientation(Qt::Horizontal);

        horizontalLayout_3->addWidget(horizontalSlider_2);

        lineEdit_2 = new QLineEdit(centralwidget);
        lineEdit_2->setObjectName("lineEdit_2");
        sizePolicy.setHeightForWidth(lineEdit_2->sizePolicy().hasHeightForWidth());
        lineEdit_2->setSizePolicy(sizePolicy);
        lineEdit_2->setMinimumSize(QSize(150, 25));

        horizontalLayout_3->addWidget(lineEdit_2);


        verticalLayout_5->addLayout(horizontalLayout_3);


        verticalLayout_3->addLayout(verticalLayout_5);

        horizontalSpacer_2 = new QSpacerItem(400, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);

        verticalLayout_3->addItem(horizontalSpacer_2);

        label_6 = new QLabel(centralwidget);
        label_6->setObjectName("label_6");
        sizePolicy1.setHeightForWidth(label_6->sizePolicy().hasHeightForWidth());
        label_6->setSizePolicy(sizePolicy1);
        label_6->setMinimumSize(QSize(400, 50));
        label_6->setFont(font1);
        label_6->setAlignment(Qt::AlignCenter);

        verticalLayout_3->addWidget(label_6);

        verticalLayout_6 = new QVBoxLayout();
        verticalLayout_6->setObjectName("verticalLayout_6");
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        label_7 = new QLabel(centralwidget);
        label_7->setObjectName("label_7");
        sizePolicy.setHeightForWidth(label_7->sizePolicy().hasHeightForWidth());
        label_7->setSizePolicy(sizePolicy);
        label_7->setMinimumSize(QSize(50, 0));
        label_7->setFont(font2);

        horizontalLayout_5->addWidget(label_7);

        horizontalSlider_4 = new QSlider(centralwidget);
        horizontalSlider_4->setObjectName("horizontalSlider_4");
        sizePolicy.setHeightForWidth(horizontalSlider_4->sizePolicy().hasHeightForWidth());
        horizontalSlider_4->setSizePolicy(sizePolicy);
        horizontalSlider_4->setMinimumSize(QSize(200, 0));
        horizontalSlider_4->setOrientation(Qt::Horizontal);

        horizontalLayout_5->addWidget(horizontalSlider_4);

        lineEdit_4 = new QLineEdit(centralwidget);
        lineEdit_4->setObjectName("lineEdit_4");
        sizePolicy.setHeightForWidth(lineEdit_4->sizePolicy().hasHeightForWidth());
        lineEdit_4->setSizePolicy(sizePolicy);
        lineEdit_4->setMinimumSize(QSize(150, 25));

        horizontalLayout_5->addWidget(lineEdit_4);


        verticalLayout_6->addLayout(horizontalLayout_5);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName("horizontalLayout_6");
        label_8 = new QLabel(centralwidget);
        label_8->setObjectName("label_8");
        sizePolicy.setHeightForWidth(label_8->sizePolicy().hasHeightForWidth());
        label_8->setSizePolicy(sizePolicy);
        label_8->setMinimumSize(QSize(50, 0));
        label_8->setFont(font2);

        horizontalLayout_6->addWidget(label_8);

        horizontalSlider_5 = new QSlider(centralwidget);
        horizontalSlider_5->setObjectName("horizontalSlider_5");
        sizePolicy.setHeightForWidth(horizontalSlider_5->sizePolicy().hasHeightForWidth());
        horizontalSlider_5->setSizePolicy(sizePolicy);
        horizontalSlider_5->setMinimumSize(QSize(200, 0));
        horizontalSlider_5->setOrientation(Qt::Horizontal);

        horizontalLayout_6->addWidget(horizontalSlider_5);

        lineEdit_5 = new QLineEdit(centralwidget);
        lineEdit_5->setObjectName("lineEdit_5");
        sizePolicy.setHeightForWidth(lineEdit_5->sizePolicy().hasHeightForWidth());
        lineEdit_5->setSizePolicy(sizePolicy);
        lineEdit_5->setMinimumSize(QSize(150, 25));

        horizontalLayout_6->addWidget(lineEdit_5);


        verticalLayout_6->addLayout(horizontalLayout_6);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName("horizontalLayout_7");
        label_9 = new QLabel(centralwidget);
        label_9->setObjectName("label_9");
        sizePolicy.setHeightForWidth(label_9->sizePolicy().hasHeightForWidth());
        label_9->setSizePolicy(sizePolicy);
        label_9->setMinimumSize(QSize(50, 0));
        label_9->setFont(font2);

        horizontalLayout_7->addWidget(label_9);

        horizontalSlider_6 = new QSlider(centralwidget);
        horizontalSlider_6->setObjectName("horizontalSlider_6");
        sizePolicy.setHeightForWidth(horizontalSlider_6->sizePolicy().hasHeightForWidth());
        horizontalSlider_6->setSizePolicy(sizePolicy);
        horizontalSlider_6->setMinimumSize(QSize(200, 0));
        horizontalSlider_6->setOrientation(Qt::Horizontal);

        horizontalLayout_7->addWidget(horizontalSlider_6);

        lineEdit_6 = new QLineEdit(centralwidget);
        lineEdit_6->setObjectName("lineEdit_6");
        sizePolicy.setHeightForWidth(lineEdit_6->sizePolicy().hasHeightForWidth());
        lineEdit_6->setSizePolicy(sizePolicy);
        lineEdit_6->setMinimumSize(QSize(150, 25));

        horizontalLayout_7->addWidget(lineEdit_6);


        verticalLayout_6->addLayout(horizontalLayout_7);


        verticalLayout_3->addLayout(verticalLayout_6);

        horizontalSpacer = new QSpacerItem(400, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);

        verticalLayout_3->addItem(horizontalSpacer);

        label_10 = new QLabel(centralwidget);
        label_10->setObjectName("label_10");
        sizePolicy1.setHeightForWidth(label_10->sizePolicy().hasHeightForWidth());
        label_10->setSizePolicy(sizePolicy1);
        label_10->setMinimumSize(QSize(400, 50));
        label_10->setFont(font1);
        label_10->setAlignment(Qt::AlignCenter);

        verticalLayout_3->addWidget(label_10);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName("horizontalLayout_8");
        horizontalSlider_7 = new QSlider(centralwidget);
        horizontalSlider_7->setObjectName("horizontalSlider_7");
        sizePolicy.setHeightForWidth(horizontalSlider_7->sizePolicy().hasHeightForWidth());
        horizontalSlider_7->setSizePolicy(sizePolicy);
        horizontalSlider_7->setMinimumSize(QSize(200, 0));
        horizontalSlider_7->setOrientation(Qt::Horizontal);

        horizontalLayout_8->addWidget(horizontalSlider_7);

        lineEdit_7 = new QLineEdit(centralwidget);
        lineEdit_7->setObjectName("lineEdit_7");
        sizePolicy.setHeightForWidth(lineEdit_7->sizePolicy().hasHeightForWidth());
        lineEdit_7->setSizePolicy(sizePolicy);
        lineEdit_7->setMinimumSize(QSize(200, 25));

        horizontalLayout_8->addWidget(lineEdit_7);


        verticalLayout_3->addLayout(horizontalLayout_8);

        horizontalSpacer_4 = new QSpacerItem(400, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);

        verticalLayout_3->addItem(horizontalSpacer_4);

        label_12 = new QLabel(centralwidget);
        label_12->setObjectName("label_12");
        sizePolicy1.setHeightForWidth(label_12->sizePolicy().hasHeightForWidth());
        label_12->setSizePolicy(sizePolicy1);
        label_12->setMinimumSize(QSize(400, 50));
        label_12->setFont(font1);
        label_12->setAlignment(Qt::AlignCenter);

        verticalLayout_3->addWidget(label_12);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName("horizontalLayout_9");
        radioButton = new QRadioButton(centralwidget);
        radioButton->setObjectName("radioButton");
        sizePolicy.setHeightForWidth(radioButton->sizePolicy().hasHeightForWidth());
        radioButton->setSizePolicy(sizePolicy);
        radioButton->setMinimumSize(QSize(200, 0));
        radioButton->setFont(font2);

        horizontalLayout_9->addWidget(radioButton);

        radioButton_2 = new QRadioButton(centralwidget);
        radioButton_2->setObjectName("radioButton_2");
        sizePolicy.setHeightForWidth(radioButton_2->sizePolicy().hasHeightForWidth());
        radioButton_2->setSizePolicy(sizePolicy);
        radioButton_2->setMinimumSize(QSize(200, 0));
        radioButton_2->setFont(font2);

        horizontalLayout_9->addWidget(radioButton_2);


        verticalLayout_3->addLayout(horizontalLayout_9);

        horizontalSpacer_6 = new QSpacerItem(400, 50, QSizePolicy::Expanding, QSizePolicy::Minimum);

        verticalLayout_3->addItem(horizontalSpacer_6);

        horizontalLayout_12 = new QHBoxLayout();
        horizontalLayout_12->setObjectName("horizontalLayout_12");
        label_11 = new QLabel(centralwidget);
        label_11->setObjectName("label_11");
        sizePolicy.setHeightForWidth(label_11->sizePolicy().hasHeightForWidth());
        label_11->setSizePolicy(sizePolicy);
        label_11->setMinimumSize(QSize(200, 50));
        QFont font3;
        font3.setPointSize(20);
        label_11->setFont(font3);
        label_11->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout_12->addWidget(label_11);

        label_13 = new QLabel(centralwidget);
        label_13->setObjectName("label_13");
        sizePolicy.setHeightForWidth(label_13->sizePolicy().hasHeightForWidth());
        label_13->setSizePolicy(sizePolicy);
        label_13->setMinimumSize(QSize(200, 50));
        label_13->setFont(font3);
        label_13->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout_12->addWidget(label_13);


        verticalLayout_3->addLayout(horizontalLayout_12);

        horizontalLayout_13 = new QHBoxLayout();
        horizontalLayout_13->setObjectName("horizontalLayout_13");
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        radioButton_3 = new QRadioButton(centralwidget);
        radioButton_3->setObjectName("radioButton_3");
        sizePolicy.setHeightForWidth(radioButton_3->sizePolicy().hasHeightForWidth());
        radioButton_3->setSizePolicy(sizePolicy);
        radioButton_3->setMinimumSize(QSize(200, 0));
        QFont font4;
        font4.setPointSize(15);
        radioButton_3->setFont(font4);

        verticalLayout->addWidget(radioButton_3);

        radioButton_4 = new QRadioButton(centralwidget);
        radioButton_4->setObjectName("radioButton_4");
        sizePolicy.setHeightForWidth(radioButton_4->sizePolicy().hasHeightForWidth());
        radioButton_4->setSizePolicy(sizePolicy);
        radioButton_4->setMinimumSize(QSize(200, 0));
        radioButton_4->setFont(font4);

        verticalLayout->addWidget(radioButton_4);

        radioButton_5 = new QRadioButton(centralwidget);
        radioButton_5->setObjectName("radioButton_5");
        sizePolicy.setHeightForWidth(radioButton_5->sizePolicy().hasHeightForWidth());
        radioButton_5->setSizePolicy(sizePolicy);
        radioButton_5->setMinimumSize(QSize(200, 0));
        radioButton_5->setFont(font4);

        verticalLayout->addWidget(radioButton_5);


        horizontalLayout_13->addLayout(verticalLayout);

        horizontalLayout_14 = new QHBoxLayout();
        horizontalLayout_14->setObjectName("horizontalLayout_14");
        radioButton_7 = new QRadioButton(centralwidget);
        radioButton_7->setObjectName("radioButton_7");
        sizePolicy.setHeightForWidth(radioButton_7->sizePolicy().hasHeightForWidth());
        radioButton_7->setSizePolicy(sizePolicy);
        radioButton_7->setMinimumSize(QSize(100, 0));
        radioButton_7->setFont(font4);

        horizontalLayout_14->addWidget(radioButton_7);

        radioButton_6 = new QRadioButton(centralwidget);
        radioButton_6->setObjectName("radioButton_6");
        sizePolicy.setHeightForWidth(radioButton_6->sizePolicy().hasHeightForWidth());
        radioButton_6->setSizePolicy(sizePolicy);
        radioButton_6->setMinimumSize(QSize(100, 0));
        radioButton_6->setFont(font4);

        horizontalLayout_14->addWidget(radioButton_6);


        horizontalLayout_13->addLayout(horizontalLayout_14);


        verticalLayout_3->addLayout(horizontalLayout_13);

        horizontalLayout_15 = new QHBoxLayout();
        horizontalLayout_15->setObjectName("horizontalLayout_15");
        verticalLayout_8 = new QVBoxLayout();
        verticalLayout_8->setObjectName("verticalLayout_8");
        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setObjectName("horizontalLayout_11");

        verticalLayout_8->addLayout(horizontalLayout_11);

        horizontalSlider_9 = new QSlider(centralwidget);
        horizontalSlider_9->setObjectName("horizontalSlider_9");
        sizePolicy.setHeightForWidth(horizontalSlider_9->sizePolicy().hasHeightForWidth());
        horizontalSlider_9->setSizePolicy(sizePolicy);
        horizontalSlider_9->setMinimumSize(QSize(200, 0));
        horizontalSlider_9->setOrientation(Qt::Horizontal);

        verticalLayout_8->addWidget(horizontalSlider_9);

        pushButton_3 = new QPushButton(centralwidget);
        pushButton_3->setObjectName("pushButton_3");
        sizePolicy.setHeightForWidth(pushButton_3->sizePolicy().hasHeightForWidth());
        pushButton_3->setSizePolicy(sizePolicy);
        pushButton_3->setMinimumSize(QSize(200, 0));
        pushButton_3->setFont(font2);

        verticalLayout_8->addWidget(pushButton_3);


        horizontalLayout_15->addLayout(verticalLayout_8);

        verticalLayout_7 = new QVBoxLayout();
        verticalLayout_7->setObjectName("verticalLayout_7");
        horizontalSlider_8 = new QSlider(centralwidget);
        horizontalSlider_8->setObjectName("horizontalSlider_8");
        sizePolicy.setHeightForWidth(horizontalSlider_8->sizePolicy().hasHeightForWidth());
        horizontalSlider_8->setSizePolicy(sizePolicy);
        horizontalSlider_8->setMinimumSize(QSize(200, 0));
        horizontalSlider_8->setOrientation(Qt::Horizontal);

        verticalLayout_7->addWidget(horizontalSlider_8);

        pushButton_2 = new QPushButton(centralwidget);
        pushButton_2->setObjectName("pushButton_2");
        sizePolicy.setHeightForWidth(pushButton_2->sizePolicy().hasHeightForWidth());
        pushButton_2->setSizePolicy(sizePolicy);
        pushButton_2->setMinimumSize(QSize(200, 0));
        pushButton_2->setFont(font2);

        verticalLayout_7->addWidget(pushButton_2);


        horizontalLayout_15->addLayout(verticalLayout_7);


        verticalLayout_3->addLayout(horizontalLayout_15);

        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setObjectName("horizontalLayout_10");

        verticalLayout_3->addLayout(horizontalLayout_10);

        horizontalSpacer_5 = new QSpacerItem(400, 50, QSizePolicy::Expanding, QSizePolicy::Minimum);

        verticalLayout_3->addItem(horizontalSpacer_5);

        label_14 = new QLabel(centralwidget);
        label_14->setObjectName("label_14");
        sizePolicy1.setHeightForWidth(label_14->sizePolicy().hasHeightForWidth());
        label_14->setSizePolicy(sizePolicy1);
        label_14->setMinimumSize(QSize(400, 50));
        label_14->setFont(font1);
        label_14->setAlignment(Qt::AlignCenter);

        verticalLayout_3->addWidget(label_14);

        pushButton_4 = new QPushButton(centralwidget);
        pushButton_4->setObjectName("pushButton_4");
        sizePolicy.setHeightForWidth(pushButton_4->sizePolicy().hasHeightForWidth());
        pushButton_4->setSizePolicy(sizePolicy);
        pushButton_4->setMinimumSize(QSize(400, 50));
        pushButton_4->setFont(font2);

        verticalLayout_3->addWidget(pushButton_4);


        horizontalLayout->addLayout(verticalLayout_3);

        openGLWidget = new QOpenGLWidget(centralwidget);
        openGLWidget->setObjectName("openGLWidget");
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(10);
        sizePolicy2.setVerticalStretch(10);
        sizePolicy2.setHeightForWidth(openGLWidget->sizePolicy().hasHeightForWidth());
        openGLWidget->setSizePolicy(sizePolicy2);
        openGLWidget->setMinimumSize(QSize(1000, 850));
        openGLWidget->setBaseSize(QSize(100, 100));

        horizontalLayout->addWidget(openGLWidget);


        gridLayout->addLayout(horizontalLayout, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        pushButton->setText(QCoreApplication::translate("MainWindow", "\320\236\321\202\320\272\321\200\321\213\321\202\321\214 \321\204\320\260\320\271\320\273", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "./src/app/test.py", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "move", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "X", nullptr));
        lineEdit->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "Z", nullptr));
        lineEdit_3->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "Y", nullptr));
        lineEdit_2->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "rotate", nullptr));
        label_7->setText(QCoreApplication::translate("MainWindow", "X", nullptr));
        lineEdit_4->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
        label_8->setText(QCoreApplication::translate("MainWindow", "Z", nullptr));
        lineEdit_5->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
        label_9->setText(QCoreApplication::translate("MainWindow", "Y", nullptr));
        lineEdit_6->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
        label_10->setText(QCoreApplication::translate("MainWindow", "scale", nullptr));
        lineEdit_7->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
        label_12->setText(QCoreApplication::translate("MainWindow", "projection", nullptr));
        radioButton->setText(QCoreApplication::translate("MainWindow", "Solid", nullptr));
        radioButton_2->setText(QCoreApplication::translate("MainWindow", "Dashed", nullptr));
        label_11->setText(QCoreApplication::translate("MainWindow", "\320\222\320\265\321\200\321\210\320\270\320\275\321\213", nullptr));
        label_13->setText(QCoreApplication::translate("MainWindow", "\320\233\320\270\320\275\320\270\320\270", nullptr));
        radioButton_3->setText(QCoreApplication::translate("MainWindow", "\320\235\320\265\321\202", nullptr));
        radioButton_4->setText(QCoreApplication::translate("MainWindow", "\320\232\321\200\321\203\320\263\320\270", nullptr));
        radioButton_5->setText(QCoreApplication::translate("MainWindow", "\320\232\320\262\320\260\320\264\321\200\320\260\321\202\321\213", nullptr));
        radioButton_7->setText(QCoreApplication::translate("MainWindow", "\320\250\321\202\321\200\320\270\321\205\320\276\320\262\320\276\320\271", nullptr));
        radioButton_6->setText(QCoreApplication::translate("MainWindow", "\320\241\320\277\320\273\320\276\321\210\320\275\320\276\320\271", nullptr));
        pushButton_3->setText(QCoreApplication::translate("MainWindow", "choose colour", nullptr));
        pushButton_2->setText(QCoreApplication::translate("MainWindow", "choose colour", nullptr));
        label_14->setText(QCoreApplication::translate("MainWindow", "background", nullptr));
        pushButton_4->setText(QCoreApplication::translate("MainWindow", "choose colour", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
