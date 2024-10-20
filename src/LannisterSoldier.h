#ifndef LANNISTERSOLDIER_H
#define LANNISTERSOLDIER_H
#include"Enemy.h"
class LannisterSoldier:public Enemy
{
public:
    LannisterSoldier(const QVector<QPoint>& routine_, QGraphicsItem *parent = nullptr);
};

#endif // LANNISTERSOLDIER_H
