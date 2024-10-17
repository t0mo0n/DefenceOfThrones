#ifndef ENEMY_H
#define ENEMY_H

#include <QGraphicsItem>
#include <QPoint>
#include <QVector>
#include <QString>
#include <QTimer>
#include <QDebug>
#include <QPainter>
#include <QImage>
#include<QWidget>
#include<QGraphicsTextItem>
class Enemy : public QGraphicsObject
{

    Q_OBJECT

public:
    int size;

protected:
    bool isEnterBase; // 是否进入基地
    int index; // 当前位置
    int health; // 初始生命值和当前生命值
    int speed; // 移动速度
    int damage; // 对萝卜的伤害
    int reward; // 击败后给玩家的奖励（金币）
    QTimer *moveTimer; // 定时器用于控制移动
    QPoint pos0; // 当前位置
    QVector<QPoint> routine; // 敌人的移动路径
    QString path; // 图片路径
    QPixmap enemyPix; // 敌人的图片
    bool enemyType;//0是人，1是异鬼
    bool isFire;//是否点燃
    int fireCount;
    QGraphicsTextItem* healthDisplay;
public:

    explicit Enemy(const QVector<QPoint>& routine_, QGraphicsItem *parent = nullptr); // 构造函数，传入路径
    void move(); // 移动到下一个位置
    virtual void takeDamage(int damage_); // 接受伤害，检查是否死亡，死亡则触发信号

    // 重写 QGraphicsItem 的虚函数
    QRectF boundingRect() const override; // 返回项的边界矩形
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override; // 绘制项
    void updateHealthDisplay();
    virtual void enemyPause(){moveTimer->stop();};
    virtual void enemyResume(){moveTimer->start();};
signals:
    void isArrived(int damage_); // 敌人进入基地的信号
    void isDead(int reward_); // 敌人被击败的信号
public slots:
    void receive(int damage_,int type);
};

#endif // ENEMY_H
