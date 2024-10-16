#ifndef TOWERSELECTMENU_H
#define TOWERSELECTMENU_H

#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsItem>


class TowerSelectMenu : public QGraphicsItem
{
    Q_OBJECT
public:
    explicit TowerSelectMenu(QGraphicsItem *parent = nullptr);

signals:
};

#endif // TOWERSELECTMENU_H
