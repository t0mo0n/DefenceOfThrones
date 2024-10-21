#include "GreyjoySoldier.h"

GreyjoySoldier::GreyjoySoldier(const QVector<QPoint>& routine_, QGraphicsItem *parent ):Enemy(routine_,parent)
{
    // 人类单位, 移速较快. 出现在第三关

    path = ":/img/asset/GreyJoySoldier.png"; // 假设图片路径
    if (!enemyPix.load(path)) {
        qDebug() << "Failed to load enemy image from" << path;
    }
    health=60;
    speed=120;
    reward=180;
    enemyType=0;

    moveTimer->start(1000 / speed);
}
