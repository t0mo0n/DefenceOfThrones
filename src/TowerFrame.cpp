#include "TowerFrame.h"
//子弹在发射之后马上把塔删掉，会导致子弹没有归属
TowerFrame::TowerFrame(QPoint pos_, int type)
{
    if (type == 0)
    {
        qDebug() << "tower_type==0?";
    }
    if (pos_ == QPoint(0, 0))
    {
        qDebug() << "do you really means tower in(0,0)?";
    }

    this->setPos(pos_);
    towerType = type;
    level = 1;
    setTransformOriginPoint(towerSize / 2, towerSize / 2); // 设置变换原点
    target = nullptr;
    TowerCentral = QPointF(pos_.x() + towerSize / 2, pos_.y() + towerSize / 2);
    aimTimer = new QTimer(this);
    attackTimer = new QTimer(this);
    towerAngle = 0;

    connect(aimTimer, &QTimer::timeout, this, &TowerFrame::FindEnemy);
    aimTimer->start(10);
    connect(attackTimer, &QTimer::timeout, this, &TowerFrame::attack);
    elapsedTimer= new QElapsedTimer();
    elapsedTimer->start();
}

int TowerFrame::towerSize = 80;

void TowerFrame::paint(QPainter *painterconst, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    QRectF rect = boundingRect();
    painterconst->setPen(Qt::red);                                                                                         // 设置边界框颜色
    painterconst->drawRect(rect);                                                                                          // 绘制边界矩形
    painterconst->drawEllipse(towerSize / 2 - attackRange, towerSize / 2 - attackRange, 2 * attackRange, 2 * attackRange); // 绘制边界矩形

    painterconst->drawPixmap(QRect(0, 0, towerSize, towerSize), QPixmap(picDir));
}

QRectF TowerFrame::boundingRect() const
{
    return QRectF(towerSize / 2 - attackRange, towerSize / 2 - attackRange, 2 * attackRange, 2 * attackRange);
}


void TowerFrame::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
    if (QRectF(0, 0, towerSize, towerSize).contains(event->pos()))
    {
        QMenu menu;
        QAction *action1 = menu.addAction("upgrade");
        QAction *action2 = menu.addAction("sell");
        connect(action1, SIGNAL(triggered()), this, SLOT(upgrade()));
        connect(action2, SIGNAL(triggered()), this, SLOT(sell()));
        menu.exec(event->screenPos()); // 在按下鼠标左键的地方弹出菜单
        QGraphicsItem::contextMenuEvent(event);
    }
}

void TowerFrame::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    // 处理鼠标按下事件
    qDebug() << "Item clicked!";

    QGraphicsItem::mousePressEvent(event); // 确保调用基类实现
}

void TowerFrame::resetTarget() // 把塔的敌人制空，同时把所有子弹的敌人置空
{
    target = nullptr;
    if (!projectileList.isEmpty())
    {
        for (auto item : projectileList)
        {
            if (item)
            {
                item->setTarget();
            }
        }
    }
}


void TowerFrame::setTarget(Enemy *target_out)
{
    update();
    target = target_out;
    if (target_out)
    {
        connect(target_out, &Enemy::destroyed, this, &TowerFrame::resetTarget);
    }
}

TowerFrame::~TowerFrame()
{
    emit destroy();
    aimTimer->stop();
    delete aimTimer;
    attackTimer->stop();
    delete attackTimer;

}

QList<QGraphicsItem *> TowerFrame::checkForItemsInBoundingRect()
{
    // 获取当前项的 boundingRect，并将其转换为场景坐标
    QRectF sceneBoundingRect = mapRectToScene(boundingRect());

    // 获取在该区域内的所有项
    QList<QGraphicsItem *> itemsInBoundingRect = scene()->items(sceneBoundingRect);

    // 移除自身（当前塔）避免自检测
    itemsInBoundingRect.removeOne(this);

    return itemsInBoundingRect;
}

void TowerFrame::towerPause()
{
    if (aimTimer->isActive()) {
        remainingTime1 = aimTimer->interval() - elapsedTimer->elapsed();
        aimTimer->stop();
    }
    if (attackTimer->isActive()) {
        remainingTime2 = attackTimer->interval() - elapsedTimer->elapsed();
        attackTimer->stop();
    }
    for (auto bullet :projectileList)
    {
        if(bullet)
        {
            bullet->pause();
        }
    }
}

void TowerFrame::towerResume()
{
    if (!aimTimer->isActive()) {
        aimTimer->start(remainingTime1);
        elapsedTimer->restart();
    }

    if (!attackTimer->isActive()) {
        attackTimer->start(remainingTime2);
        elapsedTimer->restart();
    }
    for (auto bullet :projectileList)
    {
        if(bullet)
        {
            bullet->resume();
        }
    }
}
