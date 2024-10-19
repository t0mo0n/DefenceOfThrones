#ifndef LEVELSELECTMENU_H
#define LEVELSELECTMENU_H

#include <QWidget>
#include <QDialog>
#include <QPushButton>
#include <QPaintEvent>
#include <QPainter>

//此处设置了三个关卡，如需增加，需增加按钮。
class LevelSelectMenu : public QDialog
{
    Q_OBJECT
public:
    explicit LevelSelectMenu(int maxLevel_,QWidget *parent = nullptr);
    void paintEvent(QPaintEvent* event);
signals:

private:
    QList<QPushButton*> buttons={new QPushButton{"LEVEL 1",this},
                                new QPushButton{"LEVEL 2",this},
                                new QPushButton{"LEVEL 3",this}};
    int maxLevel=1;
};


#endif // LEVELSELECTMENU_H
