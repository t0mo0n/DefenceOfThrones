#ifndef BUTTON_H
#define BUTTON_H

#include <QWidget>
#include <QGraphicsItem>
#include <QString>

class Button : public QGraphicsItem
{
    Q_OBJECT
public:
    Button(QString UnHoverImagePath, QString HoverImagePath, QGraphicsItem *parent = nullptr); // 未悬停时和悬停时的图片路径

signals:
    void clicked(); // 按钮被点击的信号
};

#endif // BUTTON_H
