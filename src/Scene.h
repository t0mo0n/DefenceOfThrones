#ifndef SCENE_H
#define SCENE_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>
#include <QGraphicsSceneContextMenuEvent>
#include <QCoreApplication>
#include <QObject>

class Scene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit Scene();
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override
    {
        // 获取点击位置
        QPointF clickPos = event->scenePos();
        qDebug() << "Mouse pressed at: " << clickPos;

        // 调用父类的处理方法（如果需要）
        QGraphicsScene::mousePressEvent(event);
    }
    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event)override;
};

#endif // SCENE_H
