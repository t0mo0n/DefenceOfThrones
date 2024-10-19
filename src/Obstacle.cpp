#include "Obstacle.h"

Obstacle::Obstacle(int type_)
    : Enemy(type_)
{
    count=0;
    type=type_;
    this->setBrush(Qt::blue);
    size=30;
}

