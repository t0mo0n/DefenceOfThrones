#include "Deadalive.h"

DeadAlive::DeadAlive(const QVector<QPoint>& routine_, QGraphicsItem *parent ):Enemy(routine_,parent)
{
    path = ":/img/asset/Deadalive.png"; // 假设图片路径
    if (!enemyPix.load(path)) {
        qDebug() << "Failed to load enemy image from" << path;
    }
    damage=1;
    health=60;
    speed=80;
    reward=100;
    enemyType=1;

    moveTimer->start(1000 / speed);
}
