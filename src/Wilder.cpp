#include "Wilder.h"

Wilder::Wilder(const QVector<QPoint>& routine_, QGraphicsItem *parent ):Enemy(routine_,parent)
{
    // 人类单位, 血量较多, 给目标带来一点伤害. 出现在第一关
    path = ":/colored.png"; // 假设图片路径
    if (!enemyPix.load(path)) {
        qDebug() << "Failed to load enemy image from" << path;
    }
    health=150;//血量较多
    enemyType=0;
}
