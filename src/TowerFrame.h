#ifndef TOWER_FRAME_H
#define TOWER_FRAME_H

#include <QMenu>
#include <QObject>
#include <QGraphicsSceneContextMenuEvent>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QPoint>
#include <QPainter>
#include <QDebug>
#include <Projectile.h>
#include <QVector>

class Tower_frame : public QObject,public QGraphicsItem
{

    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)
protected:
    int project_Type;//投掷物的种类
    int towertype;//防御塔的种类
    int level;//防御塔现在的等级

    int attack_range;
    int attack_speed;
    int buy_cost;
    int sellPrice;
    QGraphicsItem* target;

    QString pic_dir;
    QVector<int> upgrade_fee;
    QVector<Projectile*> projectile_list;


public:
    explicit Tower_frame(QPoint pos_=QPoint(0,0),int type=0);
    virtual void Attack()=0;
    static int tower_size;
    void FindEnemy();//跟踪并且瞄准敌人

    int get_BuyCost(){return buy_cost;};
    int get_SellPrice(){return sellPrice;};
    int get_UpdateCost(){return upgrade_fee[level];};//这里可能出问题，升级的坐标不能超过界限！！1-3级
    void set_target(QGraphicsItem* target_out=nullptr){target=target_out;};
    void ResetTarget();//如果敌人死了，调用这个方法把这个防御塔的敌人置空；

    void paint(QPainter * painterconst,const QStyleOptionGraphicsItem *option, QWidget *widget)override;//画出防御塔
    QRectF boundingRect() const override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override ;
    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event) override;

    QPointF TowerCentral;//相对于场景的坐标

signals:
public slots:
    virtual void Upgrade()=0;//升级植物,界面设计者要根据现有的钱和updatecost比较获得是否可行,别忘了扣钱
    void Sell();//出售植物并将植物删除

};

#endif // TOWER_FRAME_H
