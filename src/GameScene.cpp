#include <QGraphicsBlurEffect>
#include "GameScene.h"
#define SHILLING 100
#define HEALTH 20
GameScene::GameScene(int level, bool isHardMode, QGraphicsView *parent)
    : QGraphicsView(parent)
{
    this->level = level;
    this->isHardMode = isHardMode;
    // this->player = new Player(SHILLING, HEALTH);
    this->map = new Map();
    pauseGameButton = new Button("路径1", "路径2", 1000, 700);
    scene = new QGraphicsScene(this);
    scene->addItem(pauseGameButton);
    pauseGameButton->setZValue(90);

    gameEndButton = new Button("路径1", "路径2", 1100, 700);
    scene->addItem(gameEndButton);
    gameEndButton->setZValue(90);

    resumeGameButton = nullptr;
    pausedMenu = nullptr;

    healthTextItem = new QGraphicsTextItem(QString("HEALTH: %1").arg(HEALTH));
    scene->addItem(healthTextItem);
    healthTextItem->setPos(1000, 0);
    healthTextItem->setDefaultTextColor(Qt::red);
    healthTextItem->setZValue(90);
    connect(player, &Player::lifeChanged, this, &GameScene::updatePlayerLives);

    moneyTextItem = new QGraphicsTextItem(QString("SHILLING: %1").arg(SHILLING));
    moneyTextItem->setPos(1000, 100);
    moneyTextItem->setDefaultTextColor(Qt::yellow);
    healthTextItem->setZValue(90);
    connect(player, &Player::moneyChanged,this,[=](int newAmount){
        this->moneyTextItem->setPlainText(QString("SHILLING: %1").arg(newAmount));
    });

    towerSelectMenu = nullptr;

    QTimer *updateTimer = new QTimer(this);
    updateTimer->start(50);
    connect(updateTimer, &QTimer::timeout, this, &GameScene::updateScene);

    QTimer *enemyTimer = new QTimer(this);
    if(isHardMode)
    {
        enemyTimer->start(1500);
    }
    else
    {
        enemyTimer->start(2000);
    }

    connect(enemyTimer, &QTimer::timeout, [=](){
        addEnemy();
    });
    loadMap(level);
}

void GameScene::onPauseButtonClicked()
{
    pauseScene();
    if (!pausedMenu)
    {
        pausedMenu = new QGraphicsRectItem(QRectF(scene->sceneRect()));
        pausedMenu->setBrush(QBrush(QColor(255, 255, 255, 128)));
        pausedMenu->setZValue(100);

        QGraphicsBlurEffect *pauseMenuEffect = new QGraphicsBlurEffect();
        pauseMenuEffect->setBlurRadius(100);
        pausedMenu->setGraphicsEffect(pauseMenuEffect);
        scene->addItem(pausedMenu);
        resumeGameButton = new Button("路径1", "路径2", 550, 350);
        resumeGameButton->setParentItem(pausedMenu);
        resumeGameButton->setZValue(101);
        scene->addItem(resumeGameButton);
    }
}

void GameScene::onResumeButtonClicked()
{
    resumeScene();
    if (pausedMenu)
    {
        scene->removeItem(pausedMenu);
        scene->removeItem(resumeGameButton);
        delete pausedMenu;
        delete resumeGameButton;
        pausedMenu = nullptr;
        resumeGameButton = nullptr;
    }
}
void GameScene::updatePlayerLives(int lives)
{
    healthTextItem->setPlainText(QString("HEALTH: %1").arg(lives));
}

void GameScene::onEnemyDead(int reward, Enemy* enemyToBeDelete)
{
    player->earnMoney(reward);
    scene->removeItem(enemyToBeDelete);
    enemies.removeOne(enemyToBeDelete);
    delete enemyToBeDelete;
}


void GameScene::onEnemyArrive(int damage, Enemy* enemyToBeDelete)
{
    player->loseLife(damage);
    scene->removeItem(enemyToBeDelete);
    enemies.removeOne(enemyToBeDelete);
    delete enemyToBeDelete;
}
void GameScene::addTower(TowerFrame *tower)
{
    scene->addItem(tower);
    tower->setZValue(20);
    towers.append(tower);
}

