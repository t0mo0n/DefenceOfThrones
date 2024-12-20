#include "Mountain.h"

Mountain::Mountain(const QVector<QPoint>& routine_, QGraphicsItem *parent):Enemy(routine_,parent)
{
    // 人类单位, 血量非常非常丰厚, 给目标带来五点伤害. 出现在第三关.
    path = ":/img/asset/Mountain.png"; // 假设图片路径
    if (!enemyPix.load(path)) {
        qDebug() << "Failed to load enemy image from" << path;
    }

    health=600;
    speed=95;
    reward=600;
    enemyType=0;
    damage=5;

    moveTimer->start(1000 / speed);
}
