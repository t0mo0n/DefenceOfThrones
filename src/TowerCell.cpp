#include "TowerCell.h"

TowerCell::TowerCell(QPoint cellPos, QGraphicsObject* parent )
    :QGraphicsObject(parent)
{
    cellPixmap.load(":/img/asset/GOT.jpg");
    this->cellPos = cellPos;
}

QRectF TowerCell::boundingRect() const
{
    return QRectF(cellPos.x(),cellPos.y(),80,80);
}

void TowerCell::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    painter->drawPixmap(boundingRect(),cellPixmap,cellPixmap.rect());
}

void TowerCell::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    emit clicked(cellPos);
    event->accept();
}

