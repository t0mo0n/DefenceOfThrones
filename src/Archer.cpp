#include "Archer.h"

Archer::Archer(QPoint pos_)
    :TowerFrame(pos_,1)
{
    projectType=0;
    attackRange=150;
    attackSpeed=800;
    buyCost=1000;
    sellPrice=900;
    picDir=":/img/asset/3.png";
    towerType=1;

    upgradeFee.push_back(1000);
    upgradeFee.push_back(2000);
    upgradeFee.push_back(3000);
    aimTimer=new QTimer(this);
    attackTimer=new QTimer(this);

    connect(aimTimer, &QTimer::timeout, this, [this](){
        FindEnemy();
    });
    connect(attackTimer,&QTimer::timeout,this,&Archer::attack);
    aimTimer->start(10);
    attackTimer->start(attackSpeed);    // 根据攻击速度设置定时器间隔
}

void Archer::attack()
{
    if(target)
    {
        if (this->collidesWithItem(target)) {
            qDebug() << "Collision detected!";


            // 获取塔的位置
            QPointF towerPos = this->pos();
            // 获取目标的位置
            qreal bulletX = towerPos.x() +towerSize/2;
            qreal bulletY = towerPos.y() +towerSize/2;
            QPointF bulletStartPos(bulletX, bulletY);

            // 创建并发射投掷物
            Projectile * bullet=nullptr ;
            assert(1<=level&&level<=2);
            if (level==1)
            {
                bullet = new Projectile(bulletStartPos,TowerCentral,attackRange);
            }
            else if(level==2)
            {
                bullet = new FireArrow(bulletStartPos,TowerCentral,attackRange);
            }
            if(bullet)
            {
                projectileList.push_back(bullet);

                connect(bullet, &Projectile::destroy, this, [this, bullet]() {
                    projectileList.removeOne(bullet);  // 从列表中移除该子弹
                });
                bullet->setTarget(target);
                scene()->addItem(bullet);
            }


        }
        else {
            qDebug() << "No collision.";
        }

    }
    else
    {
        qDebug()<<"敌人无效";
    }
}

void Archer::upgrade()
{
    if(level>=2)
    {
        return;
    }
    level++;
    attackRange+=100;
    attackSpeed+=100;
    update();
}
