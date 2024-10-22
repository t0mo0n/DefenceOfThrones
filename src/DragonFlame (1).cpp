#include "DragonFlame.h"


DragonFlame::DragonFlame(QPointF pos,QPointF Tower_c,qreal attack_range)
    :Projectile(pos,Tower_c,attack_range)
{
    src=":/img/asset/Flame.png";//:/img/asset/Flame.png
    type=5;
    damage=80;
    w_=100;
    h_=200;
    moveTimer->stop();
    moveTimer2->stop();
    flameTimer=new QTimer(this);
    die=new QTimer(this);
    connect(flameTimer, &QTimer::timeout, this, &DragonFlame::detect);
    flameTimer->start(10);
    connect(die, &QTimer::timeout, this, [this](){emit outrange();});
    die->start(500);
    setTarget();//不要接collision，换成detect，并且已经链接，不用移动，不用检测碰撞，敌人是null所以消亡信号不接
    setTransformOriginPoint(QPointF(0,0));

}
void DragonFlame:: paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    QTransform transform;
    transform.rotate(90); // 旋转90度
    if(src==nullptr)
    {
        qDebug()<<"projectile pix error";
    }
    if(painter)
    {
        painter->drawPixmap(QRect(-w_/2,0,w_,h_),QPixmap(src).transformed(transform)); // 绘制激光

    }


}
QRectF DragonFlame::boundingRect() const
{

    return QRectF(-w_/2, 0, w_, h_);  // 从旋转中心 (w_/2, 0) 计算矩形


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
        assert(enemys==nullptr);
}
void DragonFlame::setDire(qreal angle_)
{
    angle=angle_ * 180.0 / M_PI-90;
    // 设置塔的旋转（如果需要旋转显示）
    setRotation(angle ); // 将弧度转换为度
}
void DragonFlame::pause()
{

    if (flameTimer->isActive()) {
        remainingTime1 = flameTimer->interval() - elapsedTimer->elapsed();
        flameTimer->stop();
    }
    if (die->isActive()) {
        remainingTime2 = die->interval() - elapsedTimer->elapsed();
        die->stop();
    }

}
void DragonFlame::resume()
{
    if (!flameTimer->isActive()) {
        flameTimer->start(remainingTime1);
        elapsedTimer->restart();
    }
    if (!die->isActive()) {
        die->start(remainingTime2);
        elapsedTimer->restart();
    }
}
