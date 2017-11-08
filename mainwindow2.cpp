#include "mainwindow2.h"
#include "ui_mainwindow2.h"
#include <QTimer>
#include <QPixmap>
#include <QColor>
#include <QQuickWidget>
#include <QLayout>
#include <backgroundimage.h>
#include <chrono>
#include <thread>

static int waitMilliSec = 2000;
static QString basePath = "D:/tmp/dongeon keeper/";

MainWindow2::MainWindow2(QWidget *parent)
    :QMainWindow(parent, Qt::WindowStaysOnTopHint)
    , m_ui(new Ui::MainWindow2)
    , m_beginElt(0)
    , m_nbVictory(0)
    , m_nbDefeat(0)
{
    m_ui->setupUi(this);

    m_begin = new GraphManager::Elt();
    m_begin->_name = "begin";
    m_begin->_pattern = QImage();

    m_graphMger.addElts(m_begin);

    initHeroeBattle();
    initAttackTower();

    QTimer::singleShot(waitMilliSec,this,&MainWindow2::screenShot);
}

void MainWindow2::initHeroeBattle()
{
    GraphManager::Elt* beginHeroBattle = new GraphManager::Elt();
    beginHeroBattle->_name = "beginHeroBattle";
    beginHeroBattle->_pattern = QImage();

    GraphManager::Elt* heroBattle = new GraphManager::Elt();
    heroBattle->_name = "heroBattle";
    heroBattle->_pattern = QImage(basePath + "heroBattle.png");

    GraphManager::Elt* wizardsChosen = new GraphManager::Elt();
    wizardsChosen->_name = "WizardsChosen";
    wizardsChosen->_pattern = QImage(basePath + "WizardsChosen.png");

    GraphManager::Elt* yes = new GraphManager::Elt();
    yes->_name = "yes";
    yes->_pattern = QImage(basePath + "yes.png");

    // first battle
    GraphManager::Elt* paladin = new GraphManager::Elt();
    paladin->_name = "paladin";
    paladin->_pattern = QImage(basePath + "paladin.png");

    GraphManager::Elt* paladinPower = new GraphManager::Elt();
    paladinPower->_name = "paladinPower";
    paladinPower->_pattern = QImage(basePath + "paladinPower.png");

    GraphManager::Elt* kensaiPower = new GraphManager::Elt();
    kensaiPower->_name = "kensaiPower";
    kensaiPower->_pattern = QImage(basePath + "kensaiPower.png");

    GraphManager::Elt* shamanPower = new GraphManager::Elt();
    shamanPower->_name = "shamanPower";
    shamanPower->_pattern = QImage(basePath + "shamanPower.png");

    GraphManager::Elt* templarPower = new GraphManager::Elt();
    templarPower->_name = "templarPower";
    templarPower->_pattern = QImage(basePath + "templarPower.png");

    // second battle
    GraphManager::Elt* barbarianPower = new GraphManager::Elt();
    barbarianPower->_name = "barbarianPower";
    barbarianPower->_pattern = QImage(basePath + "barbarianPower.png");

    GraphManager::Elt* clericPower = new GraphManager::Elt();
    clericPower->_name = "clericPower";
    clericPower->_pattern = QImage(basePath + "clericPower.png");

    GraphManager::Elt* amazonPower = new GraphManager::Elt();
    amazonPower->_name = "amazonPower";
    amazonPower->_pattern = QImage(basePath + "amazonPower.png");

    GraphManager::Elt* backguardPower = new GraphManager::Elt();
    backguardPower->_name = "backguardPower";
    backguardPower->_pattern = QImage(basePath + "backguardPower.png");

    // third battle
    GraphManager::Elt* archemagePower = new GraphManager::Elt();
    archemagePower->_name = "archemagePower";
    archemagePower->_pattern = QImage(basePath + "archemagePower.png");

    GraphManager::Elt* druidPower = new GraphManager::Elt();
    druidPower->_name = "druidPower";
    druidPower->_pattern = QImage(basePath + "druidPower.png");

    GraphManager::Elt* archerPower = new GraphManager::Elt();
    archerPower->_name = "archerPower";
    archerPower->_pattern = QImage(basePath + "archerPower.png");

    // end
    GraphManager::Elt* ok = new GraphManager::Elt();
    ok->_name = "ok";
    ok->_pattern = QImage(basePath + "ok.png");

    GraphManager::Elt* okV = new GraphManager::Elt();
    okV->_name = "okV";
    okV->_pattern = QImage(basePath + "okV.png");

    // no more coins
    GraphManager::Elt* stop = new GraphManager::Elt();
    stop->_name = "stop";
    stop->_pattern = QImage(basePath + "stop.png");

    GraphManager::Elt* close = new GraphManager::Elt();
    close->_name = "close";
    close->_pattern = QImage(basePath + "close.png");

    GraphManager::Elt* back = new GraphManager::Elt();
    back->_name = "back";
    back->_pattern = QImage(basePath + "back.png");

    m_graphMger.addElts(beginHeroBattle);
    m_graphMger.addElts(heroBattle);
    m_graphMger.addElts(wizardsChosen);
    m_graphMger.addElts(stop);
    m_graphMger.addElts(close);
    m_graphMger.addElts(back);
    m_graphMger.addElts(yes);
    m_graphMger.addElts(paladin);
    m_graphMger.addElts(paladinPower);

    m_graphMger.connectTo(m_begin, beginHeroBattle);
    m_graphMger.connectTo(beginHeroBattle, heroBattle);
    m_graphMger.connectTo(heroBattle, wizardsChosen);
    m_graphMger.connectTo(wizardsChosen, yes);
    m_graphMger.connectTo(wizardsChosen, stop);
    m_graphMger.connectTo(stop, close);
    m_graphMger.connectTo(close, back);
    m_graphMger.connectTo(yes, paladin);

    //selection paladin
    m_graphMger.connectTo(paladin, paladinPower);
    m_graphMger.connectTo(paladin, kensaiPower);
    m_graphMger.connectTo(paladin, shamanPower);

    //selection power 1st round
    m_graphMger.link(paladinPower, kensaiPower);
    m_graphMger.link(paladinPower, shamanPower);
    m_graphMger.link(paladinPower, templarPower);
    m_graphMger.link(kensaiPower, shamanPower);
    m_graphMger.link(kensaiPower, templarPower);
    m_graphMger.link(shamanPower, templarPower);

    // begin 2sd round
    m_graphMger.connectTo(kensaiPower, barbarianPower);
    m_graphMger.connectTo(paladinPower, barbarianPower);
    m_graphMger.connectTo(shamanPower, barbarianPower);
    m_graphMger.connectTo(templarPower, barbarianPower);
    m_graphMger.connectTo(kensaiPower, amazonPower);
    m_graphMger.connectTo(paladinPower, amazonPower);
    m_graphMger.connectTo(shamanPower, amazonPower);
    m_graphMger.connectTo(templarPower, amazonPower);

    //selection power 2sd round
    m_graphMger.link(amazonPower, clericPower);
    m_graphMger.link(amazonPower, backguardPower);
    m_graphMger.link(amazonPower, barbarianPower);
    m_graphMger.link(backguardPower, clericPower);
    m_graphMger.link(backguardPower, barbarianPower);
    m_graphMger.link(clericPower, barbarianPower);

    // maybe end
    m_graphMger.link(amazonPower, ok);
    m_graphMger.link(backguardPower, ok);
    m_graphMger.link(clericPower, ok);
    m_graphMger.link(barbarianPower, ok);
    m_graphMger.link(amazonPower, okV);
    m_graphMger.link(backguardPower, okV);
    m_graphMger.link(clericPower, okV);
    m_graphMger.link(barbarianPower, okV);

    // begin 3th round
    m_graphMger.connectTo(amazonPower, archemagePower);
    m_graphMger.connectTo(backguardPower, archemagePower);
    m_graphMger.connectTo(clericPower, archemagePower);
    m_graphMger.connectTo(barbarianPower, archemagePower);
    m_graphMger.connectTo(amazonPower, druidPower);
    m_graphMger.connectTo(backguardPower, druidPower);
    m_graphMger.connectTo(clericPower, druidPower);
    m_graphMger.connectTo(barbarianPower, druidPower);

    //selection power 3th round
    m_graphMger.link(archemagePower, druidPower);

    // maybe end
    m_graphMger.link(archemagePower, ok);
    m_graphMger.link(druidPower, ok);
    m_graphMger.link(archemagePower, okV);
    m_graphMger.link(druidPower, okV);
    m_graphMger.link(okV, ok);

    // restart
    m_graphMger.connectTo(ok, heroBattle);
    m_graphMger.connectTo(okV, heroBattle);
}

