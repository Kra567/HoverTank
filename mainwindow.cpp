#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QTimer>
#include "forces.h"
#include <QShortcut>
#include <map>
#include "gameworld.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    //ui->setupUi(this);
    //this->setAcceptHoverEvents(true);
    //this->resize(700,600);
    //qDebug()
    // 1536 x 864
    setWindowState(Qt::WindowFullScreen);
    qDebug() << size();
    this->setMouseTracking(true);
    //Weapon({},)
    Weapon wep = Weapon({0,M_PI/4,-M_PI/4},500,10,5,10,2);
    world.spamHero(QPointF(800,600),{wep});
   //world.getHero()->shoot();

    QImage block = QImage(":/WallSprites/IMG/WALLT.png").transformed(QTransform().scale(3,3));
    QImage bionic = QImage(":/WallSprites/IMG/Floor.png").transformed(QTransform().scale(3,3));




    PolynomCurve curve = PolynomCurve({QPointF(20,20),
                                       QPointF(200,60),
                                       QPointF(500,30),
                                       QPointF(1000,30),
                                      QPointF(1300,60),
                                       QPointF(1480,20),
                                       QPointF(1440,300),
                                       QPointF(1440,500),
                                       QPointF(1480,800),
                                       QPointF(1300,760),
                                       QPointF(1000,790),
                                       QPointF(500,790),
                                       QPointF(200,760),
                                       QPointF(20,800),
                                       QPointF(60,500),
                                       QPointF(60,300),
                                       QPointF(20,20)
                                      });

    std::vector<std::vector<QPointF>> barriers = {
        {QPointF(250,150),QPointF(450,150),QPointF(500,400),QPointF(250,350),QPointF(250,150)},
        {QPointF(350,650),QPointF(500,550),QPointF(700,700),QPointF(350,650)},
        {QPointF(800,200),QPointF(1200,350),QPointF(1300,450),QPointF(900,600),QPointF(800,200)},

    };
    for (auto bar : barriers){
        Wall wall_ = Wall(bar);
        wall_.setImage(bionic);
        wall_.setDrawPriority(2);
        world.spamWall(wall_);
    }
    /*
    PolynomCurve curve0 = PolynomCurve({QPointF(250,350),QPointF(200,400),QPointF(450,350),QPointF(250,350)});
    PolynomCurve curve1 = PolynomCurve({QPointF(300,250),QPointF(300,150),QPointF(450,150),QPointF(400,250),QPointF(300,250)});
    */
    Wall wall = Wall(curve);
    wall.setImage(block);
    world.spamWall(wall);

    /*

    Wall wall0 = Wall(curve0);
    wall0.setDrawPriority(2);
    wall0.setImage(bionic);

    Wall wall1 = Wall(curve1);
    wall1.setDrawPriority(2);
    wall1.setImage(bionic);

    world.spamWall(wall0);
    world.spamWall(wall1);

    Body* ebody = new Body(QPointF(250,250),20,10);
    */

    //world.spamEnemy(Enemy(new Body(QPointF(250,250),100,15),10,10,200));
    //world.spamEnemy(Enemy(new Body(QPointF(280,250),100,15),10,10,200));
    //world.spamEnemy(Enemy(new Body(QPointF(250,290),100,15),10,10,200));






    // drawing and start
    QObject::connect(world.getGameTimer(),&GameTimer::timeout,this,[&](){this->update();});
    world.getGameTimer()->start();


}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    world.paint(painter);

}

void MainWindow::mouseMoveEvent(QMouseEvent * event)
{
    world.getHero()->setWay(this->mapFromGlobal(QCursor::pos()));
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_W){
        //world.getHero()->addVelocity(QPointF(0,-50));
        world.up->activate();
    }
    if (event->key() == Qt::Key_A){
        world.left->activate();
        //world.getHero()->addVelocity(QPointF(-50,0));
    }
    if (event->key() == Qt::Key_S){
        world.down->activate();
        //world.getHero()->addVelocity(QPointF(0,50));
    }
    if (event->key() == Qt::Key_D){
        world.right->activate();
        //world.getHero()->addVelocity(QPointF(50,0));
    }
}

void MainWindow::keyReleaseEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_W){
        world.up->disactivate();
    }
    if (event->key() == Qt::Key_S){
        world.down->disactivate();
    }
    if (event->key() == Qt::Key_A){
        world.left->disactivate();
    }
    if (event->key() == Qt::Key_D){
        world.right->disactivate();
    }
}

void MainWindow::mousePressEvent(QMouseEvent *event){
    if (event->button() == Qt::LeftButton){
        world.getHero()->shoot();
    }
}



void MainWindow::first_slot()
{
    qDebug() << "first slot";
}

void MainWindow::second_slot()
{
    qDebug() << "second slot";
}




