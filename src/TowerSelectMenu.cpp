#include "TowerSelectMenu.h"
#include "Archer.h"
#include "StoneThrower.h"
#include "JohnSnow.h"
#include "Dragon.h"
TowerSelectMenu::TowerSelectMenu(QPoint pressPos, int currentMoney, QGraphicsObject *parent)
    : QGraphicsObject(parent), currentMoney(currentMoney), pressPos(pressPos)
{

    int enough = (Archer::getBuyCost() > currentMoney) ? (-1) : 1;
    Button *selectArcher = new Button(":/img/asset/ArcherButton_2.png", ":/img/asset/ArcherButton_1.png", 0, 0, enough, this);
    selectArcher->setParentItem(this);
    selectArcher->setPos(QPoint(pressPos.x()-100, pressPos.y()-100));
    selectArcher->setZValue(96);
    if (enough == 1)
    {
        connect(selectArcher, &Button::clicked, [=]()
                { emit selectTowerType(pressPos, 1);
            emit closeTowerSelectMenu();
        });
    }

    enough = (StoneThrower::getBuyCost() > currentMoney) ? (-1) : 1;
    Button *selectStoneThrower = new Button(":/img/asset/stoneButton_2.png", ":/img/asset/stoneButton.png", 0, 0, enough, this);
    selectStoneThrower->setParentItem(this);
    selectStoneThrower->setPos(QPoint(pressPos.x()-100, pressPos.y()+100));
    selectStoneThrower->setZValue(96);
    if (enough == 1)
    {
        connect(selectStoneThrower, &Button::clicked, [=]()
                { emit selectTowerType(pressPos, 2);  emit closeTowerSelectMenu();});
    }

    enough = (JohnSnow::getBuyCost() > currentMoney) ? (-1) : 1;
    Button *selectJohnSnow = new Button(":/img/asset/JohnSnowButton_2.png", ":/img/asset/JohnSnowButton.png", 0, 0, enough, this);
    selectJohnSnow->setParentItem(this);
    selectJohnSnow->setPos(QPoint(pressPos.x()+100,pressPos.y()-100));
    selectJohnSnow->setZValue(96);
    if (enough == 1)
    {
        connect(selectJohnSnow, &Button::clicked, [=]()
                { emit selectTowerType(pressPos, 3);  emit closeTowerSelectMenu();});
    }

    enough = (Dragon::getBuyCost() > currentMoney) ? (-1) : 1;
    Button *selectDragon = new Button(":/img/asset/dragonButton_2.png", ":/img/asset/dragonButton.png", 0, 0, enough, this);
    selectDragon->setParentItem(this);
    selectDragon->setPos(QPoint(pressPos.x()+100, pressPos.y()+100));
    selectDragon->setZValue(96);
    if (enough == 1)
    {
        connect(selectDragon, &Button::clicked, [=]()
                { emit selectTowerType(pressPos, 4); emit closeTowerSelectMenu(); });
    }
    Button *deleteMenu = new Button(":/img/asset/btnEnd.jpeg", ":/img/asset/btnEndLight.jpeg", 0, 0, 0, this);
    deleteMenu->setParentItem(this);
    deleteMenu->setPos(QPoint(pressPos.x(), pressPos.y()));
    deleteMenu->setZValue(96);
    connect(deleteMenu, &Button::clicked, this, &TowerSelectMenu::closeTowerSelectMenu);
}

TowerSelectMenu::~TowerSelectMenu() {};

QRectF TowerSelectMenu::boundingRect() const
{
    return QRectF(pressPos.x()-100, pressPos.y()-100, 300, 300);
}

void TowerSelectMenu::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setBrush(QBrush(QColor(255, 255, 255, 128)));

    painter->drawRect(boundingRect());
}
