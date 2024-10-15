#include "StoneThrower.h"

StoneThrower::StoneThrower(QPoint pos_)
    :TowerFrame(pos_,2)
{
    projectType=2;
    attackRange=200;
    attackSpeed=600;
    buyCost=1500;
    sellPrice=900;
    picDir=":/img/asset/GOT.jpg";
    towerType=2;

    upgradeFee.push_back(2000);
    upgradeFee.push_back(3000);
    upgradeFee.push_back(4000);
    aimTimer=new QTimer(this);
    attackTimer=new QTimer(this);


    connect(attackTimer,&QTimer::timeout,this,&StoneThrower::attack);
    attackTimer->start(attackSpeed);    // 根据攻击速度设置定时器间隔
}

void StoneThrower::attack()
{


}

void StoneThrower::upgrade()
{
    if(level>=2)
    {
        return;
    }
    level++;
    attackRange+=100;
    attackSpeed+=100;
    projectType=1;
    update();
}
void StoneThrower::checkForItemsInBoundingRect()
{


}
// void StoneThrower::FindEnemy()
// {

// }