void MainWindow2::initAttackTower()
{
    GraphManager::Elt* beginAttackTower = new GraphManager::Elt();
    beginAttackTower->_name = "beginAttackTower";
    beginAttackTower->_pattern = QImage();

    GraphManager::Elt* attackTower = new GraphManager::Elt();
    attackTower->_name = "attackTower";
    attackTower->_pattern = QImage(basePath + "attackTower.png");

    GraphManager::Elt* attack = new GraphManager::Elt();
    attack->_name = "attack";
    attack->_pattern = QImage(basePath + "attack.png");

    GraphManager::Elt* toBattle = new GraphManager::Elt();
    toBattle->_name = "toBattle";
    toBattle->_pattern = QImage(basePath + "toBattle.png");

    GraphManager::Elt* paladin = new GraphManager::Elt();
    paladin->_name = "paladin";
    paladin->_pattern = QImage(basePath + "paladin.png");

    // battle
    GraphManager::Elt* archemagePower = new GraphManager::Elt();
    archemagePower->_name = "archemagePower";
    archemagePower->_pattern = QImage(basePath + "archemagePower.png");

    GraphManager::Elt* paladinPower = new GraphManager::Elt();
    paladinPower->_name = "paladinPower";
    paladinPower->_pattern = QImage(basePath + "paladinPower.png");

    GraphManager::Elt* kensaiPower = new GraphManager::Elt();
    kensaiPower->_name = "kensaiPower";
    kensaiPower->_pattern = QImage(basePath + "kensaiPower.png");

    GraphManager::Elt* druidPower = new GraphManager::Elt();
    druidPower->_name = "druidPower";
    druidPower->_pattern = QImage(basePath + "druidPower.png");

    // end
    GraphManager::Elt* ok = new GraphManager::Elt();
    ok->_name = "ok";
    ok->_pattern = QImage(basePath + "ok.png");

    GraphManager::Elt* okV = new GraphManager::Elt();
    okV->_name = "okV";
    okV->_pattern = QImage(basePath + "okV.png");

    // no more coins
    GraphManager::Elt* stop = new GraphManager::Elt();
    stop->_name = "stop";
    stop->_pattern = QImage(basePath + "stop.png");

    GraphManager::Elt* close = new GraphManager::Elt();
    close->_name = "close";
    close->_pattern = QImage(basePath + "close.png");

    GraphManager::Elt* back = new GraphManager::Elt();
    back->_name = "back";
    back->_pattern = QImage(basePath + "close.png");

    m_graphMger.addElts(attackTower);
    m_graphMger.addElts(attack);
    m_graphMger.addElts(toBattle);

    m_graphMger.connectTo(m_begin, beginAttackTower);
    m_graphMger.connectTo(beginAttackTower, attackTower);
    m_graphMger.connectTo(attackTower, attack);
    m_graphMger.connectTo(attack, toBattle);
    m_graphMger.connectTo(attack, stop);
    m_graphMger.connectTo(stop, close);
    m_graphMger.connectTo(close, back);
    m_graphMger.connectTo(toBattle, paladin);

    //selection paladin
    m_graphMger.connectTo(paladin, paladinPower);
    m_graphMger.connectTo(paladin, archemagePower);
    m_graphMger.connectTo(paladin, druidPower);
    m_graphMger.connectTo(paladin, kensaiPower);

    //selection power 1st round
    m_graphMger.link(paladinPower, archemagePower);
    m_graphMger.link(paladinPower, druidPower);
    m_graphMger.link(paladinPower, kensaiPower);
    m_graphMger.link(archemagePower, druidPower);
    m_graphMger.link(archemagePower, kensaiPower);
    m_graphMger.link(druidPower, kensaiPower);

    // maybe end
    m_graphMger.connectTo(paladinPower, ok);
    m_graphMger.connectTo(archemagePower, ok);
    m_graphMger.connectTo(druidPower, ok);
    m_graphMger.connectTo(kensaiPower, ok);
    m_graphMger.connectTo(paladinPower, okV);
    m_graphMger.connectTo(archemagePower, okV);
    m_graphMger.connectTo(druidPower, okV);
    m_graphMger.connectTo(kensaiPower, okV);
    m_graphMger.link(okV, ok);

    // restart
    m_graphMger.connectTo(ok, attackTower);
    m_graphMger.connectTo(okV, attackTower);
}

