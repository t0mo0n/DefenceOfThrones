#ifndef PLAYER_H
#define PLAYER_H
#include<QWidget>
#include <QObject>
#include"Enemy.h"

class Player : public QWidget
{
    Q_OBJECT


private:
    int shilling;//玩家拥有的金币数
    int health;//当前生命值

public:
    explicit Player(int money,int lives,QWidget *parent = nullptr);
    void spendMoney(int amount);// 消耗金币
    void earnMoney(int amount);// 获得金币
    void loseLife(int damage);// 玩家失去生命 (顺便判断玩家是否失去所有生命)
    int curMoney();//当前金币
signals:
    void moneyChanged(int newAmount);  // 金钱变化信号
    void notEnoughMoney();              // 金钱不足信号
    void lifeChanged(int lives);        // 生命值变化信号
    void gameOver();                    // 游戏结束信号
};

#endif // PLAYER_H
