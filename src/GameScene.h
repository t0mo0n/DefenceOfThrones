#ifndef GAMESCENE_H
#define GAMESCENE_H

#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QGraphicsTextItem>
#include <QmouseEvent>
#include <QList>
#include "Player.h"
#include "Enemy.h"
#include "TowerFrame.h" //但文档里好像说是"Tower.h"
#include "Map.h"
#include "Obstacle.h"
#include "TowerSelectMenu.h"
#include "Button.h"

class GameScene : public QGraphicsView
{
    Q_OBJECT
public:
    GameScene(QGraphicsView *parent = nullptr);
    void addTower(Tower *);
    void addEnemy();
    void addObstacles();
    void updateScene();
    void pauseScene();
    void mousePressEvent(QMouseEvent *event);

public
    slot : void onPauseButtonClicked();
    void onResumeButtonClicked();
    void onGameEndButtonClicked();
    void onTowerSelectButtonClicked(int cost);
    void updatePlayerLives(int lives);
    void onEnemyDead(int reward);
    void onEnemyArrive(int damage);
    void onObstacleDestroyed(int reward);

private:
    Player *player;
    Map *map;
    Button *pauseGameButton;
    Button *resumeGameButton;
    Button *gameEndButton;

    QGraphicsScene *scene;
    QGraphicsTextItem *healthTextItem;
    QGraphicsTextItem *moneyTextItem;
    QList<TowerFrame *> towers;
    QList<Enemy *> enemies;
    QList<Obstacle *> obstacles;
    TowerSelectMenu *towerSelectMenu;
    QGraphicsItem *pausedMenu;

signals:
    void gameEnd();
};

#endif // GAMESCENE_H
