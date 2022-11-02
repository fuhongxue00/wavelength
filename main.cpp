#include "mainwindow.h"

#include <QApplication>
#include "view.h"
#include "callout.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    View x;


    return a.exec();
}
