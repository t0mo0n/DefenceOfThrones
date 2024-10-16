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
}

GameScene::closeEvent(QCloseEvent *event)
{
    emit gameEnd();
    event->accept();
}
