#ifndef MAP_H
#define MAP_H

#include <QObject>
#include <QPoint>

class Map : public QObject {
    Q_OBJECT

public:
    Map(QObject *parent = nullptr);

    void loadMap(int level);
    QVector<QPoint> getSpawnPoints() const;
    QVector<QPoint> getPath() const;
    int getEnemySpawnInterval() const;
    QVector<int> getEnemyTypes() const;

private:

    QVector<QPoint> spawnPoints;
    QVector<QPoint> enemyPath;
    int enemySpawnInterval;
    QVector<int> enemyTypes; // 用于存储敌人的类型
};


#endif // MAP_H
