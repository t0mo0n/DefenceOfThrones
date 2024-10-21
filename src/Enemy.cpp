#include "Enemy.h"


Enemy::Enemy(const QVector<QPoint>& routine_, QGraphicsItem *parent)
    : QGraphicsObject(parent), isEnterBase(false), index(1),
    health(50), speed(100), damage(1), reward(100)
{
    //斩击效果
    isSlash=false;
    slashTimer=new QTimer(this);
    connect(slashTimer, &QTimer::timeout, this, &Enemy::onSlashTimeout);

    slashPath=":/img/asset/shield.png";
    if (!slashPix.load(slashPath)) {
        qDebug() << "Failed to load slash image from" << slashPath;
    }
    //others
    for (int var = 0; var < routine_.size(); ++var) {
        routine<<QPoint((routine_[var].x()-1)*80+10,(routine_[var].y()-1)*80+10);
    }
    // routine=routine_;
    // 加载图片
    isFire=false;
    fireCount=0;

    size=60;
    path =":/img/asset/Deadalive.png"; // default图片路径
    if (!enemyPix.load(path)) {
        qDebug() << "Failed to load enemy image from" << path;
    }

    // 起点
    if (!routine.isEmpty()) {
        pos0 = routine[0];
    }
    //行走的方向和次数
    stepCount=0;
    if(routine.size()>1){
        if(routine[0].x()==routine[1].x()){
            if(routine[0].y()>routine[1].y()){
                direct=1;//上
            }else{
                direct=2;//下
            }
            step=abs(routine[1].y()-routine[0].y())/STEP;

        }else if(routine[0].y()==routine[1].y()){
            if(routine[0].x()>routine[1].x()){
                direct=3;//左
            }else{
                direct=4;//右
            }
            step=abs(routine[1].x()-routine[0].x())/STEP;
        }
        moveTimer = new QTimer(this);
        connect(moveTimer, &QTimer::timeout, this, &Enemy::move);
        moveTimer->start(1000 / speed);
        healthDisplay = new QGraphicsTextItem(this);
        healthDisplay->setParentItem(this);
        healthDisplay->setPlainText(QString::number(health));
        healthDisplay->setDefaultTextColor(Qt::red);
        healthDisplay->setFont(QFont("Arial", 12));
        healthDisplay->setPos(size/2-healthDisplay->boundingRect().width()/2,-50+healthDisplay->boundingRect().height());  // 设置在敌人图片上方居中显示
    }

    this->setPos(pos0);
}

QRectF Enemy::boundingRect() const
{
    return QRectF(0, 0, size, size); // 返回一个包含敌人图像的矩形
}

void Enemy::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    // qDebug()<<boundingRect();

    painter->drawPixmap(boundingRect(), enemyPix,enemyPix.rect()); // 绘制敌人图像

    if (isSlash) {
        // painter->drawPixmap(boundingRect(), slashPix, slashPix.rect()); // 绘制斜线图像

        painter->drawPixmap(20,20,20,20,slashPix);

    }
}


void Enemy::move()
{
    if (isEnterBase) {
        emit isArrived(damage,this);
        return;
    }

    stepCount++;
    switch (direct){
    case 1:
        pos0.setY(pos0.y()-STEP);
        break;
    case 2:
        pos0.setY(pos0.y()+STEP);
        break;
    case 3:
        pos0.setX(pos0.x()-STEP);
        break;
    case 4:
        pos0.setX(pos0.x()+STEP);
        break;
    default:
        break;
    }

    if(stepCount>=step){
        index++;
        if(index>=routine.size()){
            isEnterBase=true;
            emit isArrived(damage,this);
            return;
        }
        stepCount=0;
        if(routine[index-1].x()==routine[index].x()){
            if(routine[index-1].y()>routine[index].y()){
                direct=1;//上
            }else{
                direct=2;//下
            }
            step=abs(routine[index].y()-routine[index-1].y())/STEP;
        }else{
            if(routine[index-1].x()>routine[index].x()){
                direct=3;//左
            }else{
                direct=4;//右
            }
            step=abs(routine[index].x()-routine[index-1].x())/STEP;
        }
    }

    if(isFire){
        if(fireCount<500){
            fireCount++;
            if(fireCount%50==0){
                health--;
                if (health <= 0) {
                    health = 0;
                    moveTimer->stop();
                    emit isDead(reward,this); // 发出死亡信号
                    return;
                }
            }
        }else{
            isFire=false;
            fireCount=0;
        }
    }

    if (index >= routine.size()&&stepCount>step-1 ) {
        isEnterBase = true;
        emit isArrived(damage,this); // 发出进入基地的信号
        return ;
    }else{
        this->setPos(pos0); // 更新 QGraphicsItem 的位置
        // 更新图形项的位置
        healthDisplay->setPos(size / 2 - healthDisplay->boundingRect().width() / 2,
                              -50+healthDisplay->boundingRect().height());
        updateHealthDisplay();
    }
}


void Enemy::takeDamage(int damage_)
{
    if(enemyType==1)damage_+=5;
    health -= damage_;
    if (health <= 0) {
        health = 0;
        moveTimer->stop();
        emit isDead(reward,this); // 发出死亡信号
    }
}


void Enemy::receive(int damage_,int type){

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
    qDebug() << "hurted"<<health;
    takeDamage(damage_);
}

void Enemy::updateHealthDisplay() {
    healthDisplay->setPlainText(QString::number(health));
}

void Enemy::receiveSnow(int damage_){
    if (!isSlash) {
        isSlash = true;
        slashTimer->start(1000); // 启动定时器，1秒后触发超时
    }
    takeDamage(damage_);
    qDebug()<<"jinijin"<<pos0;
}

void Enemy::onSlashTimeout() {
    isSlash = false;
}
