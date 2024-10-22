#ifndef DRAGONFLAME_H
#define DRAGONFLAME_H

#include "Projectile.h"

class DragonFlame : public Projectile
{
    Q_OBJECT
public:
    DragonFlame(QPointF pos,QPointF Tower_c,qreal attack_range);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)override;
    virtual QRectF boundingRect() const override;
    void detect();
    QTimer* flameTimer;
    QTimer* die;
    qreal angle;
    void setDire(qreal angle);
    ~DragonFlame(){flameTimer->stop();delete flameTimer;die->stop();delete die;};
    void pause()override;
    void resume()override;
    qreal remainingTime3;
    qreal remainingTime4;

protected:
    int w_,h_;
};

#endif // DRAGONFLAME_H
