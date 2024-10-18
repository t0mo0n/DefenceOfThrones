#include "Wolf.h"


Wolf::Wolf(QPointF pos,QPointF Tower_c,qreal attack_range)
    :Projectile(pos,Tower_c,attack_range)
{
    src=":/img/asset/2.png";
    type=3;
    damage=60;
}
