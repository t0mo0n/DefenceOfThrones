#ifndef GAMESCENE_H
#define GAMESCENE_H

#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QGraphicsTextItem>
#include <QGraphicsRectItem>
#include <QmouseEvent>
#include <QTimer>
#include <QList>
#include <QVector>
#include <QPoint>
#include <QPointF>
#include <QPair>
#include "Player.h"
#include "Enemy.h"
#include "TowerFrame.h" //但文档里好像说是"Tower.h"
#include "Map.h"
#include "Obstacle.h"
#include "TowerSelectMenu.h"
#include "Button.h"
#include "Deadalive.h"
#include "GreyjoySoldier.h"
#include "KingSlayer.h"
#include "LannisterSoldier.h"
#include "Melisandre.h"
#include "NightKing.h"
#include "Mountain.h"
#include "Vesalion.h"
#include "Wilder.h"
#include "TowerCell.h"
#include "PathCell.h"
#define CELL_SIZE 80

class GameScene : public QGraphicsView
{
    Q_OBJECT

public:
    GameScene(int level, bool isHardMode, QGraphicsView *parent = nullptr);
    void addTower(TowerFrame * tower);
    void addEnemy();
    void addObstacles();
    void updateScene();
    void pauseScene();
    void resumeScene();
    void mousePressEvent(QMouseEvent *event) override;
    void closeEvent(QCloseEvent *event) override;
    void loadMap(int level);

public slots:
    void onPauseButtonClicked();
    void onResumeButtonClicked();
    void onGameEndButtonClicked();
    void onTowerSelectButtonClicked(int type);
    void onTowerUpdated(int cost);
    void onDeleteTowerButtonClicked(int cost);
    void updatePlayerLives(int lives);
    void onEnemyDead(int reward, Enemy* enemyToBedelete);
    void onEnemyArrive(int damage, Enemy* enemyToBedelete);
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
    QGraphicsRectItem *pausedMenu;
    int level;
    bool isHardMode;

signals:
    void gameEnd();
};

#endif // GAMESCENE_H
