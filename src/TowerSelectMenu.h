#ifndef TOWERSELECTMENU_H
#define TOWERSELECTMENU_H

#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QGraphicsObject>
#include "TowerFrame.h"
#include "Button.h"

class TowerSelectMenu : public QGraphicsObject
{
    Q_OBJECT
public:
    TowerSelectMenu(QGraphicsObject *parent = nullptr);

private:
    TowerFrame *towerToBeSelected;
    Button *selectArcher;
    Button *selectStoneThrower;
    Button *selectJohnSnow;
    Button *selectDragon;
    Button *deleteMenu;
signals:
    void closeTowerSelectMenu();
};

#endif // TOWERSELECTMENU_H