MainWindow2::~MainWindow2()
{
    delete m_ui;
}

static int pid = 0;

void MainWindow2::screenShot()
{
    BackgroundImage bi = m_screenShot.takeScreenshot();
    BackgroundImage::box b;
    QImage image;
    for (GraphManager::Elt* elt : m_graphMger.getCurrentElt()->_outputElts)
    {
        image = elt->_pattern;


        b = bi.findSampleImage(image,100);
        if(b.isValid())
        {
            m_graphMger.setCurrentElt(elt);
            image = image.scaled(image.size()/2);
            m_ui->label->setPixmap(QPixmap::fromImage(image));
            break;
        }
    }



    if (b.isValid())
    {
        if(m_graphMger.getCurrentElt()->_name == "okV")
        {
            ++m_nbVictory;
            std::this_thread::sleep_for(std::chrono::milliseconds(waitMilliSec));
        }
        if(m_graphMger.getCurrentElt()->_name == "ok")
        {
            ++m_nbDefeat;
            std::this_thread::sleep_for(std::chrono::milliseconds(waitMilliSec));
        }
        if(m_graphMger.getCurrentElt()->_name != "stop")
        {
            int xc = b._xmin + (b._xmax - b._xmin)/2;
            int yc = b._ymin + (b._ymax - b._ymin)/2;
            m_mouseControl.leftClickOnPoint(QPoint(yc, xc));
        }
        if(m_graphMger.getCurrentElt()->_name == "back")
        {
            m_beginElt = (m_beginElt + 1)%m_begin->_outputElts.size();
            m_graphMger.setCurrentElt(m_begin->_outputElts[m_beginElt]);
            if( m_beginElt == 0)
            {
                system("Shutdown /h");
                return;
            }
        }
    }

    QTimer::singleShot(waitMilliSec,this,&MainWindow2::screenShot);

    m_ui->score->setText(QString("V: %1 -- D: %2").arg(m_nbVictory).arg(m_nbDefeat));
}
