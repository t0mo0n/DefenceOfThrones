#include "TowerFrame.h"

Tower_frame::Tower_frame(QPoint pos_,int type)
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
    towertype=type;
    level=1;
    setTransformOriginPoint(tower_size/2,tower_size/2); // 设置变换原点
    target=nullptr;
    TowerCentral=QPointF(pos_.x()+tower_size/2,pos_.y()+tower_size/2);
}

int Tower_frame::tower_size=100;

void Tower_frame::paint(QPainter * painterconst,const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);


    QRectF rect = boundingRect();
    painterconst->setPen(Qt::red); // 设置边界框颜色
    painterconst->drawRect(rect); // 绘制边界矩形
    painterconst->drawEllipse(tower_size/2-attack_range,tower_size/2-attack_range,2*attack_range,2*attack_range); // 绘制边界矩形

    painterconst->drawPixmap(QRect(0,0,tower_size,tower_size),QPixmap(pic_dir));
}

QRectF Tower_frame::boundingRect()const
{
    return QRectF(tower_size/2-attack_range,tower_size/2-attack_range,2*attack_range,2*attack_range);
}

void Tower_frame::Sell()
{
    QGraphicsScene *game_map=this->scene();
    if(game_map!=nullptr)
    {
        game_map->removeItem(this);
    }
}

void Tower_frame::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
    QMenu menu;
    QAction *action1 = menu.addAction("upgrade");
    QAction *action2 = menu.addAction("sell");
    connect(action1,SIGNAL(triggered()),this,SLOT(Upgrade()));
    connect(action2,SIGNAL(triggered()),this,SLOT(Sell()));
    menu.exec(event->screenPos()); //在按下鼠标左键的地方弹出菜单
    QGraphicsItem::contextMenuEvent(event);
}

void Tower_frame:: mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    // 处理鼠标按下事件
    qDebug() << "Item clicked!";

    QGraphicsItem::mousePressEvent(event); // 确保调用基类实现
}

void Tower_frame::FindEnemy()
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
        qDebug()<<"tower攻击的目标无效";
    }
}
void Tower_frame::ResetTarget()// 把塔的敌人制空，同时把所有子弹的敌人置空
{
    target=nullptr;
    if(!projectile_list.isEmpty())
    {
        for(auto item: projectile_list)
        {
            item->SetTarget();
        }
    }
}
