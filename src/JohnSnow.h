#ifndef JOHNSNOW_H
#define JOHNSNOW_H

#include <QObject>
#include <TowerFrame.h>
#include <Wolf.h>

class JohnSnow : public TowerFrame
{
    Q_OBJECT
protected:
    int hurt;
    int hurt2;

public:
    explicit JohnSnow(QPoint pos_ = QPoint(0, 0));
    void attack() override;
    void FindEnemy() override;
    void upgrade() override;
    int attackTime;
signals:
    void snowAttack(int hurt_);
};

#endif // JOHNSNOW_H
