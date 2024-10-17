#include "Stone.h"

Stone::Stone(QPointF pos,QPointF Tower_c,qreal attack_range)
    :Projectile(pos,Tower_c,attack_range)
{
    src=":/img/asset/1.png";
    type=2;
    damage=500;
}
