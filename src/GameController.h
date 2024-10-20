#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include <QObject>
#include "GameScene.h"
#include "MainMenu.h"
#include <QFile>
#include <QMediaPlayer>
#include <QAudioOutput>

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
    float volumnLevel; // range:0.0~1.0, equal to 0% to 100% in settingMenu.
    int gameBgm;
    GameScene *gameScene_;
    MainMenu *mainMenu_;
    QString archiveFileRoute;
    QMediaPlayer *bgmPlayer;
    QAudioOutput *bgmOutput;

private slots:
    void startGame();
    void endGame();
    void exitGame();
    void showSettingMenu();
    void showLevelSelectMenu();
    void loadLevel(int level);
    void changeVolumn(float volumn);
    void startHardMode(bool hardmode);
    void changeGameBgm(int bgm);

signals://By TrroJay
    void emitMaxLevel(int maxLevel_);

};
#endif // GAMECONTROLLER_H
