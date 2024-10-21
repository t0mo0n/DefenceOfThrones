#include "Projectile.h"

Projectile::Projectile(QPointF pos, QPointF Tower_c, qreal attack_range)
{
    delta = QPointF(0, 0);
    setPos(pos);
    moveTimer = new QTimer(this);
    moveTimer2 = new QTimer(this);
    connect(moveTimer, &QTimer::timeout, this, &Projectile::moveToEneny);
    connect(moveTimer, &QTimer::timeout, this, &Projectile::setDire0);
    connect(moveTimer2, &QTimer::timeout, this, &Projectile::checkCollision);
    connect(moveTimer, &QTimer::timeout, this, &Projectile::outOfRange);
    moveTimer->start(70); // 每调用一次move()
    moveTimer2->start(10);
    elapsedTimer= new QElapsedTimer();
    elapsedTimer->start();
    towerCor = Tower_c;
    src = ":/img/asset/Arrow.png";
    speed = 20;
    tattackRange = attack_range;
    type = 0;
    damage = 10;
    anangle=0;
    pix_size_h=20;
    pix_size_w=45;

    setTransformOriginPoint(QPointF(pix_size_w/2,pix_size_h/2));

    setZValue(10);
}
void Projectile::setTarget(Enemy *target)
{
    enemys = target;

    if (target)
    {
        connect(target, &Enemy::destroy, this, [this]()
                { emit outrange(); });
        qDebug()<<"bound"<<target->pos();
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
        anangle=angle;
        // 计算 x 和 y 的增量，基于速度
        qreal dx = speed * std::cos(angle); // x方向的速度分量
        qreal dy = speed * std::sin(angle); // y方向的速度分量

        // 更新子弹的位置
        this->setPos(ProjectilePos.x() + dx, ProjectilePos.y() + dy);
    }
    if(enemys==nullptr)
    {
        qDebug() << "攻击的目标无效" << this->pos();
        emit outrange();
    }
}

QRectF Projectile::boundingRect() const
{
    // 返回项的边界矩形
    return QRectF(0, 0, pix_size_w, pix_size_h); // 示例边界矩形
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
        painter1->drawPixmap(QRect(0, 0, pix_size_w, pix_size_h), QPixmap(src));
    }
}

void Projectile::outOfRange()
{
    qreal distance=QLineF(this->pos(),towerCor).length();

    if(distance>tattackRange)
    {
        emit outrange();
        // moveTimer->stop();
        return;
    }
}

void Projectile::setDire0()
{
    qreal anangle_=anangle * 180.0 / M_PI;
    // 设置塔的旋转（如果需要旋转显示）
    setRotation(anangle_); // 将弧度转换为度
}

void Projectile::checkCollision()
{
    if (this->collidesWithItem(enemys))
    {

        emit collision(damage, type);
        emit outrange();
        // int enemy_type=enemys->getEnemyType();
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
        moveTimer->stop();
    }

    if (moveTimer2->isActive()) {
        moveTimer2->stop();
    }
}

// 恢复两个计时器
void Projectile:: resume() {
    if (!moveTimer->isActive()) {
        moveTimer->start(70); // 每调用一次move()

    }

    if (!moveTimer2->isActive()) {
        moveTimer2->start(10);    }
}
