#include "FireArrow.h"

FireArrow::FireArrow(QPointF pos,QPointF Tower_c,qreal attack_range)
    :Projectile(pos,Tower_c,attack_range)
{
    src=":/img/asset/2.png";
    type=1;
    damage=15;
}
