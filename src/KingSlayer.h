#ifndef KINGSLAYER_H
#define KINGSLAYER_H
#include"Enemy.h"
class KingSlayer:public Enemy
{
public:
    KingSlayer(const QVector<QPoint>& routine_, QGraphicsItem *parent = nullptr);
};

#endif // KINGSLAYER_H
