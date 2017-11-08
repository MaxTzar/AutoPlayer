#include "mainwindow.h"
#include "mainwindow2.h"
#include <QApplication>
#include <backgroundimage.h>
#include <screenshot.h>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow2 w;
    w.show();

    return a.exec();
}
