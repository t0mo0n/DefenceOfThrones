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
#include "Archer.h"
#include "StoneThrower.h"
#include "JohnSnow.h"
#include "Dragon.h"
#define CELL_SIZE 80
//关于Z值的描述 对于背景以及装饰品 0~ 9
//敌人以及障碍物 10~19
//塔 20~29
//控制按钮以及页面 90~100
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
    void onTowerUpdated(int cost);
    void onDeleteTowerButtonClicked(int cost);
    //void contextMenuEvent(QGraphicsSceneContextMenuEvent *event);
public slots:
    void onPauseButtonClicked();
    void onResumeButtonClicked();
    void onGameEndButtonClicked();
    void onTowerSelectButtonClicked(QPoint cellPos,int type);
    void updatePlayerLives(int lives);
    void onEnemyDead(int reward, Enemy* enemyToBedelete);
    void onEnemyArrive(int damage, Enemy* enemyToBedelete);
    void onObstacleDestroyed(int reward);
    void onTowerCellClicked(QPoint clickPos );

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
    void isEnough(bool state);
};

#endif // GAMESCENE_H
