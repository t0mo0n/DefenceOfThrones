#ifndef PATHCELL_H
#define PATHCELL_H


#include <QGraphicsObject>
#include <QPoint>
#include <QPixmap>
#include <QPainter>
#include <QString>
class PathCell : public QGraphicsObject
{
    Q_OBJECT
public:
    explicit PathCell(QString pixMapPath,QPoint cellPos, QGraphicsObject* parent = nullptr);;
    QRectF boundingRect() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr) override;

private:
    QString pixMapPath;
    QPixmap cellPixmap;
    QPoint cellPos;
};

#endif // PATHCELL_H
