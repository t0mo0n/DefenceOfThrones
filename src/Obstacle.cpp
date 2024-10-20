#include "Obstacle.h"



Obstacle::Obstacle(int price_, int health_, int type_,QPoint pos_,QWidget *parent):pos(pos_)
{
    if(type==0){
        path = ":/colored.png"; // 假设图片路径
    }else if(type==1){
        path = ":/colored.png"; // 假设图片路径
    }else if(type==2){
        path = ":/colored.png"; // 假设图片路径
    }

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


void Obstacle::receive(int damage_,int type){
    checkIfDead(damage_);

}

void Obstacle::receiveSnow(int damage_){
    checkIfDead(damage_);
}
