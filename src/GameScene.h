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
#include "BackGround.h"
#include "TowerSelectMenu.h"
#include "Button.h"

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
    ~GameScene()
    {
        delete player;
        delete map;
        delete pauseGameButton;
        delete gameEndButton;
        delete background;
        delete scene;
        delete updateTimer;
        delete enemyTimer;
    };
    void addTower(TowerFrame * tower);
    void addEnemy();
    void addObstacles();
    void updateScene();
    void pauseScene();
    void resumeScene();
    // void mousePressEvent(QMouseEvent *event) override;
    void closeEvent(QCloseEvent *event) override;
    void loadMap(int level);
    void onTowerUpdated(int cost);
    void onDeleteTowerButtonClicked(int cost);
    //void contextMenuEvent(QGraphicsSceneContextMenuEvent *event);
    void drawBackground(QPainter *painter,const QRectF &rect) override{
        QPixmap bgPix;
        bgPix.load(":/img/asset/Wall.jpg");
        painter->drawPixmap(0,0,this->width(),this->height(),bgPix);
    };
    ~GameScene()
    {
        delete player;
        delete map;
        delete pauseGameButton;
        delete gameEndButton;
        // delete background;
        delete scene;
        delete updateTimer;
        delete enemyTimer;
    };
public slots:
    void onPauseButtonClicked();
    void onResumeButtonClicked();
    void onGameEndButtonClicked();
    void onTowerSelectButtonClicked(QPoint cellPos,int type);
    void updatePlayerLives(int lives);
    void onEnemyDead(int reward, Enemy* enemyToBedelete);
    void onEnemyArrive(int damage, Enemy* enemyToBedelete);
    void onObstacleDestroyed(int reward, Obstacle* toBeDelete);
    void onTowerCellClicked(QPoint clickPos );

private:
    Player *player;
    Map *map;
    Button *pauseGameButton;
    Button *resumeGameButton;
    Button *gameEndButton;
    QTimer *updateTimer;
    QTimer *enemyTimer;
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
    bool win_signal1 = false;
    bool win_signal2 = false;

    int ecount = 0;

signals:
    void gameEnd();
    void isEnough(bool state);
};

#endif // GAMESCENE_H
