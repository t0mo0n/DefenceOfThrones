#ifndef TOWER1_H
#define TOWER1_H

#include <QObject>
#include <QGraphicsItem>
#include <TowerFrame.h>
#include <QGraphicsItemAnimation>
#include <QTimer>
#include <Projectile.h>

class tower1 : public Tower_frame
{
    Q_OBJECT
public:
    explicit tower1(QPoint pos_=QPoint(0,0));
    void Attack()override;
    QTimer *aimTimer;
    QTimer *attackTimer;

signals:
public slots:
    void Upgrade()override;

};

#endif // TOWER1_H
