#include <QGraphicsBlurEffect>
#include "GameScene.h"
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
#define SHILLING 100
#define HEALTH 20
GameScene::GameScene(int level, bool isHardMode, QGraphicsView *parent)
    : QGraphicsView(parent)
{
    this->setWindowIcon(QIcon(":/img/asset/GOT.jpg"));
    this->setFixedSize(1200,800);
    this->setWindowTitle("Let's Play!");
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->level = level;
    this->isHardMode = isHardMode;
    this->map = new Map();
    scene = new QGraphicsScene(0,0,1200,800,this);
    this->setScene(scene);
    // this->fitInView(scene->sceneRect(),Qt::KeepAspectRatio);
    this->setGeometry(0,0,1200,800);
    loadMap(level);
    player = new Player(map->getPlayerMoney(),map->getPlayerHealth());
    pauseGameButton = new Button(":/img/asset/button.png", ":/img/asset/button2.png", 1000, 700);//暂停按钮图片1为正常时，2为鼠标点击时
    scene->addItem(pauseGameButton);
    pauseGameButton->setZValue(90);
    connect(pauseGameButton,&Button::clicked,this,&GameScene::onPauseButtonClicked);

    gameEndButton = new Button(":/img/asset/button1.png", ":/img/asset/button2.png", 1100, 700);//结束按钮图片
    scene->addItem(gameEndButton);
    gameEndButton->setZValue(90);
    connect(gameEndButton,&Button::clicked,this,&GameScene::onGameEndButtonClicked);
    resumeGameButton = nullptr;
    pausedMenu = nullptr;

    healthTextItem = new QGraphicsTextItem(QString("HEALTH: %1").arg(map->getPlayerHealth()));
    scene->addItem(healthTextItem);
    healthTextItem->setPos(1000, 0);
    healthTextItem->setDefaultTextColor(Qt::red);
    healthTextItem->setZValue(90);
    connect(player, &Player::lifeChanged, this, &GameScene::updatePlayerLives);

    moneyTextItem = new QGraphicsTextItem(QString("SHILLING: %1").arg(map->getPlayerMoney()));
    moneyTextItem->setPos(1000, 100);
    moneyTextItem->setDefaultTextColor(Qt::yellow);
    healthTextItem->setZValue(90);
    connect(player, &Player::moneyChanged, this, [=](int newAmount)
            { this->moneyTextItem->setPlainText(QString("SHILLING: %1").arg(newAmount)); });

    towerSelectMenu = nullptr;

    QTimer *updateTimer = new QTimer(this);
    updateTimer->start(50);
    connect(updateTimer, &QTimer::timeout, this, &GameScene::updateScene);

    QTimer *enemyTimer = new QTimer(this);
    if (isHardMode)
    {
        enemyTimer->start(1500);
    }
    else
    {
        enemyTimer->start(2000);
    }

    ecount = 0;
    connect(enemyTimer, &QTimer::timeout, this,[=](){
        ecount++;
        qDebug() << ecount;
        addEnemy();
    });

}
void GameScene::onGameEndButtonClicked()
{
    emit gameEnd();
    close();
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
        connect(resumeGameButton,&Button::clicked,this,&GameScene::onResumeButtonClicked);
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

void GameScene::onEnemyDead(int reward, Enemy *enemyToBeDelete)
{
    player->earnMoney(reward);
    scene->removeItem(enemyToBeDelete);
    enemies.removeOne(enemyToBeDelete);
    delete enemyToBeDelete;
}

void GameScene::onEnemyArrive(int damage, Enemy *enemyToBeDelete)
{
    player->loseLife(damage);
    scene->removeItem(enemyToBeDelete);
    enemies.removeOne(enemyToBeDelete);
    delete enemyToBeDelete;
}

void GameScene::onTowerSelectButtonClicked(QPoint cellPos, int type)
{
    switch (type)
    {
    case 1:
    {
        Archer *archer = new Archer(cellPos);
        scene->addItem(archer);
        towers.append(archer);
        archer->setZValue(20);
        //扣钱
        player->spendMoney(archer->getBuyCost());
        connect(archer,&Archer::towerUpdate,this,[=](int cost,TowerFrame* toBeUpgrade){
            if(cost <= player->curMoney())
            {
                toBeUpgrade->upgrade();
                onTowerUpdated(cost);
            }
        });
        connect(archer, &Archer::sell,[=](TowerFrame* towerToBeDelete){
            player->earnMoney(towerToBeDelete->getSellPrice());
            towers.removeOne(towerToBeDelete);
            scene->removeItem(towerToBeDelete);
            delete towerToBeDelete;
        });
        //liang
        break;
    }
    case 2:
    {
        StoneThrower *stoneThrower = new StoneThrower(cellPos);
        scene->addItem(stoneThrower);
        towers.append(stoneThrower);
        stoneThrower->setZValue(20);
        player->spendMoney(stoneThrower->getBuyCost());
        connect(stoneThrower,&StoneThrower::towerUpdate,[=](int cost,TowerFrame* toBeUpgrade){
            if(cost <= player->curMoney())
            {
                toBeUpgrade->upgrade();
                onTowerUpdated(cost);
            }
        });

        connect(stoneThrower, &StoneThrower::sell,[=](TowerFrame* towerToBeDelete){

            player->earnMoney(towerToBeDelete->getSellPrice());
            towers.removeOne(towerToBeDelete);
            scene->removeItem(towerToBeDelete);
            delete towerToBeDelete;
        });
        break;
    }
    case 3:
    {
        JohnSnow *johnSnow = new JohnSnow(cellPos);
        scene->addItem(johnSnow);
        towers.append(johnSnow);
        johnSnow->setZValue(20);
        player->spendMoney(johnSnow->getBuyCost());
        connect(johnSnow ,&JohnSnow::towerUpdate,this,[=](int cost,TowerFrame* toBeUpgrade){
            if(cost <= player->curMoney())
            {
                toBeUpgrade->upgrade();
                onTowerUpdated(cost);
            }
        });
        connect(johnSnow, &JohnSnow::sell,[=](TowerFrame* towerToBeDelete){
            player->earnMoney(towerToBeDelete->getSellPrice());
            towers.removeOne(towerToBeDelete);
            scene->removeItem(towerToBeDelete);
            delete towerToBeDelete;
        });
        break;
    }
    case 4:
    {
        Dragon *dragon = new Dragon(cellPos);
        scene->addItem(dragon);
        towers.append(dragon);
        dragon->setZValue(20);
        player->spendMoney(dragon->getBuyCost());
        connect(dragon,&Dragon::towerUpdate,[=](int cost,TowerFrame* toBeUpgrade){
            if(cost <= player->curMoney())
            {
                toBeUpgrade->upgrade();
                onTowerUpdated(cost);
            }
        });
        connect(dragon, &Dragon::sell,[=](TowerFrame* towerToBeDelete){
            player->earnMoney(towerToBeDelete->getSellPrice());
            towers.removeOne(towerToBeDelete);
            scene->removeItem(towerToBeDelete);
            delete towerToBeDelete;
        });
        break;
    }
    default:
        break;
    }
}

// void GameScene::onDeleteTowerButtonClicked(int cost)
// {
//     player->earnMoney(cost);
// }

void GameScene::onTowerUpdated(int cost)
{
    player->spendMoney(cost);
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
        DeadAlive *deadAlive = new DeadAlive(map->getPath());
        deadAlive->setZValue(10);
        scene->addItem(deadAlive);
        enemies.append(deadAlive);
        break;
    }
    case 2:
    {
        Wilder *wilder = new Wilder(map->getPath());
        scene->addItem(wilder);
        wilder->setZValue(10);
        enemies.append(wilder);
        break;
    }
    case 3:
    {
        Melisandre *melisandre = new Melisandre(map->getPath());
        scene->addItem(melisandre);
        melisandre->setZValue(10);
        enemies.append(melisandre);
        break;
    }
    case 4:
    {
        Vesalion *vesalion = new Vesalion(map->getPath());
        scene->addItem(vesalion);
        vesalion->setZValue(10);
        enemies.append(vesalion);
        break;
    }
    case 5:
    {
        NightKing *nightKing = new NightKing(map->getPath());
        scene->addItem(nightKing);
        nightKing->setZValue(10);
        enemies.append(nightKing);
        connect(nightKing,&NightKing::generateDeadalive,[=](QVector<QPoint> newPath){
            DeadAlive *deadAlive = new DeadAlive(newPath);
            scene->addItem(deadAlive);
            deadAlive->setZValue(10);
            enemies.append(deadAlive);
            connect(deadAlive,&DeadAlive::isDead,this,&GameScene::onEnemyDead);
            connect(deadAlive,&DeadAlive::isArrived,this,&GameScene::onEnemyArrive);
        });
        break;
    }
    case 6:
    {
        LannisterSoldier *lannisterSoldier = new LannisterSoldier(map->getPath());
        scene->addItem(lannisterSoldier);
        lannisterSoldier->setZValue(10);
        enemies.append(lannisterSoldier);
        break;
    }
    case 7:
    {
        GreyjoySoldier *greyjoySoldier = new GreyjoySoldier(map->getPath());
        scene->addItem(greyjoySoldier);
        greyjoySoldier->setZValue(10);
        enemies.append(greyjoySoldier);
        break;
    }
    case 8:
    {
        Mountain *mountain = new Mountain(map->getPath());
        scene->addItem(mountain);
        mountain->setZValue(10);
        enemies.append(mountain);
        break;
    }
    case 9:
    {
        KingSlayer *kingSlayer = new KingSlayer(map->getPath());
        scene->addItem(kingSlayer);
        kingSlayer->setZValue(10);
        enemies.append(kingSlayer);
        break;
    }
    default:
        // todo
        //-1时敌人传输完成
        break;
    }
    if(enemyType!=0&&enemyType!=-1)
    {
        connect(enemies.last(), &Enemy::isDead, this, &GameScene::onEnemyDead);
        connect(enemies.last(), &Enemy::isArrived, this, &GameScene::onEnemyArrive);
    }

}

