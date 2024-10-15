#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include <QObject>
#include "GameScene.h"
#include "LevelSelectMenu.h"
#include "SettingsMenu.h"
#include "MainMenu.h"
#include <QFile>

class GameController : public QObject
{
    Q_OBJECT

public:
    GameController(QObject *parent = nullptr);
    ~GameController();

private:
    int currentLevel;
    int maxLevel;
    bool hardMode;
    int volumnLevel;
    int gameBgm;
    GameScene *gameScene_;
    LevelSelectMenu *lvMenu_;
    SettingsMenu *settingMenu_;
    MainMenu *mainMenu_;

    QString archiveFileRoute;

private slots:
    void startGame();
    void endGame();
    void exitGame();
    void showSettingMenu();
    void showLevelSelectMenu();
    void loadLevel(int level);
    void changeVolumn(int volumn);
    void startHardMode(bool hardmode);
    void changeGameBgm(int gameBgm);


};
#endif // GAMECONTROLLER_H
