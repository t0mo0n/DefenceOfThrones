#ifndef DRAGON_H
#define DRAGON_H

#include <QObject>
#include <TowerFrame.h>
#include <DragonBall.h>
#include <DragonFlame.h>

class Dragon : public TowerFrame
{
    Q_OBJECT
public:
    explicit Dragon(QPoint pos_ = QPoint(0, 0));
    void attack() override;
    ~Dragon() {};
    void upgrade() override;
    void FindEnemy() override;
    QList<Enemy *> enemyList;
    QList<DragonBall *> smallBullet;
protected:

signals:
};

#endif // DRAGON_H
