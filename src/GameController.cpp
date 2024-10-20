#include "GameController.h"
#include <QJsonObject>
#include <QJsonDocument>
#include <QDir>
#include <QCoreApplication>


GameController::GameController(QObject *parent)
    : QObject(parent)
{
    archiveFileRoute = "C:/dotFiles/archive.json"; // 测试用文件路径，打包时不用这个
    // archiveFileRoute = "/dotFiles/archive.json"; // 发布版本使用的文件路径，在exe文件同个文件夹下的dotFiles下面的文件
    QFile archiveFile(archiveFileRoute);
    // 第一次开启本游戏时可能没有此存档，也没有对应文件夹，所以要判断，并且如果没有的话要新建
    QDir dir = QFileInfo(archiveFile).absoluteDir();
    if (!dir.exists()) {
        qDebug() << "Directory does not exist, creating directory:" << dir.absolutePath();
        if (!dir.mkpath(".")) {
            qWarning() << "Failed to create directory:" << dir.absolutePath();
            return;
        }
    }

    if (archiveFile.exists()){
        // exist, open and read
        if (archiveFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QByteArray fileData = archiveFile.readAll();
            QJsonDocument jsonDoc(QJsonDocument::fromJson(fileData));
            QJsonObject jsonObj = jsonDoc.object();

            maxLevel = jsonObj["maxLevel"].toInt();
            hardMode = jsonObj["hardMode"].toBool();
            volumnLevel = jsonObj["volumnLevel"].toInt();
            gameBgm = jsonObj["gameBgm"].toInt();

            archiveFile.close();
        } else {
            qWarning() << "无法打开文件进行读取";
        }
    } else{
        // write and fill with fundenmental data
        if (archiveFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QJsonObject jsonObj;

            jsonObj["maxLevel"] = 1;
            jsonObj["hardMode"] = false;
            jsonObj["volumnLevel"] = 50;
            jsonObj["gameBgm"] = 1;

            QJsonDocument jsonDoc(jsonObj);
            archiveFile.write(jsonDoc.toJson());

            archiveFile.close();

            maxLevel = 1;
            hardMode = false;
            volumnLevel = 50;
            gameBgm = 1;
        } else {
            qWarning() << "无法创建文件";
        }
    }

    currentLevel = maxLevel;

    gameScene_ = nullptr;
    mainMenu_ = new MainMenu();
    mainMenu_->show();

    connect(mainMenu_,&MainMenu::startNewGame,this,&GameController::startGame);
    connect(mainMenu_,&MainMenu::exitGame,this,&GameController::exitGame);
    connect(mainMenu_,&MainMenu::openSettingMenu,this,&GameController::showSettingMenu);
    connect(mainMenu_,&MainMenu::openLevelMenu,this,&GameController::showLevelSelectMenu);

    // 根据gameBgm的数值来生成对应的游戏背景音乐
    bgmPlayer = new QMediaPlayer(this);
    bgmOutput = new QAudioOutput(this);
    bgmOutput->setVolume(volumnLevel);
    bgmPlayer->setAudioOutput(bgmOutput);
    changeGameBgm(gameBgm);
}

GameController::~GameController() {
    QFile archiveFile(archiveFileRoute);

    if (archiveFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QJsonObject jsonObj;

        jsonObj["maxLevel"] = maxLevel;
        jsonObj["hardMode"] = hardMode;
        jsonObj["volumnLevel"] = volumnLevel;
        jsonObj["gameBgm"] = gameBgm;

        QJsonDocument jsonDoc(jsonObj);
        archiveFile.write(jsonDoc.toJson());

        archiveFile.close();
    } else {
        qWarning() << "无法打开文件进行写入";
    }

    // 关闭Bgm的Media设备
    bgmPlayer->stop();
    delete bgmOutput;
    delete bgmPlayer;

    delete gameScene_;
    delete mainMenu_;
}

void GameController::startGame()
{
    // gameScene_ = new GameScene(currentLevel,hardMode);
    // mainMenu_->hide();
    // connect(gameScene_,&GameScene::gameEnd,this,&GameController::endGame);
    // gameScene_->show();
}

void GameController::endGame()
{
    delete gameScene_;
    gameScene_ = nullptr;
    mainMenu_->show();
}

void GameController::exitGame()
{
    delete gameScene_;
    delete mainMenu_;

    QCoreApplication::quit();
}

void GameController::showSettingMenu()
{
    connect(mainMenu_,&MainMenu::volumeChanged,this,&GameController::changeVolumn);
    connect(mainMenu_,&MainMenu::gameBgmChanged,this,&GameController::changeGameBgm);
}

void GameController::showLevelSelectMenu()
{
    connect(this,&GameController::emitMaxLevel,mainMenu_,&MainMenu::recieveMaxLevel);
    emit emitMaxLevel(maxLevel);
    connect(mainMenu_,&MainMenu::selectLevel,this,&GameController::loadLevel);
}

void GameController::loadLevel(int level)
{
    currentLevel = level;
    startGame();
}

void GameController::changeVolumn(float volumn)
{
    volumnLevel = volumn;
    bgmOutput->setVolume(volumnLevel);
}

void GameController::startHardMode(bool hardmode)
{
    hardMode = hardmode;
}

void GameController::changeGameBgm(int bgm)
{
    gameBgm = bgm;
    switch (gameBgm){
    case 1:
        bgmPlayer->setSource(QUrl("qrc:/sound/music/The_Rains_of_Castamere.mp3")); // The Rains of Castamere
        break;
    case 2:
        bgmPlayer->setSource(QUrl("qrc:/sound/music/Light_of_the_Seven_-_Ramin_Djawadi_Complete_Transcription.mp3"));
        break;
    case 3:
        bgmPlayer->setSource(QUrl("qrc:/sound/music/The_Night_King_-_Ramin_Djawadi.mp3"));
        break;
    case 4:
        bgmPlayer->setSource(QUrl("qrc:/sound/music/Jenny_of_Oldstones_.mp3"));
        break;
    case 5:
        bgmPlayer->setSource(QUrl("qrc:/sound/music/Light_of_Nibel_-_Ori_and_the_Blind_Forest.mp3"));
        break;
    default:
        bgmPlayer->setSource(QUrl("qrc:/sound/music/The_Night_King_-_Ramin_Djawadi.mp3"));
        qDebug() << "error bgm";
        break;
    }
    bgmPlayer->setLoops(-1);
    bgmPlayer->play();
}


