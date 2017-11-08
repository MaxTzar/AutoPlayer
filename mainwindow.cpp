#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTimer>
#include <QPixmap>
#include <QColor>
#include <QQuickWidget>
#include <QLayout>
#include <backgroundimage.h>

static int waitMilliSec = 2000;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QQuickWidget *view = new QQuickWidget;
    view->setSource(QUrl::fromLocalFile("myqmlfile.qml"));
    view->show();

    QWidget *widget = ui->widget;
    QLayout *layout = widget->layout();
    layout->addWidget(view);



    GraphManager::Elt* elt1 = new GraphManager::Elt();
    elt1->_name = "elt1";
    elt1->_pattern = QImage("D:/important/factures/tmp/test.png");
    GraphManager::Elt* elt2 = new GraphManager::Elt();
    elt2->_name = "elt2";
    elt2->_pattern = QImage("D:/important/factures/tmp/elt2.png");
    GraphManager::Elt* elt3 = new GraphManager::Elt();
    elt3->_name = "elt3";
    elt3->_pattern = QImage("D:/important/factures/tmp/test3.png");
    GraphManager::Elt* elt4 = new GraphManager::Elt();
    elt4->_name = "elt4";
    elt4->_pattern = QImage("D:/important/factures/tmp/test4.png");
    GraphManager::Elt* elt5 = new GraphManager::Elt();
    elt5->_name = "elt5";
    elt5->_pattern = QImage("D:/important/factures/tmp/test5.png");

    graphMger.addElts(elt1);
    graphMger.addElts(elt2);
    graphMger.addElts(elt3);
    graphMger.addElts(elt4);
    graphMger.addElts(elt5);

    graphMger.connectTo(elt1, elt2);
    graphMger.connectTo(elt1, elt3);
    graphMger.connectTo(elt3, elt4);
    graphMger.connectTo(elt3, elt5);
    graphMger.connectTo(elt2, elt1);
    graphMger.connectTo(elt4, elt1);
    graphMger.connectTo(elt4, elt3);
    graphMger.connectTo(elt5, elt1);
    graphMger.connectTo(elt5, elt3);

    QTimer::singleShot(waitMilliSec,this,&MainWindow::screenShot);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::screenShot()
{
    BackgroundImage bi = m_screenShot.takeScreenshot();
    BackgroundImage::box b;
    QImage image;
    for (GraphManager::Elt* elt : graphMger.getCurrentElt()->_outputElts)
    {
        image = elt->_pattern;
        b = bi.findSampleImage(image,100);
        if(b.isValid())
        {
            graphMger.setCurrentElt(elt);
            break;
        }
    }


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

    ui->pattern->setPixmap(QPixmap::fromImage(image));
    ui->image->setPixmap(QPixmap::fromImage(bi).scaled(bi.width()/2,bi.height()/2));
    QTimer::singleShot(waitMilliSec,this,&MainWindow::screenShot);
}
