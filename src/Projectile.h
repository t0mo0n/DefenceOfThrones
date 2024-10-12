#ifndef PROJECTILE_H
#define PROJECTILE_H

#include <QObject>
#include <QGraphicsItem>
#include <QString>
#include <QPainter>
#include <QTimer>

class Projectile : public QObject,public QGraphicsItem
{
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)
public:
    explicit Projectile(QPointF pos);
    void SetTarget(QGraphicsItem* Enemy=nullptr);
    void MoveToEneny();
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)override;
    QRectF boundingRect() const override;
    static qreal pix_size;
protected:
    int speed;
    int damage;
    int target;
    QString src;//投掷物的图片
    QGraphicsItem* enemys;
    QPointF delta;
    QTimer* moveTimer ;


signals:
};

#endif // PROJECTILE_H
