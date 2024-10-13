#ifndef GAMESCENE_H
#define GAMESCENE_H

#include <QWidget>

class GameScene : public QWidget
{
    Q_OBJECT
public:
    explicit GameScene(QWidget *parent = nullptr);

signals:
};

#endif // GAMESCENE_H
