#include "Melisandre.h"

Melisandre::Melisandre(const QVector<QPoint>& routine_, QGraphicsItem *parent ):Enemy(routine_,parent)
{
    //人类单位, 移速较快, 可复活自己一次, 给目标带来一点伤害.出现在全部三关中.

    path = ":/img/asset/RedWitch.png"; // 假设图片路径
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
        moveTimer->stop();
        emit isDead(reward,this); // 发出死亡信号
    }
}

void Melisandre::move()
{
    if (isEnterBase) {
        emit isArrived(damage,this);
        return;
    }

    stepCount++;
    switch (direct){
    case 1:
        pos0.setY(pos0.y()-STEP);
        break;
    case 2:
        pos0.setY(pos0.y()+STEP);
        break;
    case 3:
        pos0.setX(pos0.x()-STEP);
        break;
    case 4:
        pos0.setX(pos0.x()+STEP);
        break;
    default:
        break;
    }

    if(stepCount>=step){
        index++;
        if(index>=routine.size()){
            isEnterBase=true;
            emit isArrived(damage,this);
            return;
        }
        stepCount=0;
        if(routine[index-1].x()==routine[index].x()){
            if(routine[index-1].y()>routine[index].y()){
                direct=1;//上
            }else{
                direct=2;//下
            }
            step=abs(routine[index].y()-routine[index-1].y())/STEP;
        }else{
            if(routine[index-1].x()>routine[index].x()){
                direct=3;//左
            }else{
                direct=4;//右
            }
            step=abs(routine[index].x()-routine[index-1].x())/STEP;
        }
    }

    if(isFire){
        if(fireCount<500){
            fireCount++;
            if(fireCount%50==0){
                health--;
                if (health <= 0) {
                    if(use){
                        health = 0;
                        moveTimer->stop();
                        emit isDead(reward,this); // 发出死亡信号
                        return;
                    }else{
                        health=reviveHealth;
                        use=true;
                    }

                }
            }
        }else{
            isFire=false;
            fireCount=0;
        }
    }

    if (index >= routine.size()&&stepCount>step-1 ) {
        isEnterBase = true;
        emit isArrived(damage,this); // 发出进入基地的信号
        return ;
    }else{
        this->setPos(pos0); // 更新 QGraphicsItem 的位置
        // 更新图形项的位置
        healthDisplay->setPos(size / 2 - healthDisplay->boundingRect().width() / 2,
                              -50+healthDisplay->boundingRect().height());
        updateHealthDisplay();
    }
}
