#include "JohnSnow.h"
// 还没有添加友军增益效果
JohnSnow::JohnSnow(QPoint pos_)
    : TowerFrame(pos_, 3)
{
    projectType = 10; // 没有投掷物
    attackRange = 1.5*towerSize;
    attackSpeed = 1500;
    attackTime = 0;
    buyCost = 280;
    sellPrice .push_back( 200);
    sellPrice .push_back( 420);
    picDir = ":/img/asset/JohnSnow.png";
    towerType = 3;
    hurt = 25;
    hurt2=35;
    upgradeFee=750;

    attackTimer->start(attackSpeed);
}

void JohnSnow::FindEnemy()
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
        qreal targetAngle= (angle * 180.0) / M_PI; // 将弧度转换为度

        // 获取当前角度
        qreal currentAngle = rotation();

        // 插值计算，控制转动的速度。0.1 表示转动速度，可以根据需要调整这个系数
        qreal rotationSpeed = 0.08;
        qreal newAngle = currentAngle + rotationSpeed * (targetAngle - currentAngle);

        // 设置新的旋转角度
        setRotation(newAngle);
    }
    if (target == nullptr||target->isEnemy()==false)
    {
        // qDebug()<<"tower攻击的目标无效";
        QList<QGraphicsItem *> itemsInBoundingRect = checkForItemsInBoundingRect();

        if (!itemsInBoundingRect.isEmpty())
        {
            Enemy* ob=nullptr;
            Enemy *min_item = nullptr;
            qreal min_distance = attackRange;
            for (auto *item : itemsInBoundingRect)
            {
                Enemy *enemy_p = dynamic_cast<Enemy *>(item);
                if (enemy_p != nullptr)
                {
                    if(enemy_p->isEnemy()==true)
                    {
                        qreal distance = QLineF(QPointF(enemy_p->pos().x() + enemy_p->size / 2, enemy_p->pos().y() + enemy_p->size / 2), this->TowerCentral).length() - 10;
                        if (distance <= min_distance)
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
                connect(this, &JohnSnow::snowAttack, target, &Enemy::receiveSnow);
            }
            else if(min_item==nullptr&&ob!=nullptr)
            {
                setTarget(ob);
                connect(this, &JohnSnow::snowAttack, ob, &Enemy::receiveSnow);
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
}

void JohnSnow::attack()
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
            Wolf *bullet = nullptr;

            assert(1 <= level && level <= 2);
            if(level==1)
            {
                emit snowAttack(hurt);

            }
            else
            {
                emit snowAttack(hurt2);
            }
            attackTime++;

            if (level == 2 && attackTime % 4 == 0)
            {
                bullet = new Wolf(bulletStartPos, TowerCentral, attackRange);
                if (bullet)
                {
                    projectileList.push_back(bullet);

                        bullet->setDire0();

                    connect(bullet, &Projectile::outrange, this, [this, bullet]()
                            {
                        projectileList.removeOne(bullet);  // 从列表中移除该子弹
                        scene()->removeItem(bullet);
                        delete bullet; });
                    bullet->setTarget(target);
                    scene()->addItem(bullet);
                }
            }
        }
        else
        {
            disconnect(this, &JohnSnow::snowAttack, target, &Enemy::receiveSnow);
            resetTarget();
        }
    }
}

void JohnSnow::upgrade()
{
    if (level >= 2)
    {
        return;
    }
    level++;
    attackSpeed = 800;
    projectType = 3;
    update();
}
