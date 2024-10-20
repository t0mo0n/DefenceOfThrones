#include "PathCell.h"

PathCell::PathCell(QString pixMapPath,QPoint cellPos, QGraphicsObject* parent )
    :QGraphicsObject(parent)
{
    this->cellPos = cellPos;
    this->cellPixmap = pixMapPath;
    cellPixmap.load(pixMapPath);


}

QRectF PathCell::boundingRect() const
{
    return QRectF(cellPos.x(),cellPos.y(),80,80);
}

void PathCell::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    painter->drawPixmap(0,0,cellPixmap);
}
