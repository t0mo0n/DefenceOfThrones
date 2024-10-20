#include "Player.h"

Player::Player(int money,int lives,QWidget *parent)
    : QWidget{parent}
{

    shilling=money;
    health=lives;

}

void Player::spendMoney(int amount)
{

    if (amount <= shilling) {
        shilling -= amount;
        emit moneyChanged(shilling);
    } else {
        emit notEnoughMoney();  // 发出金币不足的信号
    }
}

void Player::earnMoney(int amount)
{
    shilling+=amount;
    emit moneyChanged(shilling);
}

void Player::loseLife(int damage)
{
    if (health > 0) {
        health-=damage;
        emit lifeChanged(health);  // 发出生命值变化的信号

        if (health <= 0) {
            emit gameOver();  // 发出游戏结束的信号
        }
    }
}

int Player::curMoney()
{
    return shilling;
}
//在主函数适当位置connect(enemy, &Enemy::isArrived, player, &Player::loseLife);
