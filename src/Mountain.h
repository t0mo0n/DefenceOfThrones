#ifndef MOUNTAIN_H
#define MOUNTAIN_H
#include"Enemy.h"
class Mountain:public Enemy
{
public:
    Mountain(const QVector<QPoint>& routine_, QGraphicsItem *parent = nullptr);
};

#endif // MOUNTAIN_H
