#include "Tower1.h"

tower1::tower1(QPoint pos_)
    :Tower_frame(pos_,1)
{
    project_Type=0;
    attack_range=300;
    attack_speed=1000;
    buy_cost=1000;
    sellPrice=900;
    pic_dir=":/img/asset/3.png";

    upgrade_fee.push_back(1000);
    upgrade_fee.push_back(2000);
    upgrade_fee.push_back(3000);
    aimTimer=new QTimer(this);

    connect(aimTimer, &QTimer::timeout, this, [this](){
        Findenemy();
    });
    aimTimer->start(10); // 根据攻击速度设置定时器间隔
}

void tower1::Attack()
{
    if (target!=nullptr) {
        // 获取塔的位置
        QPointF towerPos = this->pos();
        // 获取目标的位置
        qreal bulletX = towerPos.x() +tower_size/2;
        qreal bulletY = towerPos.y() +tower_size/2;
        QPointF bulletStartPos(bulletX, bulletY);

        // 创建并发射子弹
        Projectile * bullet = new Projectile(bulletStartPos);
        bullet->SetTarget(target);
        scene()->addItem(bullet);

    }
    else
    {
        qDebug()<<"tower攻击的目标无效";
    }
}
void tower1::Upgrade()
{
    level++;
    attack_range+=100;
    attack_speed+=100;
}
