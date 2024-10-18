#ifndef OBSTACLE_H
#define OBSTACLE_H

#include <QWidget>
#include <QGraphicsItem>
#include<QPixmap>
#include<QPoint>
#include<QPainter>
class Obstacle : public QWidget,public QGraphicsItem
{
    Q_OBJECT
private:

    QString path;//图片路径
    int price;//被击碎后给予玩家的金币
    int health;//生命值
    int type;
    QPoint pos;
    QPixmap obstaclePix;
public:
    explicit Obstacle(int price_,int health_,int type_,QPoint pos_,QWidget *parent = nullptr);

    void checkIfDead(int damage);//击碎发出信号
    QRectF boundingRect() const override;  // 定义边界矩形
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;  // 绘制障碍物
    ~Obstacle(){emit destory();}
signals:
    void isDamaged(int price);
    void destory();
public slots:
    void receive(int damage_,int type);
    void receiveSnow(int damage_);
};

#endif // OBSTACLE_H
