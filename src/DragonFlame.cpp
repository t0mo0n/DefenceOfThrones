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
    die->start(1000);
    setTarget();//不要接collision，换成detect，并且已经链接，不用移动，不用检测碰撞，敌人是null所以消亡信号不接

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
        QPointF laserEnd(towerCor.x() + h_ * cos(angle * M_PI / 180.0),
                         towerCor.y() + h_ * sin(angle * M_PI / 180.0));

        // 计算激光图片的位置和大小
        QRectF laserRect(laserEnd.x() - w_ / 2,laserEnd.y() -h_/ 2,w_,h_);
        QRectF recc=mapRectFromScene(laserRect);
        // 绘制激光图片
        painter->save(); // 保存当前绘制状态
        painter->translate(towerCor); // 移动到防御塔中心
        painter->rotate(angle); // 旋转
        painter->drawPixmap(recc.toRect(),QPixmap(src)); // 绘制激光
        painter->restore(); // 恢复绘制状态
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
                connect(this,&DragonFlame::collision,enemy_p,&Enemy::receive);
                emit collision(damage,type);
            }
        }

}
void DragonFlame::setDire(qreal angle_)
{

    angle=angle_;
}
