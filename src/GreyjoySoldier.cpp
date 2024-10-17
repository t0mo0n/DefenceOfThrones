#include "GreyjoySoldier.h"

GreyjoySoldier::GreyjoySoldier(const QVector<QPoint>& routine_, QGraphicsItem *parent ):Enemy(routine_,parent)
{
    // 人类单位, 移速较快. 出现在第三关

    path = ":/colored.png"; // 假设图片路径
    if (!enemyPix.load(path)) {
        qDebug() << "Failed to load enemy image from" << path;
    }

    enemyType=0;
    speed=5;
}
