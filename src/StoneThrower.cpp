#include "StoneThrower.h"

StoneThrower::StoneThrower(QPoint pos_)
    : TowerFrame(pos_, 2)
{
    projectType = 2;
    attackRange = 5*towerSize;
    attackSpeed = 3000;
    buyCost = 350;
    sellPrice .push_back( 220);
    sellPrice .push_back( 450);

    picDir = ":/img/asset/GOT.jpg";
    towerType = 2;

    upgradeFee=420;


    attackTimer->start(attackSpeed); // 根据攻击速度设置定时器间隔
}

void StoneThrower::attack()
{

    if (level == 1)
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
                assert(1 <= level && level <= 2);

                Stone *bullet = new Stone(bulletStartPos, TowerCentral, attackRange);

                if (bullet)
                {
                    projectileList.push_back(bullet);
                    connect(bullet, &Projectile::collision, target, &Enemy::receive);

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
    else
    {
        if (target)
        {
            // 获取塔的位置
            QPointF towerPos = this->pos();
            // 获取目标的位置
            qreal bulletX = towerPos.x() + towerSize / 2;
            qreal bulletY = towerPos.y() + towerSize / 2;
            QPointF bulletStartPos(bulletX, bulletY);

            // 创建并发射投掷物
            assert(1 <= level && level <= 2);

            Stone *bullet1 = new Stone(bulletStartPos, TowerCentral, attackRange);
            Stone *bullet2 = new Stone(bulletStartPos, TowerCentral, attackRange);
            Stone *bullet3 = new Stone(bulletStartPos, TowerCentral, attackRange);

            if (bullet1)
            {
                smallBullet.push_back(bullet1);
                projectileList.push_back(bullet1);
            }
            if (bullet2)
            {
                smallBullet.push_back(bullet2);
                projectileList.push_back(bullet2);
            }
            if (bullet3)
            {
                smallBullet.push_back(bullet3);
                projectileList.push_back(bullet2);
            }
            int enemyNum = enemyList.length();
            if(target->isEnemy()==true)
            {
                assert(enemyNum > 0);
            }
            int count = 0;
            for (auto bullet : smallBullet)
            {
                if(target->isEnemy()==true)
                {
                    if (enemyNum >= 3)
                    {
                        connect(bullet, &Projectile::collision, enemyList.front(), &Enemy::receive);
                        bullet->setTarget(enemyList.front());
                        enemyList.pop_front();
                    }
                    else if (enemyNum == 2)
                    {
                        if (count == 0)
                        {
                            connect(bullet, &Projectile::collision, enemyList.front(), &Enemy::receive);
                            bullet->setTarget(enemyList.front());
                            enemyList.pop_front();
                        }
                        else
                        {
                            connect(bullet, &Projectile::collision, enemyList.front(), &Enemy::receive);
                            bullet->setTarget(enemyList.front());
                        }
                    }
                    else if (enemyNum == 1)
                    {
                        connect(bullet, &Projectile::collision, enemyList.front(), &Enemy::receive);
                        bullet->setTarget(enemyList.front());
                    }
                }
                else
                {
                    connect(bullet, &Projectile::collision, target, &Enemy::receive);
                    bullet->setTarget(target);
                }

                connect(bullet, &Projectile::outrange, this, [this, bullet]()
                        {
                        projectileList.removeOne(bullet);  // 从列表中移除该子弹
                        scene()->removeItem(bullet);
                        delete bullet; });

                scene()->addItem(bullet);
                count++;
            }
            smallBullet.clear(); // 会不会把投掷物也一起析构了？
            enemyList.clear();
        }
        else
        {
            resetTarget();
        }
    }
}

void StoneThrower::upgrade()
{
    if (level >= 2)
    {
        return;
    }
    level++;
    attackRange += 1*towerSize;
    attackSpeed -= 1000;
    projectType = 1;
    update();
}

void StoneThrower::FindEnemy()
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

    QList<QGraphicsItem *> itemsInBoundingRect = checkForItemsInBoundingRect();
    if (level == 1)
    {
        if (!itemsInBoundingRect.isEmpty())
        {
            Enemy *ob=nullptr;
            Enemy *min_item = nullptr;
            qreal min_distance = attackRange;
            for (auto *item : itemsInBoundingRect)
            {
                Enemy *enemy_p = dynamic_cast<Enemy *>(item);
                if (enemy_p == nullptr || std::find(enemyList.begin(), enemyList.end(), enemy_p) != enemyList.end())
                {
                    continue;
                }
                if(enemy_p!=nullptr)
                {
                    if(enemy_p->isEnemy()==true)
                    {
                        qreal distance = QLineF(enemy_p->pos(), this->pos()).length();
                        if (distance < min_distance)
                        {
                            min_item = enemy_p;
                        }
                    }
                    else
                    {
                        ob=enemy_p;
                    }
                }

            }
            if (min_item)
            {
                setTarget(min_item);
            }

            else if(min_item==nullptr&&ob!=nullptr)
            {
                setTarget(ob);
            }
            else
            {
                resetTarget();
            }
        }
        else
        {
            resetTarget();
        }
    }
    else
    {
        enemyList.clear();
        assert(enemyList.isEmpty());
        Enemy* ob=nullptr;
        if (!itemsInBoundingRect.isEmpty())
        {
            for (auto *item : itemsInBoundingRect)
            {
                Enemy *enemy_p = dynamic_cast<Enemy *>(item);
                if (enemy_p != nullptr)
                {
                    if(enemy_p->isEnemy()==true)
                    {
                        qreal distance = QLineF(enemy_p->pos(), this->pos()).length();
                        if (distance <= attackRange + 25)
                        {
                            connect(enemy_p, &Enemy::destroy, this, [this, enemy_p]()
                                    {
                                        enemyList.removeOne(enemy_p);/*敌人类中是否会自己调用removescene？？*/ });
                            enemyList.push_back(enemy_p);
                        }
                    }
                    else
                    {
                        ob=enemy_p;
                    }

                }
            }
        }
        if (!enemyList.isEmpty())
        {
            setTarget(enemyList.front());
        }
        else if (enemyList.isEmpty())
        {
            resetTarget();
            if(ob)
                setTarget(ob);
        }
    }
}
