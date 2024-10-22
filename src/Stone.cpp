#include "Stone.h"

Stone::Stone(QPointF pos,QPointF Tower_c,qreal attack_range)
    :Projectile(pos,Tower_c,attack_range)
{
    src=":/img/asset/stone.png";
    type=2;
    pix_size_w=40;
    pix_size_h=40;
    damage=35;
}
