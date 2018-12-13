/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_mainwindowClass
{
public:
    QWidget *centralWidget;
    QPushButton *pushButton;
    QPushButton *pushButton_4;
    QLabel *Facelabel;
    QPushButton *open;
    QPushButton *close;
    QFrame *line;
    QSlider *endadj;
    QSlider *shapeadj;
    QLabel *label;
    QLabel *label_2;
    QPushButton *pushButton_5;
    QMenuBar *menuBar;
    QMenu *menuFaceMaker;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *mainwindowClass)
    {
        if (mainwindowClass->objectName().isEmpty())
            mainwindowClass->setObjectName(QStringLiteral("mainwindowClass"));
        mainwindowClass->resize(846, 596);
        centralWidget = new QWidget(mainwindowClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(630, 80, 171, 41));
        QFont font;
        font.setFamily(QStringLiteral("Ink Free"));
        font.setPointSize(13);
        font.setBold(true);
        font.setWeight(75);
        pushButton->setFont(font);
        pushButton->setCursor(QCursor(Qt::OpenHandCursor));
        pushButton_4 = new QPushButton(centralWidget);
        pushButton_4->setObjectName(QStringLiteral("pushButton_4"));
        pushButton_4->setGeometry(QRect(630, 450, 171, 41));
        pushButton_4->setFont(font);
        pushButton_4->setCursor(QCursor(Qt::OpenHandCursor));
        Facelabel = new QLabel(centralWidget);
        Facelabel->setObjectName(QStringLiteral("Facelabel"));
        Facelabel->setGeometry(QRect(60, 120, 481, 371));
        QFont font1;
        font1.setFamily(QStringLiteral("Ink Free"));
        font1.setPointSize(15);
        font1.setBold(true);
        font1.setWeight(75);
        Facelabel->setFont(font1);
        Facelabel->setAutoFillBackground(false);
        Facelabel->setWordWrap(false);
        Facelabel->setMargin(0);
        open = new QPushButton(centralWidget);
        open->setObjectName(QStringLiteral("open"));
        open->setGeometry(QRect(130, 30, 131, 41));
        open->setFont(font);
        open->setCursor(QCursor(Qt::OpenHandCursor));
        close = new QPushButton(centralWidget);
        close->setObjectName(QStringLiteral("close"));
        close->setGeometry(QRect(340, 30, 131, 41));
        close->setFont(font);
        close->setCursor(QCursor(Qt::OpenHandCursor));
        line = new QFrame(centralWidget);
        line->setObjectName(QStringLiteral("line"));
        line->setGeometry(QRect(580, 10, 20, 621));
        QFont font2;
        font2.setPointSize(9);
        font2.setBold(false);
        font2.setWeight(50);
        line->setFont(font2);
        line->setFrameShadow(QFrame::Plain);
        line->setLineWidth(3);
        line->setMidLineWidth(0);
        line->setFrameShape(QFrame::VLine);
        endadj = new QSlider(centralWidget);
        endadj->setObjectName(QStringLiteral("endadj"));
        endadj->setGeometry(QRect(630, 200, 171, 21));
        endadj->setCursor(QCursor(Qt::ClosedHandCursor));
        endadj->setMinimum(-20);
        endadj->setMaximum(20);
        endadj->setPageStep(10);
        endadj->setValue(0);
        endadj->setOrientation(Qt::Horizontal);
        shapeadj = new QSlider(centralWidget);
        shapeadj->setObjectName(QStringLiteral("shapeadj"));
        shapeadj->setGeometry(QRect(630, 310, 171, 21));
        shapeadj->setCursor(QCursor(Qt::ClosedHandCursor));
        shapeadj->setMinimum(-1);
        shapeadj->setMaximum(1);
        shapeadj->setValue(0);
        shapeadj->setOrientation(Qt::Horizontal);
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(630, 160, 171, 31));
        label->setFont(font);
        label->setFrameShadow(QFrame::Plain);
        label->setLineWidth(1);
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(630, 270, 171, 31));
        label_2->setFont(font);
        label_2->setFrameShadow(QFrame::Plain);
        label_2->setLineWidth(1);
        pushButton_5 = new QPushButton(centralWidget);
        pushButton_5->setObjectName(QStringLiteral("pushButton_5"));
        pushButton_5->setGeometry(QRect(630, 370, 171, 41));
        pushButton_5->setFont(font);
        pushButton_5->setCursor(QCursor(Qt::OpenHandCursor));
        mainwindowClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(mainwindowClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 846, 23));
        menuFaceMaker = new QMenu(menuBar);
        menuFaceMaker->setObjectName(QStringLiteral("menuFaceMaker"));
        mainwindowClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(mainwindowClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        mainwindowClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(mainwindowClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        mainwindowClass->setStatusBar(statusBar);

        menuBar->addAction(menuFaceMaker->menuAction());

        retranslateUi(mainwindowClass);
        QObject::connect(pushButton_4, SIGNAL(clicked()), mainwindowClass, SLOT(button4()));
        QObject::connect(pushButton, SIGNAL(clicked()), mainwindowClass, SLOT(button1()));
        QObject::connect(open, SIGNAL(clicked()), mainwindowClass, SLOT(opencamera()));
        QObject::connect(close, SIGNAL(clicked()), mainwindowClass, SLOT(closecamera()));
        QObject::connect(endadj, SIGNAL(valueChanged(int)), mainwindowClass, SLOT(slider1()));
        QObject::connect(shapeadj, SIGNAL(valueChanged(int)), mainwindowClass, SLOT(slider2()));
        QObject::connect(pushButton_5, SIGNAL(clicked()), mainwindowClass, SLOT(button5()));

        QMetaObject::connectSlotsByName(mainwindowClass);
    } // setupUi

    void retranslateUi(QMainWindow *mainwindowClass)
    {
        mainwindowClass->setWindowTitle(QApplication::translate("mainwindowClass", "mainwindow", Q_NULLPTR));
        pushButton->setText(QApplication::translate("mainwindowClass", "Color Adjustment", Q_NULLPTR));
        pushButton_4->setText(QApplication::translate("mainwindowClass", "Developers Bio", Q_NULLPTR));
        Facelabel->setText(QApplication::translate("mainwindowClass", "                 Your Face Here :)", Q_NULLPTR));
        open->setText(QApplication::translate("mainwindowClass", "Open Camera", Q_NULLPTR));
        close->setText(QApplication::translate("mainwindowClass", "Close Camera", Q_NULLPTR));
        label->setText(QApplication::translate("mainwindowClass", "   End Adjustment", Q_NULLPTR));
        label_2->setText(QApplication::translate("mainwindowClass", "  Shape Adjustment", Q_NULLPTR));
        pushButton_5->setText(QApplication::translate("mainwindowClass", "Back to Origin", Q_NULLPTR));
        menuFaceMaker->setTitle(QApplication::translate("mainwindowClass", "FaceMaker", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class mainwindowClass: public Ui_mainwindowClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
