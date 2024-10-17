#include "Obstacle.h"



Obstacle::Obstacle(int price_, int health_, QPoint pos_,QWidget *parent):pos(pos_)
{
    path = ":/colored.png"; // 假设图片路径
    if (!obstaclePix.load(path)) {
        qDebug() << "Failed to load enemy image from" << path;
    }

    price=price_;
    health=health_;
}

void Obstacle::checkIfDead(int damage)
{
    if(health>0){
        health-=damage;

        if(health<=0){
            emit isDamaged(price);
            delete this;
        }
    }
}
QRectF Obstacle::boundingRect() const
{
    return QRectF(pos, QSize(obstaclePix.width(), obstaclePix.height()));
}

// 绘制障碍物
void Obstacle::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    painter->drawPixmap(pos, obstaclePix);
}
