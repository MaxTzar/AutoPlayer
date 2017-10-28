#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTimer>
#include <QPixmap>
#include <QColor>
#include <backgroundimage.h>

static int waitMilliSec = 2000;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QTimer::singleShot(waitMilliSec,this,&MainWindow::screenShot);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::screenShot()
{
    BackgroundImage bi = m_screenShot.takeScreenshot();

    QImage image("D:/important/factures/tmp/test.png");

    BackgroundImage::box b = bi.findSampleImage(image,10);

    if (b.isValid())
    {
        for(int i = b._xmin; i < b._xmax; ++i)
        {
            for(int j = 0; j < 2; ++j)
            {
                bi.setPixelColor(QPoint(b._ymin + j, i), Qt::red);
                bi.setPixelColor(QPoint(b._ymax - j, i), Qt::red);
            }
        }


        for(int i = b._ymin; i < b._ymax; ++i)
        {
            for(int j = 0; j < 2; ++j)
            {
                bi.setPixelColor(QPoint(i, b._xmin + j), Qt::red);
                bi.setPixelColor(QPoint(i, b._xmax - j), Qt::red);
            }
        }
    }

    ui->image->setPixmap(QPixmap::fromImage(bi).scaled(bi.width()/2,bi.height()/2));
    QTimer::singleShot(waitMilliSec,this,&MainWindow::screenShot);
}
