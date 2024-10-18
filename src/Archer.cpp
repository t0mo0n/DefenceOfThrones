#include "Archer.h"

Archer::Archer(QPoint pos_)
    : TowerFrame(pos_, 1)
{
    projectType = 0;
    attackRange = 3*towerSize;
    attackSpeed = 1500;
    buyCost = 1000;
    sellPrice = 900;
    picDir = ":/img/asset/1.png";
    towerType = 1;

    upgradeFee.push_back(1000);
    upgradeFee.push_back(2000);
    upgradeFee.push_back(3000);

    attackTimer->start(attackSpeed); // 根据攻击速度设置定时器间隔
}

void Archer::attack()
{
    if (target)
    {
        if (this->collidesWithItem(target))
        {

            // 获取塔的位置
            QPointF towerPos = this->pos();
            // 获取目标的位置
            qreal bulletX = towerPos.x() + towerSize / 2;
            qreal bulletY = towerPos.y() + towerSize / 2;
            QPointF bulletStartPos(bulletX, bulletY);

            // 创建并发射投掷物
            Projectile *bullet = nullptr;
            assert(1 <= level && level <= 2);
            if (level == 1)
            {
                bullet = new Projectile(bulletStartPos, TowerCentral, attackRange);
            }
            else if (level == 2)
            {
                bullet = new FireArrow(bulletStartPos, TowerCentral, attackRange);
            }
            if (bullet)
            {
                projectileList.push_back(bullet);

                connect(bullet, &Projectile::outrange, this, [this, bullet]()
                        {
                    projectileList.removeOne(bullet);  // 从列表中移除该子弹
                    scene()->removeItem(bullet);
                    delete bullet; });
                bullet->setTarget(target);
                scene()->addItem(bullet);
            }
        }
        else
        {

            resetTarget();
        }
    }
}

void Archer::upgrade()
{
    if (level >= 2)
    {
        return;
    }
    level++;
    attackRange += 2*towerSize;
    attackSpeed -= 500;
    projectType = 1;
    update();
}

void Archer::FindEnemy()
{
    if (target != nullptr)
    {
        // 获取塔的位置
        QPointF towerPos = this->pos();
        // 获取目标的位置
        QPointF targetPos = target->pos();

        // 计算方向
        qreal angle = std::atan2(targetPos.y() - towerPos.y(), targetPos.x() - towerPos.x());

        // 设置塔的旋转（如果需要旋转显示）
        setRotation(angle * 180.0 / M_PI); // 将弧度转换为度
    }
    if (target == nullptr)
    {
        // qDebug()<<"tower攻击的目标无效";
        QList<QGraphicsItem *> itemsInBoundingRect = checkForItemsInBoundingRect();

        if (!itemsInBoundingRect.isEmpty())
        {
            Enemy *min_item = nullptr;
            qreal min_distance = attackRange;
            for (auto *item : itemsInBoundingRect)
            {
                Enemy *enemy_p = dynamic_cast<Enemy *>(item);
                if (enemy_p == nullptr)
                {
                    continue;
                }
                qreal distance = QLineF(QPointF(enemy_p->pos().x() + enemy_p->size / 2, enemy_p->pos().y() + enemy_p->size / 2), this->TowerCentral).length() - 10;
                if (distance <= min_distance)
                {
                    min_item = enemy_p;
                }
            }
            if (min_item)
            {
                // qDebug()<<"设置新目标";
                setTarget(min_item);
            }
        }
        else
        {
            resetTarget();
        }
    }
}
