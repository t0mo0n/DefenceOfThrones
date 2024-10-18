#ifndef STONE_H
#define STONE_H

#include "Projectile.h"

class Stone : public Projectile
{
    Q_OBJECT
public:
    Stone(QPointF pos,QPointF Tower_c,qreal attack_range);
};

#endif // STONE_H
