#include "Enemy.h"


Enemy::Enemy(const QVector<QPoint>& routine_, QGraphicsItem *parent)
    : QGraphicsObject(parent), isEnterBase(false), index(1),
    health(50), speed(3), damage(1), reward(100),routine(routine_)
{
    // 加载图片
    isFire=false;
    fireCount=0;

    size=60;
    path = ":/colored.png"; // 假设图片路径
    if (!enemyPix.load(path)) {
        qDebug() << "Failed to load enemy image from" << path;
    }

    // 起点
    if (!routine.isEmpty()) {
        pos0 = routine.at(0);
    }
    //行走的方向和次数
    stepCount=0;
    if(routine.size()>1){
        if(routine[0].x()==routine[1].x()){
            if(routine[0].y()>routine[1].y()){
                direct=1;//左
            }else{
                direct=2;//右
            }
            step=(routine[1].y()-routine[0].y())/8;
        }else{
            if(routine[0].x()>routine[1].x()){
                direct=3;//上
            }else{
                direct=4;//下
            }
            step=(routine[1].x()-routine[0].x())/8;
        }
        moveTimer = new QTimer(this);
        connect(moveTimer, &QTimer::timeout, this, &Enemy::move);
        moveTimer->start(1000 / speed);
    }




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
    if (isEnterBase || (index >= routine.size() - 1&&stepCount>step-1)) {
        if (!isEnterBase) {
            emit isArrived(damage,this);
        }
        return;
    }

    stepCount++;

    if(stepCount==step){
        index++;
        stepCount=0;
        if(routine[index-1].x()==routine[index].x()){
            if(routine[index-1].y()>routine[index].y()){
                direct=1;//左
            }else{
                direct=2;//右
            }
            step=(routine[index].y()-routine[index-1].y())/80;
        }else{
            if(routine[index-1].x()>routine[index].x()){
                direct=3;//上
            }else{
                direct=4;//下
            }
            step=(routine[index].x()-routine[index-1].x())/80;
        }
    }

    switch (direct){
    case 1:
        pos0.setY(pos0.y()-10);
        break;
    case 2:
        pos0.setY(pos0.y()+10);
        break;
    case 3:
        pos0.setX(pos0.x()-10);
        break;
    case 4:
        pos0.setX(pos0.x()+10);
        break;
    default:
        break;
    }

    if (index >= routine.size()-1&&stepCount>step-1 ) {
        isEnterBase = true;
        emit isArrived(damage,this); // 发出进入基地的信号
        qDebug()<<"2";

    }else{
        // 更新图形项的位置
        healthDisplay->setPos(pos0.x() + (size / 2) -(healthDisplay->boundingRect().width() / 2),
                              pos0.y() - healthDisplay->boundingRect().height());
        qDebug() <<"1";
        updateHealthDisplay();
        this->setPos(pos0); // 更新 QGraphicsItem 的位置
    }

    qDebug()<<pos0.x()<<","<<pos0.y();
}

void Enemy::takeDamage(int damage_)
{
    if(enemyType==1)damage+=5;
    health -= damage_;
    if (health <= 0) {
        health = 0;
        emit isDead(reward,this); // 发出死亡信号
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

void Enemy::receiveSnow(int damage_){
    takeDamage(damage_);
}
