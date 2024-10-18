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

    //init font
    // int fontId = QFontDatabase::addApplicationFont(":/font/font/Argor Got Scaqh.ttf");
    // QString fontFamily =QFontDatabase::applicationFontFamilies(fontId).at(0);
    // QFont font(fontFamily);
    // font.setPointSize(12);

    //init buttons
    for(int i=0;i<4;i++){
        buttons[i]->setGeometry(870-65*i,390+i*90,280,100);
        //buttons[i]->setFont(font);
        QString styleSheet =QString(
            "QPushButton{"
            "color: #DEDEDE;"
            "border-image:url(%1);"
            "width: 280px;"
            "height: 100px;"
            "}"
            ).arg(buttonsPix[i]);
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
    QPixmap pixMainMenuBackground(":/img/asset/mainMenuBackground.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pixMainMenuBackground);

}

MainMenu::~MainMenu()
{
    delete ui;
}
