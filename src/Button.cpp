#include <QStyleOptionGraphicsItem>
#include <QGraphicsSceneMouseEvent>
#include "Button.h"

Button::Button(QString UnHoverImagePath, QString HoverImagePath,int posX,int posY, int inTowerSelect,QGraphicsObject *parent)
    : QGraphicsObject(parent), inTowerSelect(inTowerSelect)
{
    this->UnHoverImagePath = UnHoverImagePath;
    this->HoverImagePath = HoverImagePath;
    this->posX = posX;
    this->posY = posY;
    UnHoverImage.load(UnHoverImagePath);
    HoverImage.load(HoverImagePath);
    setAcceptHoverEvents(true);
}

QRectF Button::boundingRect() const
{
    return QRectF(posX,posY,100,100);
}

void Button::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if(inTowerSelect ==0)
    {
        if(option->state & QStyle::State_MouseOver)
        {
            painter->drawPixmap(boundingRect(),HoverImage,HoverImage.rect());
        }
        else
        {
            painter->drawPixmap(boundingRect(),UnHoverImage,UnHoverImage.rect());
        }
    }
    else if(inTowerSelect == -1)
    {
        painter->drawPixmap(boundingRect(),UnHoverImage,UnHoverImage.rect());
    }
    else if(inTowerSelect == 1)
    {
        painter->drawPixmap(boundingRect(),HoverImage,HoverImage.rect());
    }

}

void Button::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    update();
    event->accept();
}
void Button::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    update();
    event->accept();
}
void Button::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    emit clicked();
    event->accept();
}
