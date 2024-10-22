#include "DragonBall.h"


DragonBall::DragonBall(QPointF pos,QPointF Tower_c,qreal attack_range)
    :Projectile(pos,Tower_c,attack_range)
{
    // qDebug() << "create a ball" << pos;
    src=":/img/asset/FireBall.png";
    type=4;
    pix_size_w=20;
    pix_size_h=20;
    damage=50;
}
