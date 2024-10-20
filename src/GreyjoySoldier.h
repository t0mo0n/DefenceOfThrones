#ifndef GREYJOYSOLDIER_H
#define GREYJOYSOLDIER_H

#include"Enemy.h"
class GreyjoySoldier:public Enemy
{
public:
    GreyjoySoldier(const QVector<QPoint>& routine_, QGraphicsItem *parent = nullptr);
};

#endif // GREYJOYSOLDIER_H
