#ifndef MAINWINDOW2_H
#define MAINWINDOW2_H

#include <QMainWindow>
#include <screenshot.h>
#include <backgroundimage.h>
#include <graphmanager.h>
#include <QImage>
#include <mouse.h>

namespace Ui {
class MainWindow2;
}

class MainWindow2 : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow2(QWidget *parent = 0);
    ~MainWindow2();

public Q_SLOTS:
    void screenShot();

private:
    void initHeroeBattle();
    void initAttackTower();

    Ui::MainWindow2 *m_ui;

    Screenshot m_screenShot;
    Mouse m_mouseControl;

    GraphManager m_graphMger;
    GraphManager::Elt* m_begin;
    int m_beginElt;

    int m_nbVictory;
    int m_nbDefeat;
};

#endif // MAINWINDOW2_H
