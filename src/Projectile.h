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
    void SetTarget(QGraphicsItem* Enemy=nullptr);
    void MoveToEneny();
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)override;
    QRectF boundingRect() const override;
    static qreal pix_size;
    void OutOfRange();//删除超过攻击范围的子弹

protected:
    int speed;
    int damage;
    int target;
    QString src;//投掷物的图片
    QGraphicsItem* enemys;
    QPointF delta;
    QTimer* moveTimer ;
    QPointF Tower_cor;
    qreal Tattack_range;


signals:
};

#endif // PROJECTILE_H
