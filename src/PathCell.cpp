#include "PathCell.h"

PathCell::PathCell(QPoint cellPos, QGraphicsObject* parent )
    :QGraphicsObject(parent)
{
    cellPixmap.load("路径");
    this->cellPos = cellPos;
}

QRectF PathCell::boundingRect() const
{
    return QRectF(cellPos.x(),cellPos.y(),80,80);
}

void PathCell::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    painter->drawPixmap(0,0,cellPixmap);
}
