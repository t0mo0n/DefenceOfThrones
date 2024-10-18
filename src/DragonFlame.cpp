#include "DragonFlame.h"


DragonFlame::DragonFlame(QPointF pos,QPointF Tower_c,qreal attack_range)
    :Projectile(pos,Tower_c,attack_range)
{
    src=":/img/asset/GOT.jpg";
    type=5;
    damage=2000;
    w_=100;
    h_=400;
    moveTimer->stop();
    moveTimer2->stop();
    flameTimer=new QTimer(this);
    die=new QTimer(this);
    connect(flameTimer, &QTimer::timeout, this, &DragonFlame::detect);
    flameTimer->start(10);
    connect(die, &QTimer::timeout, this, [this](){emit outrange();});
    die->start(300);
    setTarget();//不要接collision，换成detect，并且已经链接，不用移动，不用检测碰撞，敌人是null所以消亡信号不接
    setTransformOriginPoint(QPointF(w_/2,0));

}
void DragonFlame:: paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    if(src==nullptr)
    {
        qDebug()<<"projectile pix error";
    }
    if(painter)
    {

        painter->drawPixmap(QRect(0-w_/2,0,w_,h_),QPixmap(src)); // 绘制激光
    }


}
QRectF DragonFlame::boundingRect() const
{
    return QRectF(0,0,w_,h_);
}

void DragonFlame::detect()
{
        QRectF sceneBoundingRect = mapRectToScene(boundingRect());

        QList<QGraphicsItem*> itemsInBoundingRect = scene()->items(sceneBoundingRect);

        itemsInBoundingRect.removeOne(this);

        if (!itemsInBoundingRect.isEmpty()) {
            for (auto* item : itemsInBoundingRect) {
                Enemy* enemy_p = dynamic_cast<Enemy*>(item);
                if(enemy_p==nullptr)
                {
                    continue;
                }
                connect(this,&DragonFlame::collision,enemy_p,&Enemy::recieve);
                emit collision(damage,type);
            }
        }
        assert(enemys==nullptr);
}
void DragonFlame::setDire(qreal angle_)
{

    angle=angle_;

    // 设置塔的旋转（如果需要旋转显示）
    setRotation(angle * 180.0 / M_PI); // 将弧度转换为度
}
