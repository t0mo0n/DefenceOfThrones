#ifndef BACKGROUND_H
#define BACKGROUND_H

#include <QObject>
#include <Qstring>
#include <QPoint>
#include <QPixmap>
#include <QGraphicsObject>
#include <QStyleOptionGraphicsItem>
#include <QPainter>
#include <QRectF>
class BackGround : public QGraphicsObject
{
    Q_OBJECT
public:
    BackGround(QString backgroundPath,QGraphicsObject* parent = nullptr);
private:
    QString backgroundPath;
    QPixmap backgroundPixmap;
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

};

#endif // BACKGROUND_H
