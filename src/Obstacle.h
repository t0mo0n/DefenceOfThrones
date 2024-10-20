#ifndef OBSTACLE_H
#define OBSTACLE_H

#include <QWidget>
#include <QGraphicsItem>
#include<QPixmap>
#include<QPoint>
#include<QPainter>
#include"Enemy.h"
class Obstacle : public Enemy
{
    Q_OBJECT
private:
    int type;
    QPoint pos;

public:
    explicit Obstacle(int type_,QVector<QPoint> routine_, QGraphicsItem *parent = nullptr);
    void takeDamage  (int damage_) override;//击碎发出信号
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    // 绘制障碍物
    bool isEnemy() override {return false;}
    ~Obstacle(){emit destory();}

signals:
    void isDamaged(int price,Obstacle *toBeDelete);
    void destory();
public slots:
    void receive(int damage_,int type);//可能有bug
};

#endif // OBSTACLE_H



