#include "TowerSelectMenu.h"
#include "TowerFrame.h"
TowerSelectMenu::TowerSelectMenu(QGraphicsObject *parent)
    : QGraphicsObject{parent}
{
    Button *selectArcher = new Button("路径1", "路径2");
    selectArcher->setParentItem(this);
    selectArcher->setPos(QPoint(100, 100));

    Button *selectStoneThrower = new Button("路径1", "路径2");
    selectStoneThrower->setParentItem(this);
    selectStoneThrower->setPos(QPoint(300, 100));

    Button *selectJohnSnow = new Button("路径1", "路径2");
    selectJohnSnow->setParentItem(this);
    selectJohnSnow->setPos(QPoint(100, 300));

    Button *selectDragon = new Button("路径1", "路径2");
    selectDragon->setParentItem(this);
    selectDragon->setPos(QPoint(300, 100));

    Button *deleteMenu = new Button("路径1", "路径2");
    deleteMenu->setParentItem(this);
    deleteMenu->setPos(QPoint(200, 200));
    connect(deleteMenu, &Button::clicked, this, &TowerSelectMenu::closeTowerSelectMenu);
}
