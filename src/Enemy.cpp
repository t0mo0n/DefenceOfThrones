#include "Enemy.h"

Enemy::Enemy(const QVector<QPoint>& routine_, QGraphicsItem *parent)
    : QGraphicsObject(parent), isEnterBase(false), index(0),
    health(100), speed(1), damage(1), reward(50), routine(routine_)
{
    // 加载图片
    path = ":/colored.png"; // 假设图片路径
    if (!enemyPix.load(path)) {
        qDebug() << "Failed to load enemy image from" << path;
    }

    // 起点
    if (!routine.isEmpty()) {
        pos = routine.at(0);
    }

    moveTimer = new QTimer(this);
    connect(moveTimer, &QTimer::timeout, this, &Enemy::move);
    moveTimer->start(1000 / speed);
}

QRectF Enemy::boundingRect() const
{
    return QRectF(pos.x(), pos.y(), 50, 50); // 返回一个包含敌人图像的矩形
}

void Enemy::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->drawPixmap(boundingRect(), enemyPix,enemyPix.rect()); // 绘制敌人图像
}




void Enemy::move()
{
    if (isEnterBase || index >= routine.size() - 1) {
        if (!isEnterBase) {
            emit isArrived(damage);
        }
        return;
    }

    index++;
    pos = routine.at(index);

    if (index >= routine.size() - 1) {
        isEnterBase = true;
        emit isArrived(damage); // 发出进入基地的信号
        delete this;
    }

    // 更新图形项的位置
    this->setPos(pos); // 更新 QGraphicsItem 的位置
}

void Enemy::takeDamage(int damage_)
{
    health -= damage_;
    if (health <= 0) {
        health = 0;
        emit isDead(reward); // 发出死亡信号
        delete this;
        moveTimer->stop();
    }
}
