#include "MainMenu.h"
#include "qpainter.h"
#include "ui_mainmenu.h"


MainMenu::MainMenu(QWidget *parent)
    : QWidget{parent}
    , ui(new Ui::MainMenu)
{
    ui->setupUi(this);

    //init mainwindow
    this->setFixedSize(1200,800);
    this->setWindowTitle("Defense of Thrones");

    //init buttons
    for(int i=0;i<4;i++){
        buttons[i]->setGeometry(50,50+i*100,200,100);
        QString styleSheet =QString(
            "QPushButton{"
            "border-image:url(%1);"
            "}"
            "QPushButton:pressed{"
            "border-image:url(%2);"
            "}").arg(buttonsPix[i]).arg(buttonsPix[i]);
        buttons[i]->setStyleSheet(styleSheet);
    }

    //click button
    connect(buttons[0],&QPushButton::clicked,this,[=](){
        emit startNewGame();
    });
    connect(buttons[1],&QPushButton::clicked,this,[=](){
        emit openLevelMenu();
    });
    connect(buttons[2],&QPushButton::clicked,this,[=](){
        emit openSettingMenu();
    });
    connect(buttons[3],&QPushButton::clicked,this,[=](){
        emit exitGame();
    });


}

void MainMenu::paintEvent(QPaintEvent *event){
    //实例化画家
    QPainter painter(this);

    //QPixmap pix()
    QPixmap pixMainMenuBackground(":/imgBackground/asset/mainMenuBackground.jpg");
    painter.drawPixmap(0,0,this->width(),this->height(),pixMainMenuBackground);
}

MainMenu::~MainMenu()
{
    delete ui;
}
