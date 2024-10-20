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
    return QRectF(posX,posY,UnHoverImage.width(),HoverImage.height());
}

void Button::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if(inTowerSelect ==0)
    {
        if(option->state & QStyle::State_MouseOver)
        {
            painter->drawPixmap(0,0,HoverImage);
        }
        else
        {
            painter->drawPixmap(0,0,UnHoverImage);
        }
    }
    else if(inTowerSelect == -1)
    {
        painter->drawPixmap(0,0,UnHoverImage);
    }
    else if(inTowerSelect == 1)
    {
        painter->drawPixmap(0,0,HoverImage);
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
