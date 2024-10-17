#ifndef TOWERSELECTMENU_H
#define TOWERSELECTMENU_H

#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsItem>
#include "TowerFrame.h"
#include "Button.h"

class TowerSelectMenu : public QGraphicsItem
{
    Q_OBJECT
public:
    TowerSelectMenu(QGraphicsItem *parent = nullptr);

private:
    TowerFrame *towerToBeSelected;
    Button *selectArcher;
    Button *selectStoneThrower;
    Button *selectJhonSnow;
    Button *selectDragon;
    Button *deleteMenu;
signals:
};

#endif // TOWERSELECTMENU_H
