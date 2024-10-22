#include "Wilder.h"

Wilder::Wilder(const QVector<QPoint>& routine_, QGraphicsItem *parent ):Enemy(routine_,parent)
{
    // 人类单位, 血量较多, 给目标带来一点伤害. 出现在第一关
    path = ":/img/asset/Wild1.png"; // 假设图片路径
    if (!enemyPix.load(path)) {
        qDebug() << "Failed to load enemy image from" << path;
    }
    health=100;//血量较多
    damage=1;
    speed=120;
    reward=160;
    enemyType=0;

    moveTimer->start(1000 / speed);
}
