#ifndef WILDER_H
#define WILDER_H

#include"Enemy.h""
class Wilder:public Enemy
{
public:
    Wilder(const QVector<QPoint>& routine_, QGraphicsItem *parent = nullptr);
};

#endif // WILDER_H
