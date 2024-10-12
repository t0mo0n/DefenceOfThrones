#include "MovingItem.h"

MovingItem::MovingItem()
    : QGraphicsEllipseItem(0, 0, 30, 30)
{
    setBrush(Qt::blue);
    count=0;
}


void MovingItem::moveItem(){

    if(count<80)
    {
        // 每次移动10个像素
        setPos(x() + 10, y());
        count++;
    }
    else
    {
        scene()->removeItem(this);
        delete this;
    }


}

