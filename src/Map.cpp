#include "Map.h"


Map::Map(QObject *parent)
    : QObject(parent),
    playerHealth(0),playerMoney(0), enemySpawnInterval(1000) {
}

void Map::load(int level,bool isHardMode) {
    //根据关卡载入地图和敌人生成信息
    //示例代码，实际实现需要根据具体关卡信息进行调整
    if (level == 1) {
        if(!isHardMode){
            QFile file
        }else{

        }
        spawnPoints = {QPoint(0, 0)};
        enemyPath = {QPoint(0, 0), QPoint(1, 0), QPoint(1, 1)};
        enemySpawnInterval = 1000; // 每秒生成一个敌人
        enemyTypes = {1, 2, 1}; // 敌人的类型
    }
}

