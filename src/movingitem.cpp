#include "MovingItem.h"

MovingItem::MovingItem()
    : QGraphicsEllipseItem(0, 0, 30, 30)
{
    setBrush(Qt::blue);
}


void MovingItem::moveItem(){
    // 每次移动10个像素
    setPos(x() + 10, y());

}
