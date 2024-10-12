#include "Tower1.h"

tower1::tower1(QPoint pos_)
    :Tower_frame(pos_,1)
{
    project_Type=0;
    attack_range=150;
    attack_speed=800;
    buy_cost=1000;
    sellPrice=900;
    pic_dir=":/img/asset/3.png";

    upgrade_fee.push_back(1000);
    upgrade_fee.push_back(2000);
    upgrade_fee.push_back(3000);
    aimTimer=new QTimer(this);
    attackTimer=new QTimer(this);

    connect(aimTimer, &QTimer::timeout, this, [this](){
        FindEnemy();
    });
    connect(attackTimer,&QTimer::timeout,this,&tower1::Attack);
    aimTimer->start(10);
    attackTimer->start(attack_speed);    // 根据攻击速度设置定时器间隔
}

void tower1::Attack()
{
    if(target)
    {
        if (this->collidesWithItem(target)) {
            qDebug() << "Collision detected!";


            // 获取塔的位置
            QPointF towerPos = this->pos();
            // 获取目标的位置
            qreal bulletX = towerPos.x() +tower_size/2;
            qreal bulletY = towerPos.y() +tower_size/2;
            QPointF bulletStartPos(bulletX, bulletY);

            // 创建并发射投掷物
            Projectile * bullet = new Projectile(bulletStartPos,TowerCentral,attack_range);
            projectile_list.push_back(bullet);
            bullet->SetTarget(target);
            scene()->addItem(bullet);

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

void tower1::Upgrade()
{
    level++;
    attack_range+=100;
    attack_speed+=100;
}
