#ifndef VESALION_H
#define VESALION_H
#include"Enemy.h"
class Vesalion:public Enemy
{
public:
    Vesalion(const QVector<QPoint>& routine_, QGraphicsItem *parent = nullptr);
};

#endif // VESALION_H
