#include "LevelSelectMenu.h"

LevelSelectMenu::LevelSelectMenu(int maxLevel_,QWidget *parent)
    : QDialog{parent},maxLevel(maxLevel_)
{
    this->setFixedSize(1200,800);
    this->setWindowTitle("Defense of Thrones");

    for (int var = 0; var < 3; ++var) {
        levelButtons[var]->setGeometry(50+var*100,50,100,80);
        levelButtons[var]->setStyleSheet(
            "QPushButton{"
            "border-image:url(:/img/asset/1.png);"
            "}"
            "QPushButton:pressed{"
            "border-image:url(:/img/asset/1.png);"
            "}");
    }

}
void LevelSelectMenu::paintEvent(QPaintEvent *event){
    QPainter painter(this);
    QPixmap pixMainMenuBackground(":/imgBackground/asset/mainMenuBackground.jpg");
    painter.drawPixmap(0,0,this->width(),this->height(),pixMainMenuBackground);

    QPixmap lockPix(":/img/asset/1.png");
    for (int var = 0; var < maxLevel; ++var) {
        painter.drawPixmap(50+var*100,50,100,100,lockPix);
    }

}
