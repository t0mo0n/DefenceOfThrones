#include "TowerSelectMenu.h"
#include "TowerFrame.h"
TowerSelectMenu::TowerSelectMenu(QPoint pressPos, QGraphicsObject *parent)
    : QGraphicsObject(parent),pressPos(pressPos)
{
    Button *selectArcher = new Button("路径1", "路径2",0,0,this);
    selectArcher->setParentItem(this);
    selectArcher->setPos(QPoint(100, 100));
    connect(selectArcher,&Button::clicked,[=](){
        emit selectTowerType(1);
    });

    Button *selectStoneThrower = new Button("路径1", "路径2",0,0,this);
    selectStoneThrower->setParentItem(this);
    selectStoneThrower->setPos(QPoint(300, 100));
    connect(selectStoneThrower,&Button::clicked,[=](){
        emit selectTowerType(2);
    });

    Button *selectJohnSnow = new Button("路径1", "路径2",0,0,this);
    selectJohnSnow->setParentItem(this);
    selectJohnSnow->setPos(QPoint(100, 300));
    connect(selectJohnSnow,&Button::clicked,[=](){
        emit selectTowerType(3);
    });

    Button *selectDragon = new Button("路径1", "路径2",0,0,this);
    selectDragon->setParentItem(this);
    selectDragon->setPos(QPoint(300, 100));
    connect(selectDragon,&Button::clicked,[=](){
        emit selectTowerType(4);
    });

    Button *deleteMenu = new Button("路径1", "路径2",0,0,this);
    deleteMenu->setParentItem(this);
    deleteMenu->setPos(QPoint(200, 200));
    connect(deleteMenu, &Button::clicked, this, &TowerSelectMenu::closeTowerSelectMenu);
}

TowerSelectMenu::~TowerSelectMenu(){};

QRectF TowerSelectMenu::boundingRect() const
{
    return QRectF(pressPos.x(),pressPos.y(),500,500);
}

void TowerSelectMenu::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setBrush(QBrush(QColor(255,255,255,128)));

    painter->drawRect(boundingRect());
}
