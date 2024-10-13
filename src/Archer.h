#ifndef ARCHER_H
#define ARCHER_H

#include <QObject>
#include <QGraphicsItem>
#include <TowerFrame.h>
#include <QGraphicsItemAnimation>
#include <QTimer>
#include <FireArrow.h>
#include <Projectile.h>

class Archer : public TowerFrame
{
    Q_OBJECT
public:
    explicit Archer(QPoint pos_=QPoint(0,0));
    void attack()override;
    QTimer *aimTimer;
    QTimer *attackTimer;

signals:
public slots:
    void upgrade()override;

};

#endif // ARCHER_H
