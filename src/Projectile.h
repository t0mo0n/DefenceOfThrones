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

class Projectile : public QObject,public QGraphicsItem
{
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)
public:
    explicit Projectile(QPointF pos,QPointF Tower_c,qreal attack_range);
    void setTarget(QGraphicsItem* Enemy=nullptr);//在进攻时会自己调用
    void moveToEneny();
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)override;
    QRectF boundingRect() const override;
    static qreal pix_size;
    void outOfRange();//删除超过攻击范围的子弹
    int getType(){return type;};//获得投掷物的类型 0 普通子弹 1 火箭

protected:
    int type;
    int speed;
    int damage;
    QString src;//投掷物的图片
    QGraphicsItem* enemys;
    QPointF delta;
    QTimer* moveTimer ;
    QPointF towerCor;
    qreal tattackRange;


signals:
    void destroy();
};

#endif // PROJECTILE_H
