#include "Button.h"

Button::Button(QString UnHoverImagePath, QString HoverImagePath, QGraphicsItem *parent)
    : QGraphicsItem{parent}
{
    this->UnHoverImagePath = UnHoverImagePath;
    this->HoverImagePath = HoverImagePath;
    setAcceptHoverEvents(true);

}
