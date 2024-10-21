#ifndef MAP_H
#define MAP_H

#include <QObject>
#include <QPoint>
#include <QPair>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QDebug>


class Map : public QObject {
    Q_OBJECT

public:
    Map(QObject *parent = nullptr);

    void load(int level,bool isHardMode);
    void refresh();

    bool isPlaceAble(QPoint pos_){
        //TODO:
        if(map[pos_.y()][pos_.x()]=='1'){
            return true;
        }
        return false;
    }
    const QPoint& getSpawnPoints() const{
        return spawnPoints;
    }
    const QVector<QPoint>& getPath() const{
        return enemyPath;
    }
    int getEnemyTypes() {
        enemyNum++;
        if(enemyNum>=enemyTotalNum){
            qDebug()<<"get too much enemy";
            return -1;
        }
        return enemyTypes[enemyNum];
    }
    int getPlayerHealth(){
        return playerHealth;
    }
    int getPlayerMoney(){
        return playerMoney;
    }
    const QPoint& getPlayerPosition(){
        return playerPosition;
    }
    const QVector<QPair<QPoint,int>>& getObsPosType(){
        return obsPos;
    }

private:

    //player info
    int playerHealth;
    int playerMoney;
    QPoint playerPosition;


    //map info
    char map[16][16]={0};
    QPoint spawnPoints;

    //enermy info
    QVector<QPoint> enemyPath;
    QVector<int> enemyTypes;// 用于存储敌人的类型
    int enemyNum=-1;
    int enemyTotalNum=0;

    //obstacles
    QVector<QPair<QPoint,int>> obsPos;
};


#endif // MAP_H
