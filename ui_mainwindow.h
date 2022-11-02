/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QWidget>
#include "qchartview.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QTabWidget *tabWidget;
    QWidget *tab_2;
    QChartView *waveGraphicsView_2;
    QPushButton *readDataButton;
    QPushButton *readDataButton_2;
    QChartView *waveGraphicsView;
    QPushButton *pushButton;
    QWidget *tab;
    QScrollArea *myarea;
    QWidget *area;
    QPushButton *btn_print;
    QPushButton *printdata;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1800, 900);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setGeometry(QRect(10, 10, 1700, 850));
        tabWidget->setTabShape(QTabWidget::Triangular);
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        waveGraphicsView_2 = new QChartView(tab_2);
        waveGraphicsView_2->setObjectName(QString::fromUtf8("waveGraphicsView_2"));
        waveGraphicsView_2->setGeometry(QRect(10, 450, 1500, 300));
        readDataButton = new QPushButton(tab_2);
        readDataButton->setObjectName(QString::fromUtf8("readDataButton"));
        readDataButton->setGeometry(QRect(1550, 200, 93, 29));
        readDataButton_2 = new QPushButton(tab_2);
        readDataButton_2->setObjectName(QString::fromUtf8("readDataButton_2"));
        readDataButton_2->setGeometry(QRect(1550, 600, 93, 29));
        waveGraphicsView = new QChartView(tab_2);
        waveGraphicsView->setObjectName(QString::fromUtf8("waveGraphicsView"));
        waveGraphicsView->setGeometry(QRect(10, 50, 1500, 300));
        pushButton = new QPushButton(tab_2);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(1550, 750, 111, 41));
        tabWidget->addTab(tab_2, QString());
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        myarea = new QScrollArea(tab);
        myarea->setObjectName(QString::fromUtf8("myarea"));
        myarea->setGeometry(QRect(10, 20, 1600, 700));
        myarea->setWidgetResizable(true);
        area = new QWidget();
        area->setObjectName(QString::fromUtf8("area"));
        area->setGeometry(QRect(0, 0, 1598, 698));
        myarea->setWidget(area);
        btn_print = new QPushButton(tab);
        btn_print->setObjectName(QString::fromUtf8("btn_print"));
        btn_print->setGeometry(QRect(740, 750, 93, 29));
        printdata = new QPushButton(tab);
        printdata->setObjectName(QString::fromUtf8("printdata"));
        printdata->setGeometry(QRect(850, 750, 93, 29));
        tabWidget->addTab(tab, QString());
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1800, 25));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        readDataButton->setText(QCoreApplication::translate("MainWindow", "\345\212\240\350\275\275\346\226\207\344\273\266", nullptr));
        readDataButton_2->setText(QCoreApplication::translate("MainWindow", "\345\212\240\350\275\275\346\226\207\344\273\266", nullptr));
        pushButton->setText(QCoreApplication::translate("MainWindow", "\345\217\215\345\260\204\347\216\207\350\256\241\347\256\227", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QCoreApplication::translate("MainWindow", "\346\240\207\345\256\232/\346\265\213\351\207\217\346\225\260\346\215\256", nullptr));
        btn_print->setText(QCoreApplication::translate("MainWindow", "\346\211\223\345\215\260\347\252\227\345\217\243", nullptr));
        printdata->setText(QCoreApplication::translate("MainWindow", "\346\211\223\345\215\260\346\225\260\346\215\256", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QCoreApplication::translate("MainWindow", "\345\217\215\345\260\204\347\216\207\346\265\213\351\207\217", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
