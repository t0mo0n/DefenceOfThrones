#include "Deadalive.h"

DeadAlive::DeadAlive(const QVector<QPoint>& routine_, QGraphicsItem *parent ):Enemy(routine_,parent)
{
    path = ":/img/asset/GOT.jpg"; // 假设图片路径
    if (!enemyPix.load(path)) {
        qDebug() << "Failed to load enemy image from" << path;
    }
    damage=1;
    health=50;
    speed=4;
    reward=100;
    enemyType=1;
}
