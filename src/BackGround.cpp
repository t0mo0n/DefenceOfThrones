#include "BackGround.h"

BackGround::BackGround(QString backgroundPath,QGraphicsObject* parent)
    :backgroundPath(backgroundPath)
{
    backgroundPixmap.load(backgroundPath);
}

QRectF BackGround::boundingRect() const
{
    return QRectF(0,0,1200,800);
};

void BackGround::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(0,0,backgroundPixmap);
}
