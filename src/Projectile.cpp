#include "Projectile.h"

Projectile::Projectile(QPointF pos, QPointF Tower_c, qreal attack_range)
{
    delta = QPointF(0, 0);
    setPos(pos);
    moveTimer = new QTimer(this);
    moveTimer2 = new QTimer(this);
    connect(moveTimer, &QTimer::timeout, this, &Projectile::moveToEneny);
    // connect(moveTimer, &QTimer::timeout, this, &Projectile::outOfRange);
    connect(moveTimer2, &QTimer::timeout, this, &Projectile::checkCollision);
    moveTimer->start(70); // 每调用一次move()
    moveTimer2->start(10);
    elapsedTimer= new QElapsedTimer();
    elapsedTimer->start();
    towerCor = Tower_c;
    src = ":/img/asset/GOT.jpg";
    speed = 20;
    tattackRange = attack_range;
    type = 0;
    damage = 10;
}
qreal Projectile::pix_size = 10;
void Projectile::setTarget(Enemy *target)
{
    enemys = target;

    if (target)
    {
        connect(target, &Enemy::destroy, this, [this]()
                { emit outrange(); });
        connect(this, &Projectile::collision, target, &Enemy::receive);
    }
}

void Projectile::moveToEneny()
{
    if (enemys != nullptr)
    {

        // 获取 projectile 的当前位置
        QPointF ProjectilePos = this->pos();
        // 获取目标 enemy 的位置
        QPointF enemyPos = enemys->pos();

        // 计算方向角度（弧度）
        qreal angle = std::atan2(enemyPos.y() - ProjectilePos.y(), enemyPos.x() - ProjectilePos.x());

        // 计算 x 和 y 的增量，基于速度
        qreal dx = speed * std::cos(angle); // x方向的速度分量
        qreal dy = speed * std::sin(angle); // y方向的速度分量

        // 更新子弹的位置
        this->setPos(ProjectilePos.x() + dx, ProjectilePos.y() + dy);
    }
    if(enemys==nullptr)
    {

        qDebug() << "攻击的目标无效" << this->pos();
        // moveTimer->stop();
        emit outrange();
        // scene()->removeItem(this);
        // delete this;  // 删除子弹对象
        // return;
        // this->setPos(this->pos().x()+delta.x(),this->pos().y()+delta.y());
    }
}

QRectF Projectile::boundingRect() const
{
    // 返回项的边界矩形
    return QRectF(0, 0, pix_size, pix_size); // 示例边界矩形
}

void Projectile::paint(QPainter *painter1, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    // 绘制项的内容
    Q_UNUSED(option);
    Q_UNUSED(widget);
    if (src == nullptr)
    {
        qDebug() << "projectile pix error";
    }
    if (painter1)
    {
        painter1->drawPixmap(QRect(0, 0, pix_size, pix_size), QPixmap(src));
    }
}

// void Projectile::outOfRange()
// {
//     qreal distance=QLineF(this->pos(),towerCor).length();

//     if(distance>tattackRange)
//     {
//         emit outrange();
//         // moveTimer->stop();
//         return;
//     }
// }

void Projectile::checkCollision()
{
    if (this->collidesWithItem(enemys))
    {
        emit collision(damage, type);
        emit outrange();
        // int enemy_type=enemys->getEnemyType();
        /*这里还有一个条件判断是不是异鬼*/
        qDebug() << "碰到敌人";
    }
}
Projectile::~Projectile()
{
    emit destroy();
    qDebug() << "projectile被消除";
    moveTimer->stop();
    moveTimer2->stop();
    delete moveTimer2;
    delete moveTimer;
}
void Projectile:: pause() {
    if (moveTimer->isActive()) {
        remainingTime1 = moveTimer->interval() - elapsedTimer->elapsed();
        moveTimer->stop();
    }

    if (moveTimer2->isActive()) {
        remainingTime2 = moveTimer2->interval() - elapsedTimer->elapsed();
        moveTimer2->stop();
    }
}

// 恢复两个计时器
void Projectile:: resume() {
    if (!moveTimer->isActive()) {
        moveTimer->start(remainingTime1);
        elapsedTimer->restart();
    }

    if (!moveTimer2->isActive()) {
        moveTimer2->start(remainingTime2);
        elapsedTimer->restart();
    }
}
