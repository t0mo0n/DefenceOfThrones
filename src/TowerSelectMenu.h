#ifndef TOWERSELECTMENU_H
#define TOWERSELECTMENU_H

#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QGraphicsObject>
#include <QPoint>
#include <QStyleOptionGraphicsItem>
#include <QGraphicsSceneMouseEvent>
#include <QString>
#include <QPixmap>
#include <QPainter>
#include <QBrush>
#include "TowerFrame.h"
#include "Button.h"

class TowerSelectMenu : public QGraphicsObject
{
    Q_OBJECT
public:
    TowerSelectMenu(QPoint pressPos, QGraphicsObject *parent = nullptr);
    ~TowerSelectMenu() override;
private:
    QPoint pressPos;
    Button *selectArcher;
    Button *selectStoneThrower;
    Button *selectJohnSnow;
    Button *selectDragon;
    Button *deleteMenu;
public:
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
signals:
    void closeTowerSelectMenu();
    void selectTowerType(int type);
};

#endif // TOWERSELECTMENU_H
