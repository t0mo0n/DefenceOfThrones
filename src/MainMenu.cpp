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
    pixMainMenuBackground.load(":/img/asset/mainMenuBackground.jpg");
    pixShield.load(":/img/asset/shield.png");

    //set preAnimation



    //set scrolling
    QTimer *timer =new QTimer(this);
    connect(timer,&QTimer::timeout,this,&MainMenu::updateOffset);
    timer->start(20);


    //init font
    int fontId = QFontDatabase::addApplicationFont(":/font/font/Mason Regular.ttf");
    QString fontFamily =QFontDatabase::applicationFontFamilies(fontId).at(0);
    QFont btnFont(fontFamily);
    QFont labelFont(fontFamily);
    QFont comboFont(fontFamily);
    btnFont.setPointSize(OriginSize);
    btnFont.setWeight(QFont::Bold);
    labelFont.setPointSize(OriginSize+4);
    labelFont.setWeight(QFont::Bold);
    comboFont.setPointSize(OriginSize-4);

    //init original buttons
    for(int i=0;i<4;i++){
        buttons[i]->setGeometry(510+i*5,260+i*75,BTNW-i*10,BTNH-i*5);
        buttons[i]->setFont(btnFont);
        QString styleSheet =QString(
            "QPushButton{"
            "color: black;"
            "border-image:url(%1);"
            "width: 280px;"
            "height: 100px;"
            "}"
            ).arg(buttonsPix[i]);
        buttons[i]->setStyleSheet(styleSheet);
    }

    mainMenuLayout=new QVBoxLayout;
    for (int var = 0; var < 4; ++var) {
        mainMenuLayout->addWidget(buttons[var]);
    }


    //init setting btns
    int labelX=520;
    int barX=520;
    int barW=150;
    int barH=18;

        //return btn
    backMainMenu1=new QPushButton("BACK",this);
    backMainMenu1->setGeometry(510+3*5,260+3*75,BTNW-3*10,BTNH-3*5);
    backMainMenu1->setFont(btnFont);
    backMainMenu1->setStyleSheet(
        "QPushButton{"
        "color: black;"
        "border-image:url(:/img/asset/button3.png);"
        "width: 280px;"
        "height: 100px;"
        "}"
        );
    backMainMenu1->hide();

        //set volume
    volumeLabel =new QLabel("VOLUME:50",this);
    volumeLabel->setFont(labelFont);
    volumeLabel->move(labelX,250);
    volumeLabel->setFixedSize(150,60);
    volumeLabel->hide();
    volumeLabel->setStyleSheet(
        "QLabel{"
        "background-position:center;"
        "background-repeat:no-repeat;"
        "color:#DEDEDE;"
        "}"
        );


    volumeSlider=new QSlider(Qt::Horizontal,this);
    volumeSlider->setRange(0,100);
    volumeSlider->setValue(50);
    volumeSlider->setFixedWidth(barW);
    volumeSlider->move(barX,300);
    volumeSlider->hide();
    volumeSlider->setStyleSheet(
        "QSlider::groove:horizontal {"
        "    border: 1px solid #918376;"
        "    height: 160px;"
        "    background: #918376;"
        "    margin: 0px 0;"
        "}"
        "QSlider::handle:horizontal {"
        "    background: #742b2b;"
        "    border: 1px solid #742b2b;"
        "    width: 26px;"
        "    margin: -2px 0;"
        "    border-radius: 3px;"
        "}"
        );


    connect(volumeSlider,&QSlider::valueChanged,this,[=](int value){
        volumeLabel->setText(QString("VOLUME:%1").arg(value));
        emit volumeChanged(value/100.0);
    });


        //set hard mode

    hardModeLabel =new QLabel("MODE:",this);
    hardModeLabel->move(labelX,330);
    hardModeLabel->setFont(labelFont);
    hardModeLabel->hide();
    hardModeLabel->setStyleSheet(
        "QLabel{"
        "background-position:center;"
        "background-repeat:no-repeat;"
        "}"
        );

    hardModeComboBox=new QComboBox(this);
    hardModeComboBox->move(barX,365);
    hardModeComboBox->setFont(comboFont);
    hardModeComboBox->addItem("EASY");
    hardModeComboBox->addItem("HARD");
    hardModeComboBox->setFixedSize(barW,barH);
    hardModeComboBox->hide();
    hardModeComboBox->setStyleSheet(
        "QComboBox {"
        "    border: 0px solid gray;"
        "    border-radius: 0px;"
        "    padding: 1px 18px 1px 3px;"
        "    background-color: #918376;"
        "    color: black;"
        "}"
        "QComboBox::drop-down {"
        "    subcontrol-origin: padding;"
        "    subcontrol-position: top right;"
        "    width: 18px;"
        "    border-left-width: 0px;"
        "    border-left-color: #918376;"
        "    border-left-style: solid;"
        "    border-top-right-radius: 3px;"
        "    border-bottom-right-radius: 3px;"
        "}"
        "QComboBox QAbstractItemView {"
        "    background-color: #918376;"
        "    selection-background-color: #918376;"
        "}"
        );

    connect(hardModeComboBox,&QComboBox::currentTextChanged,this,
            [=](QString text){
                if(text=="Easy"){
                    emit hardModeChanged(false);
                }else{
                    emit hardModeChanged(true);
                }
            });

        //set bgm


    bgmChangedLabel =new QLabel("BGM:",this);
    bgmChangedLabel->move(labelX,400);
    bgmChangedLabel->setFont(labelFont);
    bgmChangedLabel->hide();
    bgmChangedLabel->setStyleSheet(
        "QLabel{"
        "background-position:center;"
        "background-repeat:no-repeat;"
        "}"
        );

    bgmChangedComboBox=new QComboBox(this);
    bgmChangedComboBox->setFont(comboFont);
    bgmChangedComboBox->addItem("Jenny of Oldstones");
    bgmChangedComboBox->addItem("Light of Nibel");
    bgmChangedComboBox->addItem("Light of the Seven");
    bgmChangedComboBox->addItem("the Night King");
    bgmChangedComboBox->addItem("the Rains of Castamere");
    bgmChangedComboBox->move(barX,435);
    bgmChangedComboBox->setFixedSize(barW,barH);
    bgmChangedComboBox->hide();
    bgmChangedComboBox->setStyleSheet(
        "QComboBox {"
        "    border: 0px solid gray;"
        "    border-radius: 0px;"
        "    padding: 1px 18px 1px 3px;"
        "    background-color: #918376;"
        "    color: black;"
        "}"
        "QComboBox::drop-down {"
        "    subcontrol-origin: padding;"
        "    subcontrol-position: top right;"
        "    width: 18px;"
        "    border-left-width: 1px;"
        "    border-left-color: #918376;"
        "    border-left-style: solid;"
        "    border-top-right-radius: 3px;"
        "    border-bottom-right-radius: 3px;"
        "}"
        "QComboBox QAbstractItemView {"
        "    background-color: #918376;"
        "    selection-background-color: #918376;"
        "}"
        );

    connect(hardModeComboBox,&QComboBox::currentTextChanged,this,
            [=](QString text){
                if(text=="Easy"){
                    emit hardModeChanged(false);
                }else{
                    emit hardModeChanged(true);
                }
            });



    connect(bgmChangedComboBox,&QComboBox::currentTextChanged,this,
            [=](QString text){
                if(text=="Jenny of Oldstones"){
                    emit gameBgmChanged(4);
                }else if(text=="Light of Nibel"){
                    emit gameBgmChanged(5);
                }else if(text=="Light of the Seven"){
                    emit gameBgmChanged(2);
                }else if(text=="the Night King"){
                    emit gameBgmChanged(3);
                }else{
                    emit gameBgmChanged(1);
                }
            });



    //set levelselectmenu

    backMainMenu2=new QPushButton("BACK",this);
    backMainMenu2->setGeometry(510+3*5,260+3*75,BTNW-3*10,BTNH-3*5);
    backMainMenu2->setFont(btnFont);
    backMainMenu2->setStyleSheet(
        "QPushButton{"
        "color: black;"
        "border-image:url(:/img/asset/button3.png);"
        "width: 280px;"
        "height: 100px;"
        "}"
        );
    backMainMenu2->hide();
    for(int i=0;i<3;i++){
        levelButtons[i]->setGeometry(510+i*5,260+i*75,BTNW-i*10,BTNH-i*5);
        levelButtons[i]->setFont(btnFont);
        levelButtons[i]->hide();
        levelButtons[i]->setStyleSheet(
             "QPushButton{"
             "color: black;"
             "border-image:url(:/img/asset/button3.png);"
             "width: 280px;"
             "height: 100px;"
             "}"
            );
    }

    connect(levelButtons[0],&QPushButton::clicked,this,[=](){
        emit selectLevel(1);
    });
    connect(levelButtons[1],&QPushButton::clicked,this,[=](){
        emit selectLevel(2);
    });
    connect(levelButtons[2],&QPushButton::clicked,this,[=](){
        emit selectLevel(3);
    });

    //set change widget signal
    connect(buttons[0],&QPushButton::clicked,this,[=](){
        emit startNewGame();
    });
    connect(buttons[1],&QPushButton::clicked,this,[=](){
        qDebug()<<maxLevel<<1111;
        emit openLevelMenu();
        showLevelSelect();
    });
    connect(buttons[2],&QPushButton::clicked,this,&MainMenu::showSettings);
    connect(buttons[3],&QPushButton::clicked,this,[=](){
        emit exitGame();
    });

    connect(backMainMenu1,&QPushButton::clicked,this,&MainMenu::hideSettings);
    connect(backMainMenu2,&QPushButton::clicked,this,&MainMenu::hideLevelSelect);
}

void MainMenu::paintEvent(QPaintEvent *event){
    //实例化画家
    QPainter painter(this);

    //QPixmap pix()
    painter.drawPixmap(yOffset,0,this->width(),this->height(),pixMainMenuBackground);
    painter.drawPixmap(yOffset+this->width(),0,this->width(),this->height(),pixMainMenuBackground);
    painter.drawPixmap(440,100,400,600,pixShield);
    if(yOffset<=-(this->width())){
        yOffset=0;
    }

}

MainMenu::~MainMenu()
{
    delete ui;
}
