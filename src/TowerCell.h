#ifndef TOWERCELL_H
#define TOWERCELL_H

#include <QGraphicsSceneMouseEvent>
#include <QGraphicsObject>
#include <QPoint>
#include <QPixmap>
#include <QPainter>
#include <QRectF>
class TowerCell : public QGraphicsObject
{
    Q_OBJECT
public:
    explicit TowerCell(QPoint cellPos, QGraphicsObject* parent = nullptr);
    QRectF boundingRect() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

private:
    QPixmap cellPixmap;
    QPoint cellPos;
signals:
    void clicked(QPoint cellPos);
};

#endif // TOWERCELL_H
