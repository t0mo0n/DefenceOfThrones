#include "NightKing.h"

NightKing::NightKing(const QVector<QPoint>& routine_, QGraphicsItem *parent ):Enemy(routine_,parent)
{
    // 异鬼军团单位, 异鬼军团的王, 第二关的 BOSS. 血量非常丰厚, 给目标带来
    // 三点伤害. 可以每八秒在自己的位置召唤一只异鬼士兵.
    path = ":/colored.png"; // 假设图片路径
    if (!enemyPix.load(path)) {
        qDebug() << "Failed to load enemy image from" << path;
    }

    health=150;
    damage=3;
    enemyType=1;
    timer=new QTimer;
    timer = new QTimer(this);
    // connect(timer, &QTimer::timeout, this, &NightKing::generateDeadalive);
    timer->start(15000);
}

// void NightKing::generate()
// {

// }