void GameScene::addObstacles()
{
    QVector<QPair<QPoint, int>> obsPos = map->getObsPosType();
    for (int i = 0; i < obsPos.size(); i++)
    {
        QPoint toScenePos((obsPos[i].first.x()-1) * CELL_SIZE, (obsPos[i].first.y()-1) * CELL_SIZE);
        // todo加上price和health
        Obstacle *obstacle = new Obstacle(obsPos[i].second, toScenePos);
        scene->addItem(obstacle);
        obstacle->setZValue(10);
        obstacles.append(obstacle);
        connect(obstacle,&Obstacle::isDamaged,this,&GameScene::onObstacleDestroyed);
    }
}
void GameScene::onObstacleDestroyed(int reward,Obstacle* toBeDelete)
{
    player->earnMoney(reward);
    scene->removeItem(toBeDelete);
    obstacles.removeOne(toBeDelete);
    delete toBeDelete;
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

// void GameScene::mousePressEvent(QMouseEvent *event)
// {
//     QPointF pressPos = event->pos();
//     QPoint pressPosInt = pressPos.toPoint();
//     if (map->isPlaceAble(pressPosInt))
//     {
//         pauseScene();
//         towerSelectMenu = new TowerSelectMenu(pressPosInt);
//         scene->addItem(towerSelectMenu);
//         towerSelectMenu->setZValue(95);

//     }
// }

void GameScene::onTowerCellClicked(QPoint clickPos)
{
    pauseScene();
    towerSelectMenu = new TowerSelectMenu(clickPos, player->curMoney());
    scene->addItem(towerSelectMenu);
    towerSelectMenu->setZValue(95);
    towerSelectMenu->setVisible(true); // 确保可见
    scene->update(); // 确保场景更新
    connect(towerSelectMenu, &TowerSelectMenu::selectTowerType, this, &GameScene::onTowerSelectButtonClicked);
    connect(towerSelectMenu, &TowerSelectMenu::closeTowerSelectMenu, [=]()
            {
                resumeScene();
                scene->removeItem(towerSelectMenu);
                delete towerSelectMenu; });
}

void GameScene::closeEvent(QCloseEvent *event)
{
    emit gameEnd();
    event->accept();
}

    void GameScene::loadMap(int level)
{
    map->load(level, isHardMode);
    addObstacles();
    // 加入towerCell
    for (int i = 0; i < 15; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            if (map->isPlaceAble(QPoint(i, j)))
            {
                TowerCell *towerCell = new TowerCell(QPoint(i * CELL_SIZE, j * CELL_SIZE));
                scene->addItem(towerCell);
                towerCell->setZValue(1);
                connect(towerCell, &TowerCell::clicked, this, &GameScene::onTowerCellClicked);
            }
        }
    }
    // 加入pathCell
    QVector<QPoint> pathPos = map->getPath();
    for (int i = 0; i < pathPos.size() - 1; i++)
    {
        QPoint startPoint = pathPos[i];
        QPoint endPoint = pathPos[i + 1];
        int dx = endPoint.x() - startPoint.x();
        int dy = endPoint.y() - startPoint.y();
        int nx = (dx > 0) ? dx : (-dx);
        int ny = (dy > 0) ? dy : (-dy);
        if (dx != 0)
        {
            for (int j = 0; j < nx; j++)
            {
                PathCell *pathCell = new PathCell("普通道路方块",QPoint((startPoint.x() + j) * CELL_SIZE, startPoint.y() * CELL_SIZE));
                scene->addItem(pathCell);
                pathCell->setZValue(1);
            }
        }
        if (dy != 0)
        {
            for (int j = 0; j < ny; j++)
            {
                PathCell *pathCell = new PathCell("普通道路方块",QPoint(startPoint.x() * CELL_SIZE, (startPoint.y() + j) * CELL_SIZE));
                scene->addItem(pathCell);
                pathCell->setZValue(1);
            }
        }
    }
    QPoint playerPos = map->getPlayerPosition();
    PathCell *endPlayer = new PathCell("终点玩家方块",QPoint(playerPos.x()*CELL_SIZE,playerPos.y()*CELL_SIZE));
    scene->addItem(endPlayer);
    endPlayer->setZValue(5);
    // todo
    // 背景怎么办
}

