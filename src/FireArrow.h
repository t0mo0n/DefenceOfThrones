#ifndef FIREARROW_H
#define FIREARROW_H

#include "Projectile.h"

class FireArrow : public Projectile
{
    Q_OBJECT
public:
    FireArrow(QPointF pos,QPointF Tower_c,qreal attack_range);
};

#endif // FIREARROW_H
