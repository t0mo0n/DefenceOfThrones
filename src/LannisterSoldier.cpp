#include "LannisterSoldier.h"

LannisterSoldier::LannisterSoldier(const QVector<QPoint>& routine_, QGraphicsItem *parent ):Enemy(routine_,parent)
{
    // 人类单位, 基础单位, 带来一点伤害. 出现在第三关
    path = ":/img/asset/LannistSoldier.png"; // 假设图片路径
    if (!enemyPix.load(path)) {
        qDebug() << "Failed to load enemy image from" << path;
    }
    health=65;
    speed=80;
    reward=150;
    enemyType=0;

    moveTimer->start(1000 / speed);
}
