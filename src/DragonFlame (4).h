#ifndef STONETHROWER_H
#define STONETHROWER_H

#include <QObject>
#include <TowerFrame.h>
#include <Stone.h>
#include <Enemy.h>
class StoneThrower : public TowerFrame
{
    Q_OBJECT
public:
    explicit StoneThrower(QPoint pos_ = QPoint(0, 0));
    void attack() override;
    ~StoneThrower() {};
    void upgrade() override;
    void FindEnemy() override;

protected:
    QList<Enemy *> enemyList;
    QList<Stone *> smallBullet;

signals:
};

#endif // STONETHROWER_H