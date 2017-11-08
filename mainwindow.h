#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <screenshot.h>
#include <backgroundimage.h>
#include <graphmanager.h>
#include <QImage>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public Q_SLOTS:
    void screenShot();

private:
    Ui::MainWindow *ui;
    Screenshot m_screenShot;
    QImage image;
    GraphManager graphMger;
};

#endif // MAINWINDOW_H
