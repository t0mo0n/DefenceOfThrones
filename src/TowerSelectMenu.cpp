#include "TowerSelectMenu.h"
#include "TowerFrame.h"
TowerSelectMenu::TowerSelectMenu(QGraphicsObject *parent)
    : QGraphicsObject{parent}
{
    Button *selectArcher = new Button("路径1", "路径2");
    selectArcher->setParentItem(this);
    selectArcher->setPos(QPointF(100, 100));

    Button *selectStoneThrower = new Button("路径1", "路径2");
    selectStoneThrower->setParentItem(this);
    selectStoneThrower->setPos(QPointF(300, 100));

    Button *selectJohnSnow = new Button("路径1", "路径2");
    selectJohnSnow->setParentItem(this);
    selectJohnSnow->setPos(QPointF(100, 300));

    Button *selectDragon = new Button("路径1", "路径2");
    selectDragon->setParentItem(this);
    selectDragon->setPos(QPointF(300, 100));

    Button *deleteMenu = new Button("路径1", "路径2");
    deleteMenu->setParentItem(this);
    deleteMenu->setPos(QPointF(200, 200));
    connect(deleteMenu, &Button::clicked, this, &TowerSelectMenu::closeTowerSelectMenu);
}
