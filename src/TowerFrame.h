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
//#include <movingitem.h>

class TowerFrame : public QObject,public QGraphicsItem
{

    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)
protected:
    int projectType;//投掷物的种类
    int towertype;//防御塔的种类
    int level;//防御塔现在的等级

    int attackRange;
    int attackSpeed;
    int buyCost;
    int sellPrice;
    QGraphicsItem* target;

    QString picDir;
    QVector<int> upgradeFee;
    QVector<Projectile*> projectileList;



public:
    explicit TowerFrame(QPoint pos_=QPoint(0,0),int type=0);
    virtual void attack()=0;
    static int towerSize;
    void FindEnemy();//跟踪并且瞄准敌人

    int getBuyCost(){return buyCost;};
    int getSellPrice(){return sellPrice;};
    int getUpdateCost(){return upgradeFee[level];};//这里可能出问题，升级的坐标不能超过界限！！1-3级
    void setTarget(QGraphicsItem* target_out=nullptr);//仍有仅作测试的内容！！！！！！？？？？？
    void resetTarget();//如果敌人死了，调用这个方法把这个防御塔的敌人置空；

    void paint(QPainter * painterconst,const QStyleOptionGraphicsItem *option, QWidget *widget)override;//画出防御塔
    QRectF boundingRect() const override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override ;
    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event) override;

    QPointF TowerCentral;//相对于场景的坐标
    void removeProjectileList();

signals:
public slots:
    virtual void upgrade()=0;//升级植物,界面设计者要根据现有的钱和updatecost比较获得是否可行,别忘了扣钱
    void sell();//出售植物并将植物删除

};

#endif // TOWER_FRAME_H
