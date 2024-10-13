// #include "GameController.h"

// #include <QApplication>

// int main(int argc, char *argv[])
// {
//     QApplication a(argc, argv);
//     GameController w;
//     w.show();
//     return a.exec();
// }

#include <GameController.h>
#include <MovingItem.h>
#include <QApplication>
#include <TowerFrame.h>
#include <Archer.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    // MainWindow w;
    // w.show();

    QGraphicsScene scene;
    scene.setSceneRect(0, 0, 1000, 1000);
    scene.setBackgroundBrush(QBrush(Qt::lightGray));

    MovingItem *item = new MovingItem();
    item->setPos(QPointF(10,250));
    scene.addItem(item);


    Archer *tow1=new Archer(QPoint(300,300));

    Archer *tow2=new Archer(QPoint(500,100));
    scene.addItem(tow1);
    scene.addItem(tow2);
    tow1->setTarget(item);
    tow2->setTarget(item);

    QGraphicsView view(&scene);
    view.setFixedSize(1000, 1000);
    view.show();



    QTimer timer;
    QObject::connect(&timer, &QTimer::timeout, item, &MovingItem::moveItem);


    // QObject::connect(&timer, &QTimer::timeout,item, [tow1,item]() {
    //     // 检查碰撞
    //     if (tow1->collidesWithItem(item)) {
    //         qDebug() << "Collision detected!";
    //         tow1->Attack();
    //     } else {
    //         qDebug() << "No collision.";
    //     }
    // });
    timer.start(100);
    // timer2.start(1000);






    return a.exec();
}
