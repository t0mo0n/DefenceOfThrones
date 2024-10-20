#include "SettingsMenu.h"

SettingsMenu::SettingsMenu(QWidget *parent)
    : QDialog{parent}
{
    this->setFixedSize(600,400);
    this->setWindowTitle("Defense of Thrones");
    //TODO:setIcon


}

void SettingsMenu::paintEvent(QPaintEvent *event){
    QPainter painter(this);

    //QPixmap pix()
    QPixmap pixMainMenuBackground(":/img/asset/otherMenu.jpg");
    painter.drawPixmap(0,0,this->width(),this->height(),pixMainMenuBackground);
}

SettingsMenu::~SettingsMenu(){
}
