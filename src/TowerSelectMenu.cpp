#include "TowerSelectMenu.h"
#include "TowerFrame.h"
#include "Archer.h"
#include "StoneThrower.h"
#include "JohnSnow.h"
#include "Dragon.h"
TowerSelectMenu::TowerSelectMenu(QPoint pressPos, int currentMoney, QGraphicsObject *parent)
    : QGraphicsObject(parent), currentMoney(currentMoney), pressPos(pressPos)
{

    Archer archerExample;
    int enough = (archerExample.getBuyCost() > currentMoney) ? (-1) : 1;
    Button *selectArcher = new Button(":/img/asset/3.png", ":/img/asset/3.png", 0, 0, enough, this);
    selectArcher->setParentItem(this);
    selectArcher->setPos(QPoint(100, 100));
    selectArcher->setZValue(96);
    if (enough == 1)
    {
        connect(selectArcher, &Button::clicked, [=]()
                { emit selectTowerType(pressPos, 1);
            emit closeTowerSelectMenu();
        });
    }

    StoneThrower stoneThrowerExample;
    enough = (stoneThrowerExample.getBuyCost() > currentMoney) ? (-1) : 1;
    Button *selectStoneThrower = new Button(":/img/asset/2.png", ":/img/asset/2.png", 0, 0, enough, this);
    selectStoneThrower->setParentItem(this);
    selectStoneThrower->setPos(QPoint(300, 100));
    selectStoneThrower->setZValue(96);
    if (enough == 1)
    {
        connect(selectStoneThrower, &Button::clicked, [=]()
                { emit selectTowerType(pressPos, 2);  emit closeTowerSelectMenu();});
    }

    JohnSnow johnSnowExample;
    enough = (johnSnowExample.getBuyCost() > currentMoney) ? (-1) : 1;
    Button *selectJohnSnow = new Button(":/img/asset/3.png", ":/img/asset/3.png", 0, 0, enough, this);
    selectJohnSnow->setParentItem(this);
    selectJohnSnow->setPos(QPoint(100, 300));
    selectJohnSnow->setZValue(96);
    if (enough == 1)
    {
        connect(selectJohnSnow, &Button::clicked, [=]()
                { emit selectTowerType(pressPos, 3);  emit closeTowerSelectMenu();});
    }

    Dragon dragonExample;
    enough = (dragonExample.getBuyCost() > currentMoney) ? (-1) : 1;
    Button *selectDragon = new Button(":/img/asset/1.png", ":/img/asset/1.png", 0, 0, enough, this);
    selectDragon->setParentItem(this);
    selectDragon->setPos(QPoint(300, 100));
    selectDragon->setZValue(96);
    if (enough == 1)
    {
        connect(selectDragon, &Button::clicked, [=]()
                { emit selectTowerType(pressPos, 4); emit closeTowerSelectMenu(); });
    }
    Button *deleteMenu = new Button("路径1", "路径2", 0, 0, 0, this);
    deleteMenu->setParentItem(this);
    deleteMenu->setPos(QPoint(200, 200));
    deleteMenu->setZValue(96);
    connect(deleteMenu, &Button::clicked, this, &TowerSelectMenu::closeTowerSelectMenu);
}

TowerSelectMenu::~TowerSelectMenu() {};

QRectF TowerSelectMenu::boundingRect() const
{
    return QRectF(pressPos.x(), pressPos.y(), 500, 500);
}

void TowerSelectMenu::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setBrush(QBrush(QColor(255, 255, 255, 128)));

    painter->drawRect(boundingRect());
}
