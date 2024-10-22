#include "Vesalion.h"

Vesalion::Vesalion(const QVector<QPoint>& routine_, QGraphicsItem *parent ):Enemy(routine_,parent)
{
//异鬼军团单位, 血量较多, 移速很快, 空中单位, 无法被琼恩雪诺攻击到.
//它是被夜王杀死并复活的龙, 可以喷出蓝色火焰, 所以对目标可以带来五点伤害. 出现在第二关.
    path = ":/img/asset/IceDragon.png"; // 假设图片路径
    if (!enemyPix.load(path)) {
        qDebug() << "Failed to load enemy image from" << path;
    }
    health=240;
    speed=190;
    damage=5;
    reward=500;
    enemyType=1;

    moveTimer->start(1000 / speed);
}
