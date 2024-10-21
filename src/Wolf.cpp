#include "Wolf.h"


Wolf::Wolf(QPointF pos,QPointF Tower_c,qreal attack_range)
    :Projectile(pos,Tower_c,attack_range)
{
    src=":/img/asset/Wolf.png";
    type=3;
    pix_size_h=20;
    pix_size_w=45;
    damage=60;
}
