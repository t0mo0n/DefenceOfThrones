#ifndef DEADALIVE_H
#define DEADALIVE_H

#include "Enemy.h"
class DeadAlive:public Enemy
{
public:
    DeadAlive(const QVector<QPoint>& routine_, QGraphicsItem *parent = nullptr);
};

#endif // DEADALIVE_H
