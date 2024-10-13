#include "TowerFrame.h"

TowerFrame::TowerFrame(QPoint pos_,int type)
{
    if(type==0)
    {
        qDebug()<<"tower_type==0?";
    }
    if(pos_==QPoint(0,0))
    {
        qDebug()<<"do you really means tower in(0,0)?";
    }

    this->setPos(pos_);
    towerType=type;
    level=1;
    setTransformOriginPoint(towerSize/2,towerSize/2); // 设置变换原点
    target=nullptr;
    TowerCentral=QPointF(pos_.x()+towerSize/2,pos_.y()+towerSize/2);
}

int TowerFrame::towerSize=100;

void TowerFrame::paint(QPainter * painterconst,const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);


    QRectF rect = boundingRect();
    painterconst->setPen(Qt::red); // 设置边界框颜色
    painterconst->drawRect(rect); // 绘制边界矩形
    painterconst->drawEllipse(towerSize/2-attackRange,towerSize/2-attackRange,2*attackRange,2*attackRange); // 绘制边界矩形

    painterconst->drawPixmap(QRect(0,0,towerSize,towerSize),QPixmap(picDir));
}

QRectF TowerFrame::boundingRect()const
{
    return QRectF(towerSize/2-attackRange,towerSize/2-attackRange,2*attackRange,2*attackRange);
}

void TowerFrame::sell()
{
    QGraphicsScene *game_map=this->scene();
    if(game_map!=nullptr)
    {
        game_map->removeItem(this);
        delete this;
    }
}

void TowerFrame::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
    QMenu menu;
    QAction *action1 = menu.addAction("upgrade");
    QAction *action2 = menu.addAction("sell");
    connect(action1,SIGNAL(triggered()),this,SLOT(upgrade()));
    connect(action2,SIGNAL(triggered()),this,SLOT(sell()));
    menu.exec(event->screenPos()); //在按下鼠标左键的地方弹出菜单
    QGraphicsItem::contextMenuEvent(event);
}

void TowerFrame:: mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    // 处理鼠标按下事件
    qDebug() << "Item clicked!";

    QGraphicsItem::mousePressEvent(event); // 确保调用基类实现
}

void TowerFrame::FindEnemy()
{
    if (target!=nullptr) {
        // 获取塔的位置
        QPointF towerPos = this->pos();
        // 获取目标的位置
        QPointF targetPos = target->pos();

        // 计算方向
        qreal angle = std::atan2(targetPos.y() - towerPos.y(), targetPos.x() - towerPos.x());

        // 设置塔的旋转（如果需要旋转显示）
        setRotation(angle * 180.0 / M_PI); // 将弧度转换为度

    }
    else
    {
        // qDebug()<<"tower攻击的目标无效";
    }
}
void TowerFrame::resetTarget()// 把塔的敌人制空，同时把所有子弹的敌人置空
{
    target=nullptr;
    if(!projectileList.isEmpty())
    {
        for(auto item: projectileList)
        {
            if(item)
            {
                item->setTarget();
            }

        }
    }
}

void TowerFrame::setTarget(QGraphicsItem* target_out)
{
    target=target_out;
    MovingItem* movingItem = dynamic_cast<MovingItem*>(target);//这里仅做测试
    if (movingItem) {
        connect(movingItem, &MovingItem::destroyed, this, &TowerFrame::resetTarget);
    }
}
