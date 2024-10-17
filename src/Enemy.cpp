#include "Enemy.h"

//点燃效果有问题

Enemy::Enemy(const QVector<QPoint>& routine_, QGraphicsItem *parent)
    : QGraphicsObject(parent), isEnterBase(false), index(0),
    health(100), speed(1), damage(1), reward(50),routine(routine_)
{
    // 加载图片
    isFire=true;
    fireCount=0;

    size=80;
    path = ":/colored.png"; // 假设图片路径
    if (!enemyPix.load(path)) {
        qDebug() << "Failed to load enemy image from" << path;
    }

    // 起点
    if (!routine.isEmpty()) {
        pos0 = routine.at(0);
    }

    moveTimer = new QTimer(this);
    connect(moveTimer, &QTimer::timeout, this, &Enemy::move);
    moveTimer->start(1000 / speed);

    healthDisplay = new QGraphicsTextItem(this);
    healthDisplay->setParentItem(this);
    healthDisplay->setPlainText(QString::number(health));
    healthDisplay->setDefaultTextColor(Qt::red);
    healthDisplay->setFont(QFont("Arial", 12));
    healthDisplay->setPos(pos0.x()+20,pos0.y() -20);  // 设置在敌人图片上方居中显示
}

QRectF Enemy::boundingRect() const
{
    return QRectF(pos0.x(), pos0.y(), size, size); // 返回一个包含敌人图像的矩形
}

void Enemy::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    if(isFire){
        if(fireCount<10){
            fireCount++;
            health--;
        }else{
            isFire=false;
            fireCount=0;
        }
    }

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
    pos0 = routine.at(index);

    if (index >= routine.size()-1 ) {
        isEnterBase = true;
        emit isArrived(damage); // 发出进入基地的信号
        qDebug()<<"2";
        delete this;
    }else{
        // 更新图形项的位置
        healthDisplay->setPos(pos0.x() + (size / 2) -(healthDisplay->boundingRect().width() / 2),
                              pos0.y() - healthDisplay->boundingRect().height());
        qDebug() <<"1";
        updateHealthDisplay();
        this->setPos(pos0); // 更新 QGraphicsItem 的位置
    }


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


void Enemy::receive(int damage_,int type){
    takeDamage(damage_);
    switch (type) {
    case 1:
        isFire=true;
        fireCount=0;
        break;
    case 2:
        speed-=10;
        break;
    case 4:
        isFire=true;
        fireCount=0;
        break;
    case 5:
        isFire=true;
        fireCount=0;
        break;
    default:
        break;
    }
}

void Enemy::updateHealthDisplay() {
    healthDisplay->setPlainText(QString::number(health));
}
