#ifndef MOVINGITEM_H
#define MOVINGITEM_H

#include <QApplication>
#include <QGraphicsScene>
#include <QObject>
#include <QGraphicsView>
#include <QGraphicsEllipseItem>
#include <QTimer>

class MovingItem : public QObject,public QGraphicsEllipseItem
{
    Q_OBJECT
public:
    MovingItem();
public slots:
    void moveItem();
};



#endif // MOVINGITEM_H