// void GameScene::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
// {
//     // 获取事件位置处所有的 item，最上面的 item 排在第一个
//     QList<QGraphicsItem *> itemsUnderCursor = scene->items(event->scenePos());

//     // 遍历这些 items，手动触发下层元素的 contextMenuEvent
//     for (QGraphicsItem *item : itemsUnderCursor)
//     {
//         // 创建新的 QGraphicsSceneContextMenuEvent

//         TowerFrame *tt = dynamic_cast<TowerFrame *>(item);
//         if (tt != nullptr)
//         {
//             QGraphicsSceneContextMenuEvent *newEvent = new QGraphicsSceneContextMenuEvent(QEvent::GraphicsSceneContextMenu);
//             newEvent->setScreenPos(event->screenPos()); // 设置屏幕位置
//             newEvent->setScenePos(event->scenePos());   // 设置场景位置
//             newEvent->setModifiers(event->modifiers()); // 设置键盘修饰符

//             // 调用 item 的 contextMenuEvent 以传递事件
//             tt->contextMenuEvent(newEvent);
//             if (newEvent->isAccepted())
//             {
//                 // 事件被处理了，停止传递
//                 break;
//             }
//             // 删除新建的事件，防止内存泄漏
//             delete newEvent;
//         }
//     }
// }
