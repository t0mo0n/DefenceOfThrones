#include "Melisandre.h"

Melisandre::Melisandre(const QVector<QPoint>& routine_, QGraphicsItem *parent ):Enemy(routine_,parent)
{
    //人类单位, 移速较快, 可复活自己一次, 给目标带来一点伤害.出现在全部三关中.

    path = ":/colored.png"; // 假设图片路径
    if (!enemyPix.load(path)) {
        qDebug() << "Failed to load enemy image from" << path;
    }
    health=60;
    speed=7;
    reward=270;
    enemyType=0;
    damage=1;
    use=0;
    reviveHealth=health;
}

void Melisandre::takeDamage(int damage_)
{
    health -= damage_;
    if (health <= 0) {
        if(!use){
            health=reviveHealth;
            use=1;
            return ;
        }
        health = 0;
        emit isDead(reward,this); // 发出死亡信号
        moveTimer->stop();
    }
}
