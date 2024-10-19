#ifndef OBSTACLE_H
#define OBSTACLE_H
#include <QApplication>
#include <QGraphicsScene>
#include <QObject>
#include <QGraphicsView>
#include <QGraphicsEllipseItem>
#include <QTimer>
#include <Enemy.h>
class Obstacle : public Enemy
{
    Q_OBJECT
public:
    explicit Obstacle(int type_);

    int type;
    int count;
    int size;
    ~Obstacle()
    {
        emit destroy();
    }
    bool isEnemy(){return false;};
};

#endif // OBSTACLE_H
