#ifndef WOLF_H
#define WOLF_H

#include "Projectile.h"

class Wolf : public Projectile
{
    Q_OBJECT
public:
    Wolf(QPointF pos, QPointF Tower_c, qreal attack_range);
};

#endif // WOLF_H