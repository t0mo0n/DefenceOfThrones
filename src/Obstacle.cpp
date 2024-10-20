#include "Obstacle.h"



Obstacle::Obstacle(int type_,QPoint init_pos, QGraphicsItem *parent ):Enemy(QVector<QPoint>(),parent)
{
    size = 80; // 设定障碍物大小
    step = 0;
    stepCount = 0;
    isEnterBase = false;
    index = 0;
    speed = 0; // 假设障碍物不移动
    damage = 0; // 假设障碍物没有攻击伤害
    pos0 = init_pos; // 初始位置
    type=type_;
    if(type==0){
        health=50;
        reward=180;
        path = ":/img/asset/GOT.jpg"; // 假设图片路径
    }else if(type==1){
        health=80;
        reward=300;
        path = ":/img/asset/GOT.jpg"; // 假设图片路径
    }else if(type==2){
        health=160;
        reward=420;
        path = ":/img/asset/GOT.jpg"; // 假设图片路径
    }else if(type==3){
        health=100;
        reward=360;
        path = ":/img/asset/GOT.jpg"; // 假设图片路径
    }else if(type==4){
        health=70;
        reward=200;
        path = ":/img/asset/GOT.jpg"; // 假设图片路径
    }else if(type==5){
        health=120;
        reward=400;
        path = ":/img/asset/GOT.jpg"; // 假设图片路径
    }else if(type==6){
        health=100;
        reward=250;
        path = ":/img/asset/GOT.jpg"; // 假设图片路径
    }else if(type==7){
        health=100;
        reward=250;
        path = ":/img/asset/GOT.jpg"; // 假设图片路径
    }else if(type==8){
        health=200;
        reward=450;
        path = ":/img/asset/GOT.jpg"; // 假设图片路径
    }else if(type==9){
        health=350;
        reward=750;
        path = ":/img/asset/GOT.jpg"; // 假设图片路径
    }

    if (!enemyPix.load(path)) {
        qDebug() << "Failed to load enemy image from" << path;
    }

    reward=10;
    health=10;
}

void Obstacle::takeDamage(int damage_)
{
    if(health>0){
        health-=damage_;
        if(health<=0){
            emit isDamaged(reward,this);
        }
    }
}

// // 绘制障碍物
// void Obstacle::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
// {
//     Q_UNUSED(option);
//     Q_UNUSED(widget);
//     painter->drawPixmap(boundingRect(), enemyPix,enemyPix.rect());
// }


void Obstacle::receive(int damage_,int type){
    Q_UNUSED(type);
    takeDamage(damage_);
}

