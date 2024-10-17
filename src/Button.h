#ifndef BUTTON_H
#define BUTTON_H

#include <QWidget>
#include <QGraphicsItem>
#include <QString>
#include <QPixmap>
#include <QPainter>
#include <QGraphicsObject>
class Button : public QGraphicsObject
{
    Q_OBJECT
public:
    Button(QString UnHoverImagePath, QString HoverImagePath, int posX=0, int posY=0, QGraphicsItem *parent = nullptr); // 未悬停时和悬停时的图片路径
protected:
    QString UnHoverImagePath;
    QString HoverImagePath;
    QPixmap UnHoverImage;
    QPixmap HoverImage;
    int posX;
    int posY;
    QRectF boundingRect() const;                                                            // 按钮的边界矩形
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget); // 绘制按钮的图像
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);                                  // 鼠标悬停在按钮上时的事件
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);                                  // 鼠标离开按钮时的事件
    void mousePressEvent(QGraphicsSceneMouseEvent *event);                                  // 鼠标点击按钮时的事件
signals:
    void clicked(); // 按钮被点击的信号
};

#endif // BUTTON_H
