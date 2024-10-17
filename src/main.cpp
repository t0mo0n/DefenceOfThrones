// #include "GameController.h"

// #include <QApplication>

// int main(int argc, char *argv[])
// {
//     QApplication a(argc, argv);
//     GameController w;
//     w.show();
//     return a.exec();
// }

#include <Enemy.h>
#include <QApplication>
#include <TowerFrame.h>
#include <Archer.h>
#include <StoneThrower.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


    QGraphicsScene scene;
    scene.setSceneRect(0, 0, 1000, 1000);
    scene.setBackgroundBrush(QBrush(Qt::lightGray));

    Enemy *item = new Enemy(1);
    item->setPos(QPointF(50,250));
    scene.addItem(item);

    Enemy *item2 = new Enemy(2);
    item2->setPos(QPointF(150,250));
    scene.addItem(item2);
    Enemy *item3 = new Enemy(3);
    item3->setPos(QPointF(1,600));
    scene.addItem(item3);

    Archer *tow1=new Archer(QPoint(300,300));
    StoneThrower *ss=new StoneThrower(QPoint(500,300));
    Archer *tow2=new Archer(QPoint(500,100));
    scene.addItem(tow1);
    scene.addItem(tow2);
    scene.addItem(ss);



    QGraphicsView view(&scene);
    view.setFixedSize(1000, 1000);
    view.show();



    QTimer timer;
    QObject::connect(&timer, &QTimer::timeout, item, &Enemy::moveItem);

    QObject::connect(&timer, &QTimer::timeout, item2, &Enemy::moveItem);
    QObject::connect(&timer, &QTimer::timeout, item3, &Enemy::moveItem);




    timer.start(100);






    return a.exec();
}
