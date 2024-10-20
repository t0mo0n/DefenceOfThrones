#ifndef DRAGONBALL_H
#define DRAGONBALL_H

#include "Projectile.h"

class DragonBall : public Projectile
{
    Q_OBJECT
public:
    DragonBall(QPointF pos,QPointF Tower_c,qreal attack_range);
};

#endif // DRAGONBALL_H