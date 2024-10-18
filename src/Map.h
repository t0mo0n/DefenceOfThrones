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
    const QVector<QPoint>& getSpawnPoints() const{
        return spawnPoints;
    }
    const QVector<QPoint>& getPath() const{
        return enemyPath;
    }
    int getEnemySpawnInterval() const{
        return enemySpawnInterval;
    }
    int getEnemyTypes() {
        enemyNum++;
        if(enemyNum>=enemyTotalNum){
            qDebug()<<"get too much enemy"<<endl;
        }
        return enemyTypes[enemyNum];
    }
    //TODO: obstacles

private:

    //player info
    int playerHealth;
    int playerMoney;

    //map info
    QVector<QPoint> spawnPoints;

    //enermy info
    QVector<QPoint> enemyPath;
    int enemySpawnInterval;
    QVector<int> enemyTypes;// 用于存储敌人的类型
    int enemyNum=-1;
    int enemyTotalNum=0;

    //obstacles
    QVector<QPair<QPoint,int>> obsPos;
};


#endif // MAP_H
