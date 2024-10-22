#include "FireArrow.h"

FireArrow::FireArrow(QPointF pos,QPointF Tower_c,qreal attack_range)
    :Projectile(pos,Tower_c,attack_range)
{
    src=":/img/asset/FireArrow.png";
    type=1;
    damage=15;
    pix_size_h=20;
    pix_size_w=45;
}
