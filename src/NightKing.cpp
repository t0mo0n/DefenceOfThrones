#include "NightKing.h"

NightKing::NightKing(const QVector<QPoint>& routine_, QGraphicsItem *parent ):Enemy(routine_,parent)
{
    // 异鬼军团单位, 异鬼军团的王, 第二关的 BOSS. 血量非常丰厚, 给目标带来
    // 三点伤害. 可以每八秒在自己的位置召唤一只异鬼士兵.
    path = ":/colored.png"; // 假设图片路径
    if (!enemyPix.load(path)) {
        qDebug() << "Failed to load enemy image from" << path;
    }

    health=500;
    speed=4;
    reward=2000;
    damage=3;
    enemyType=1;
    timer=new QTimer;
    timer = new QTimer(this);
    // connect(timer, &QTimer::timeout, this, &NightKing::generateDeadalive);
    timer->start(8000);
}

void NightKing::generate()
{
    QPoint p;
    switch (direct){
    case 1:
        p.setY(pos0.y()+80);
        p.setX(pos0.x());
        break;
    case 2:
        p.setY(pos0.y()-80);
        p.setX(pos0.x());
        break;
    case 3:
        p.setX(pos0.x()+80);
        p.setY(pos0.y());
        break;
    case 4:
        p.setX(pos0.x()-80);
        p.setY(pos0.y());
        break;
    default:
        break;
    }

    emit generateDeadalive(p);
}