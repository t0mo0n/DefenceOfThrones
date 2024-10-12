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
    int count;
    void stop(QTimer* t);
    ~MovingItem()
    {
        emit destroy();
    }
public slots:
    void moveItem();
signals:
    void destroy();
};



#endif // MOVINGITEM_H
