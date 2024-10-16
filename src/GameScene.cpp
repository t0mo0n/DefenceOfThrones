#include "GameScene.h"
#define SHILLING 100
#define HEALTH 20
GameScene::GameScene(int level, bool isHardMode, QGraphicsView *parent)
    : QGraphicsView{parent}
{
    this->level = level;
    this->isHardMode = isHardMode;
    this->player = new Player(SHILLING, HEALTH);
    this->map = new Map();
    pauseGameButton = new Button("路径1","路径2",1000,700);
    gameEndButton = new Button("路径1","路径2",1100,700);
    pausedMenu = nullptr;

}

void GameScene::closeEvent(QCloseEvent *event)
{
    emit gameEnd();
    event->accept();
}

void GameScene::onPauseButtonClicked()
{
    if(!pausedMenu)
    {
        pausedMenu = new QGraphicsRectItem(QRectF(scene->sceneRect()));
        pausedMenu->setBrush(QBrush(QColor(255,255,255,128)));

    }
}
