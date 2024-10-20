#include "Map.h"


Map::Map(QObject *parent)
    : QObject(parent),
    playerHealth(0),playerMoney(0), enemySpawnInterval(1000) {
}

void Map::load(int level,bool isHardMode) {

    refresh();
    QFile file("");
    if(level==1){
        if(!isHardMode){
            file.setFileName(":/img/levelData/levelOne.json");
        }else{
            file.setFileName(":/img/levelData/levelOneHard.json");
        }
    }else if(level==2){
        if(!isHardMode){
            file.setFileName(":/img/levelData/levelTwo.json");
        }else{
            file.setFileName(":/img/levelData/levelTwoHard.json");
        }
    }else if(level==3){
        if(!isHardMode){
            file.setFileName(":/img/levelData/levelThree.json");
        }else{
            file.setFileName(":/img/levelData/levelThreeHard.json");
        }
    }


    if(!file.open(QIODevice::ReadOnly)){
        qWarning()<<"Could not open file for reading:"
                   << file.errorString();
        return;
    }

    QByteArray jsonData =file.readAll();
    file.close();

    QJsonDocument jsonDoc(QJsonDocument::fromJson(jsonData));
    if (jsonDoc.isNull()) {
        qWarning() << "Failed to create JSON doc.";
        return;
    }

    if(jsonDoc.isObject()){
        QJsonObject jsonObj =jsonDoc.object();

        //read map
        QJsonArray mapArray =jsonObj["map"].toArray();
        for (int i = 0; i < mapArray.size(); ++i) {
            QJsonArray rowArray = mapArray[i].toArray();
            for (int j = 0; j < rowArray.size(); ++j) {
                QString tile = rowArray[j].toString();
                map[i][j] = tile[0].toLatin1(); // 将 QString 转换为 char 并存储
            }
        }

        //read player
        QJsonObject playerObj =jsonObj["player"].toObject();
        QJsonArray playerPosition_ =playerObj["position"].toArray();
        playerPosition.setX(playerPosition_[0].toInt());
        playerPosition.setY(playerPosition_[1].toInt());
        playerHealth=playerObj["health"].toInt();
        playerMoney=playerObj["money"].toInt();


        //read enemy
        QJsonObject enemyObj =jsonObj["enemies"].toObject();
        QJsonArray spawnPoints_ =enemyObj["spawnPoints"].toArray();
        spawnPoints.setX(spawnPoints_[0].toInt());
        spawnPoints.setY(spawnPoints_[1].toInt());
        QJsonArray types_=enemyObj["types"].toArray();
        for(int var=0;var<types_.size();var++){
            enemyTypes.push_back(types_[var].toInt());
        }
        QJsonArray path_=enemyObj["paths"].toArray();
        for(const auto& row:path_){
            QJsonArray rowArray_ =row.toArray();
            QPoint temp(rowArray_[0].toInt(),rowArray_[1].toInt());
            enemyPath.push_back(temp);
        }

        //read obstacles
        QJsonArray obstacleArray =jsonObj["obstacles"].toArray();
        for(const auto& obstacle:obstacleArray){
            QJsonObject obstacleObject =obstacle.toObject();
            QString type =obstacleObject["type"].toString();
            QJsonArray position =obstacleObject["position"].toArray();
            QPoint temp(position[0].toInt(),position[1].toInt());
            if(type=="tree"){
                QPair<QPoint,int> tempPair(temp,0);
                obsPos.push_back(tempPair);
            }else if(type=="stone"){
                QPair<QPoint,int> tempPair(temp,1);
                obsPos.push_back(tempPair);
            }else if(type=="iceburg"){
                QPair<QPoint,int> tempPair(temp,2);
                obsPos.push_back(tempPair);
            }
        }

    }

}

void Map::refresh(){
    memset(map,0,sizeof(map));

    enemyPath.clear();
    enemyTypes.clear();

    obsPos.clear();
}

