#ifndef NIGHTKING_H
#define NIGHTKING_H
#include"Enemy.h"
#include"Deadalive.h"
class NightKing:public Enemy
{
public:
    QTimer* timer;
public:
    NightKing(const QVector<QPoint>& routine_, QGraphicsItem *parent = nullptr);
    //生成异鬼士兵
    void generate();
    void enemyPause(){moveTimer->stop();timer->stop();}
    void enemyResume(){moveTimer->start();timer->start();};
signals:
    void generateDeadalive(QPoint pos_);
};

#endif // NIGHTKING_H
