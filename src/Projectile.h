#ifndef PROJECTILE_H
#define PROJECTILE_H
#pragma once

#include <QObject>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QString>
#include <QPainter>
#include <QTimer>
#include <QLine>
#include <Enemy.h>
#include <QElapsedTimer>

class Projectile : public QObject, public QGraphicsItem
{
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)
public:
    explicit Projectile(QPointF pos, QPointF Tower_c, qreal attack_range);
    void setTarget(Enemy *enemy_ = nullptr); // 在进攻时会自己调用
    virtual void moveToEneny();
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    virtual QRectF boundingRect() const override;
    qreal pix_size_w;
    qreal pix_size_h;
    // void outOfRange();//删除超过攻击范围的子弹
    int getType() { return type; }; // 获得投掷物的类型 0 普通子弹 1 火箭 2 石头 3 狼 4 龙火焰弹 5 龙焰
    int getDamage() { return damage; };
    void checkCollision();
    ~Projectile();
    Enemy *enemys;
    virtual void pause();
    virtual void resume();
    virtual void setDire0();
    QElapsedTimer*elapsedTimer;

protected:
    int type;
    int speed;
    int damage;
    QString src; // 投掷物的图片
    QPointF delta;
    QTimer *moveTimer;
    QPointF towerCor;
    qreal tattackRange;
    QTimer *moveTimer2;
    qreal remainingTime1;
    qreal remainingTime2;
    qreal anangle;

signals:
    void destroy();
    void outrange();
    void collision(int damage_, int type_);
};

#endif // PROJECTILE_H
