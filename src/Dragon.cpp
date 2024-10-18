#include "Dragon.h"

Dragon::Dragon(QPoint pos_)
    : TowerFrame(pos_, 2)
{
    projectType = 4;
    attackRange = 200;
    attackSpeed = 4000;
    buyCost = 1500;
    sellPrice = 900;
    picDir = ":/img/asset/GOT.jpg";
    towerType = 4;

    upgradeFee.push_back(2000);
    upgradeFee.push_back(3000);
    upgradeFee.push_back(4000);

    attackTimer->start(attackSpeed); // 根据攻击速度设置定时器间隔
}

void Dragon::attack()
{
    if (level == 1)
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

            DragonBall *bullet1 = new DragonBall(bulletStartPos, TowerCentral, attackRange);
            DragonBall *bullet2 = new DragonBall(bulletStartPos, TowerCentral, attackRange);

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

            int enemyNum = enemyList.length();
            assert(enemyNum > 0);
            for (auto bullet : smallBullet)
            {
                if (enemyNum >= 2)
                {
                    connect(bullet, &Projectile::collision, enemyList.front(), &Enemy::receive);
                    bullet->setTarget(enemyList.front());
                    enemyList.pop_front();
                }
                else if (enemyNum == 1)
                {
                    connect(bullet, &Projectile::collision, enemyList.front(), &Enemy::receive);
                    bullet->setTarget(enemyList.front());
                }

                connect(bullet, &Projectile::outrange, this, [this, bullet]()
                        {
                    projectileList.removeOne(bullet);  // 从列表中移除该子弹
                    scene()->removeItem(bullet);
                    delete bullet; });

                scene()->addItem(bullet);
            }
            smallBullet.clear(); // 会不会把投掷物也一起析构了？
            enemyList.clear();
        }
        else
        {
            resetTarget();
        }
    }
    else if (level == 2)
    {
        // 获取塔的位置
        QPointF towerPos = this->pos();
        // 获取目标的位置
        qreal bulletX = towerPos.x() + towerSize / 2;
        qreal bulletY = towerPos.y() + towerSize / 2;
        QPointF bulletStartPos(bulletX, bulletY);

        // 创建并发射投掷物
        assert(1 <= level && level <= 2);

        DragonFlame *bullet = new DragonFlame(bulletStartPos, TowerCentral, attackRange);

        if (bullet)
        {
            projectileList.push_back(bullet);
            bullet->setDire(towerAngle);
            connect(bullet, &DragonFlame::outrange, this, [this, bullet]()
                    {
                projectileList.removeOne(bullet);  // 从列表中移除该子弹
                scene()->removeItem(bullet);
                delete bullet; });
            scene()->addItem(bullet);
            update();
            assert(bullet->enemys == nullptr);
        }
    }
}

void Dragon::upgrade()
{
    if (level >= 2)
    {
        return;
    }
    level++;
    attackRange += 100;
    attackSpeed += 100;
    projectType = 5;
    update();
}

void Dragon::FindEnemy()
{
    if (target != nullptr)
    {
        // 获取塔的位置
        QPointF towerPos = this->pos();
        // 获取目标的位置
        QPointF targetPos = target->pos();

        // 计算方向
        qreal angle = std::atan2(targetPos.y() - towerPos.y(), targetPos.x() - towerPos.x());
        towerAngle = angle;
        // 设置塔的旋转（如果需要旋转显示）
        setRotation(angle * 180.0 / M_PI); // 将弧度转换为度
    }
    QList<QGraphicsItem *> itemsInBoundingRect = checkForItemsInBoundingRect();

    if (!itemsInBoundingRect.isEmpty())
    {
        for (auto *item : itemsInBoundingRect)
        {
            Enemy *enemy_p = dynamic_cast<Enemy *>(item);
            if (enemy_p == nullptr)
            {
                continue;
            }
            qreal distance = QLineF(enemy_p->pos(), this->pos()).length();
            if (distance <= attackRange + 25)
            {
                connect(enemy_p, &Enemy::destroy, this, [this, enemy_p]()
                        {
                    enemyList.removeOne(enemy_p);/*敌人类中是否会自己调用removescene？？*/ });
                enemyList.push_back(enemy_p);
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
    }
}
