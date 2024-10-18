#include "TowerCell.h"

TowerCell::TowerCell(QPoint cellPos, QGraphicsObject* parent )
    :QGraphicsObject(parent)
{
    cellPixmap.load("路径");
    this->cellPos = cellPos;
}

QRectF TowerCell::boundingRect() const
{
    return QRectF(cellPos.x(),cellPos.y(),80,80);
}

void TowerCell::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    painter->drawPixmap(0,0,cellPixmap);
}

void TowerCell::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    emit clicked(cellPos);
    event->accept();
}

