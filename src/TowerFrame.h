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
#include <Enemy.h>
#include <Obstacle.h>

class TowerFrame : public QObject, public QGraphicsItem
{

    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)
protected:
    int projectType; // 投掷物的种类
    int towerType;   // 防御塔的种类
    int level;       // 防御塔现在的等级

    int attackRange;
    int attackSpeed;
    int buyCost;
    int sellPrice;
    Enemy *target;

    QString picDir;
    QVector<int> upgradeFee;
    QVector<Projectile *> projectileList;
    QTimer *aimTimer;
    QTimer *attackTimer;
    qreal towerAngle;
    qreal remainingTime1;
    qreal remainingTime2;
    QElapsedTimer*elapsedTimer;
    QRectF attackRect;


public:
    explicit TowerFrame(QPoint pos_ = QPoint(0, 0), int type = 0);
    virtual void attack() = 0;
    static int towerSize;
    virtual void FindEnemy() = 0; // 跟踪并且瞄准敌人

    int getBuyCost() { return buyCost; };
    int getSellPrice() { return sellPrice; };
    int getUpdateCost() { return upgradeFee[level]; }; // 这里可能出问题，升级的坐标不能超过界限！！1-3级
    void setTarget(Enemy *target_out = nullptr);       // 仍有仅作测试的内容！！！！！！？？？？？
    void resetTarget();                                // 如果敌人死了，调用这个方法把这个防御塔的敌人置空；

    void paint(QPainter *painterconst, const QStyleOptionGraphicsItem *option, QWidget *widget) override; // 画出防御塔
    QRectF boundingRect() const override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event) override;

    QPointF TowerCentral; // 相对于场景的坐标
    void removeProjectileList();
    QList<QGraphicsItem *> checkForItemsInBoundingRect();
    void towerPause();
    void towerResume();
    ~TowerFrame();

signals:
    void destroy();
    void sell();
public slots:
    virtual void upgrade() = 0; // 升级植物,界面设计者要根据现有的钱和updatecost比较获得是否可行,别忘了扣钱
};

#endif // TOWER_FRAME_H