void GameScene::addEnemy()
{
    int enemyType = map->getEnemyTypes();
    switch (enemyType)
    {
    case 0:
        break;
    case 1:
    {
        DeadAlive* deadAlive = new DeadAlive(map->getPath());
        scene->addItem(deadAlive);
        deadAlive->setZValue(1);
        enemies.append(deadAlive);
        break;
    }
    case 2:
    {
        Wilder *wilder = new Wilder(map->getPath());
        scene->addItem(wilder);
        wilder->setZValue(1);
        enemies.append(wilder);
        break;
    }
    case 3:
    {
        Melisandre *melisandre = new Melisandre(map->getPath());
        scene->addItem(melisandre);
        melisandre->setZValue(1);
        enemies.append(melisandre);
        break;
    }
    case 4:
    {
        Vesalion *vesalion = new Vesalion(map->getPath());
        scene->addItem(vesalion);
        vesalion->setZValue(1);
        enemies.append(vesalion);
        break;
    }
    case 5:
    {
        NightKing *nightKing = new NightKing(map->getPath());
        scene->addItem(nightKing);
        nightKing->setZValue(1);
        enemies.append(nightKing);
        break;
    }
    case 6:
    {
        LannisterSoldier* lannisterSoldier = new LannisterSoldier(map->getPath());
        scene->addItem(lannisterSoldier);
        lannisterSoldier->setZValue(1);
        enemies.append(lannisterSoldier);
        break;
    }
    case 7:
    {
        GreyjoySoldier* greyjoySoldier = new GreyjoySoldier(map->getPath());
        scene->addItem(greyjoySoldier);
        greyjoySoldier->setZValue(1);
        enemies.append(greyjoySoldier);
        break;
    }
    case 8:
    {
        Mountain* mountain = new Mountain(map->getPath());
        scene->addItem(mountain);
        mountain->setZValue(1);
        enemies.append(mountain);
        break;
    }
    case 9:
    {
        KingSlayer* kingSlayer = new KingSlayer(map->getPath());
        scene->addItem(kingSlayer);
        kingSlayer->setZValue(1);
        enemies.append(kingSlayer);
        break;
    }
    default:
        //todo
        //-1时敌人传输完成
        break;
    }
    connect(enemies.last(),&Enemy::isDead,this, &GameScene::onEnemyDead);
    connect(enemies.last(),&Enemy::isArrived,this,&GameScene::onEnemyArrive);
}

void GameScene::addObstacles()
{
    QVector<QPair<QPoint,int>> obsPos = map->getObsPosType();
    for (int i = 0; i < obsPos.size(); i++)
    {
        QPoint toScenePos(obsPos[i].first.x()*CELL_SIZE,obsPos[i].first.y()*CELL_SIZE);
        //todo加上price和health
        Obstacle *obstacle = new Obstacle(toScenePos,obsPos[i].second);
        scene->addItem(obstacle);
        obstacle->setZValue(10);
        obstacles.append(obstacle);

    }
}

void GameScene::updateScene()
{
    scene->update();
}

void GameScene::pauseScene()
{
    for (Enemy *i : enemies)
    {
        i->enemyPause();
    }
    for (TowerFrame *i : towers)
    {
        i->towerPause();
    }
}
void GameScene::resumeScene()
{
    for (Enemy *i : enemies)
    {
        i->enemyResume();
    }
    for (TowerFrame *i : towers)
    {
        i->towerResume();
    }
}
void GameScene::mousePressEvent(QMouseEvent *event)
{
    QPointF pressPos = event->pos();
    QPoint pressPosInt = pressPos.toPoint();
    if (map->isPlaceAble(pressPosInt))
    {
        pauseScene();
        towerSelectMenu = new TowerSelectMenu(pressPosInt);
        scene->addItem(towerSelectMenu);
        towerSelectMenu->setZValue(95);
        connect(towerSelectMenu, &TowerSelectMenu::selectTowerType, this, &GameScene::onTowerSelectButtonClicked);
        connect(towerSelectMenu, &::TowerSelectMenu::closeTowerSelectMenu, [=]()
        {
            scene->removeItem(towerSelectMenu);
            delete towerSelectMenu; });
    }
}

void GameScene::closeEvent(QCloseEvent *event)
{
    emit gameEnd();
    event->accept();
}

void GameScene::loadMap(int level)
{
    map->load(level,isHardMode);
    addObstacles();

    // todo
    // 背景怎么办
}
