#include<QGraphicsBlurEffect>
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
        pausedMenu->setZValue(100);

        QGraphicsBlurEffect* pauseMenuEffect = new QGraphicsBlurEffect();
        pauseMenuEffect->setBlurRadius(100);
        pausedMenu->setGraphicsEffect(pauseMenuEffect);
        scene->addItem(pausedMenu);
        resumeGameButton = new Button("路径1","路径2",550,350);
        resumeGameButton->setParentItem(pausedMenu);
        resumeGameButton->setZValue(101);
        scene->addItem(resumeGameButton);
    }
}

void GameScene::onResumeButtonClicked()
{
    if(pausedMenu)
    {

    }
}
