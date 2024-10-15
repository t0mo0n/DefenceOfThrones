#ifndef STONETHROWER_H
#define STONETHROWER_H

#include <QObject>
#include <TowerFrame.h>
#include <Stone.h>
class StoneThrower :public TowerFrame
{
    Q_OBJECT
public:
    explicit StoneThrower(QPoint pos_=QPoint(0,0));
    void attack()override;
    QTimer *attackTimer;
    ~StoneThrower(){attackTimer->stop(); delete attackTimer;};
    void upgrade()override;
    void checkForItemsInBoundingRect()override;
    // void FindEnemy()override;


signals:
};

#endif // STONETHROWER_H
