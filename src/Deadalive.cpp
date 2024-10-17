#include "Deadalive.h"

DeadAlive::DeadAlive(const QVector<QPoint>& routine_, QGraphicsItem *parent ):Enemy(routine_,parent)
{
    path = ":/colored.png"; // 假设图片路径
    if (!enemyPix.load(path)) {
        qDebug() << "Failed to load enemy image from" << path;
    }

    enemyType=1;
}
