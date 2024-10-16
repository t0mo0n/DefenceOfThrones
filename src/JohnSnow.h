#ifndef JOHNSNOW_H
#define JOHNSNOW_H

#include <QObject>
#include <TowerFrame.h>

class JohnSnow : public TowerFrame
{
    Q_OBJECT
public:
    explicit JohnSnow(QPoint pos_=QPoint(0,0));
    void attack()override;
    void FindEnemy()override;
signals:
};

#endif // JOHNSNOW_H
