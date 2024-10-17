#include "TowerSelectMenu.h"
#include "TowerFrame.h"
TowerSelectMenu::TowerSelectMenu(QGraphicsObject *parent)
    : QGraphicsObject{parent}
{
    Button *selectArcher = new Button("路径1", "路径2",0,0,this);
    selectArcher->setParentItem(this);
    selectArcher->setPos(QPoint(100, 100));

    Button *selectStoneThrower = new Button("路径1", "路径2",0,0,this);
    selectStoneThrower->setParentItem(this);
    selectStoneThrower->setPos(QPoint(300, 100));

    Button *selectJohnSnow = new Button("路径1", "路径2",0,0,this);
    selectJohnSnow->setParentItem(this);
    selectJohnSnow->setPos(QPoint(100, 300));

    Button *selectDragon = new Button("路径1", "路径2",0,0,this);
    selectDragon->setParentItem(this);
    selectDragon->setPos(QPoint(300, 100));

    Button *deleteMenu = new Button("路径1", "路径2",0,0,this);
    deleteMenu->setParentItem(this);
    deleteMenu->setPos(QPoint(200, 200));
    connect(deleteMenu, &Button::clicked, this, &TowerSelectMenu::closeTowerSelectMenu);
}
