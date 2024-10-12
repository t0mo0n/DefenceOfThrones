#include "Projectile.h"

Projectile::Projectile(QPointF pos)
{
    delta=QPointF(0,0);
    setPos(pos);
    moveTimer = new QTimer(this);
    connect(moveTimer, &QTimer::timeout, this, &Projectile::MoveToEneny);
    moveTimer->start(100); // 每50ms调用一次move()

    src=":/img/asset/GOT.jpg";
    speed=10;
}
qreal Projectile::pix_size=10;
void Projectile::SetTarget(QGraphicsItem * target)
{
    enemys=target;
}

void Projectile::MoveToEneny()
{
    if (enemys!=nullptr) {
        // 获取projectile的位置
        QPointF ProjectilePos = this->pos();
        // 获取目标的位置
        QPointF enemyPos = enemys->pos();

        qreal rate = (enemyPos.y() - ProjectilePos.y())/ (enemyPos.x() - ProjectilePos.x());
        qreal dx = speed  ;
        qreal dy = dx * rate ;
        delta=QPointF(dx,dy);
        this->setPos(ProjectilePos.x()+delta.x(),ProjectilePos.y()+delta.y());
    }
    else
    {
        qDebug()<<"攻击的目标无效";

        this->setPos(this->pos().x()+delta.x(),this->pos().y()+delta.y());
    }
}

QRectF Projectile:: boundingRect() const
{
    // 返回项的边界矩形
    return QRectF(0, 0, 10, 10); // 示例边界矩形
}

void Projectile::paint(QPainter *painter1, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    // 绘制项的内容
    Q_UNUSED(option);
    Q_UNUSED(widget);
    if(src==nullptr)
    {
        qDebug()<<"projectile pix error";
    }
    painter1->drawPixmap(QRect(0,0,pix_size,pix_size),QPixmap(src));
}
