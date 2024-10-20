#ifndef MELISANDRE_H
#define MELISANDRE_H
#include "Enemy.h"
class Melisandre:public Enemy
{
private:
    bool use;
    int reviveHealth;
public:
    Melisandre(const QVector<QPoint>& routine_, QGraphicsItem *parent = nullptr);
    void takeDamage(int damage_) override;
};

#endif // MELISANDRE_H
