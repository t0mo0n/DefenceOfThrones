#include "KingSlayer.h"

KingSlayer::KingSlayer(const QVector<QPoint>& routine_, QGraphicsItem *parent):Enemy(routine_,parent)
{
    // 人类单位, 血量丰厚, 移速很快, 可给目标带来三点伤害. 第三关的 BOSS.
    path = ":/colored.png"; // 假设图片路径
    if (!enemyPix.load(path)) {
        qDebug() << "Failed to load enemy image from" << path;
    }

    health=550;
    reward=2000;
    enemyType=0;
    speed=10;
    damage=3;

}
