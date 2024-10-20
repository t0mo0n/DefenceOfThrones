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
    // int fontId = QFontDatabase::addApplicationFont(":/font/font/Argor Got Scaqh.ttf");
    // QString fontFamily =QFontDatabase::applicationFontFamilies(fontId).at(0);
    // QFont font(fontFamily);
    // font.setPointSize(12);

    //init original buttons
    for(int i=0;i<4;i++){
        buttons[i]->setGeometry(510+i*5,260+i*75,BTNW-10-i*10,BTNH-15-i*5);
        //buttons[i]->setFont(font);
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
    QFont font("Arial",24);
    int labelX=50;
    int barX=300;
    int barW=200;
    int barH=30;

        //return btn
    backMainMenu1=new QPushButton("BACK",this);
    backMainMenu1->hide();

        //set volume
    volumeLabel =new QLabel("Volume:50",this);
    volumeLabel->setFont(font);
    volumeLabel->move(labelX,100);
    volumeLabel->setFixedSize(150,60);
    volumeLabel->hide();
    volumeLabel->setStyleSheet(
        "QLabel{"
        "border-image:url(:/img/asset/button.png);"
        "background-position:center;"
        "background-repeat:no-repeat;"
        "color:DEDEDE;"
        "}"
        );


    volumeSlider=new QSlider(Qt::Horizontal,this);
    volumeSlider->setRange(0,100);
    volumeSlider->setValue(50);
    volumeSlider->setFixedWidth(barW);
    volumeSlider->move(barX,100);
    volumeSlider->hide();
    volumeSlider->setStyleSheet(
        "QSlider::groove:horizontal {"
        "    border: 1px solid #4c4c4c;"
        "    height: 200px;"
        "    background: #4c4c4c;"
        "    margin: 2px 0;"
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
        volumeLabel->setText(QString("Volume:%1").arg(value));
        emit volumeChanged(value/100.0);
    });


        //set hard mode

    hardModeLabel =new QLabel("Mode:",this);
    hardModeLabel->move(labelX,200);
    hardModeLabel->hide();
    hardModeLabel->setStyleSheet(
        "QLabel{"
        "border-image:url(:/img/asset/button.png);"
        "background-position:center;"
        "background-repeat:no-repeat;"
        "}"
        );

    hardModeComboBox=new QComboBox(this);
    hardModeComboBox->move(barX,200);
    hardModeComboBox->addItem("Easy");
    hardModeComboBox->addItem("Hard");
    hardModeComboBox->setFixedSize(barW,barH);
    hardModeComboBox->hide();
    hardModeComboBox->setStyleSheet(
        "QComboBox {"
        "    border: 0px solid gray;"
        "    border-radius: 0px;"
        "    padding: 1px 18px 1px 3px;"
        "    color: #4c4c4c;"
        "}"
        "QComboBox::drop-down {"
        "    subcontrol-origin: padding;"
        "    subcontrol-position: top right;"
        "    width: 20px;"
        "    border-left-width: 1px;"
        "    border-left-color: darkgray;"
        "    border-left-style: solid;"
        "    border-top-right-radius: 3px;"
        "    border-bottom-right-radius: 3px;"
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


    bgmChangedLabel =new QLabel("BGM:");
    bgmChangedLabel->move(labelX,300);
    bgmChangedLabel->hide();
    bgmChangedLabel->setStyleSheet(
        "QLabel{"
        "border-image:url(:/img/asset/button.png);"
        "background-position:center;"
        "background-repeat:no-repeat;"
        "}"
        );

    bgmChangedComboBox=new QComboBox(this);
    bgmChangedComboBox->addItem("Jenny of Oldstones");
    bgmChangedComboBox->addItem("Light of Nibel");
    bgmChangedComboBox->addItem("Light of the Seven");
    bgmChangedComboBox->addItem("the Night King");
    bgmChangedComboBox->addItem("the Rains of Castamere");
    bgmChangedComboBox->move(barX,300);
    bgmChangedComboBox->setFixedSize(barW,barH);
    bgmChangedComboBox->hide();


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
    backMainMenu2->hide();
    for (int var = 0; var < 3; ++var) {
        levelButtons[var]->setGeometry(50+var*100,50,100,80);
        levelButtons[var]->hide();
        levelButtons[var]->setStyleSheet(
            "QPushButton{"
            "border-image:url(:/img/asset/1.png);"
            "}"
            "QPushButton:pressed{"
            "border-image:url(:/img/asset/1.png);"
            "}");
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
