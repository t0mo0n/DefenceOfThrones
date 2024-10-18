#include "SettingsMenu.h"

SettingsMenu::SettingsMenu(QWidget *parent)
    : QDialog{parent}
{
    this->setFixedSize(600,400);
    this->setWindowTitle("Defense of Thrones");
    //TODO:setIcon

    QFont font("Arial",24);
    int labelX=50;
    int barX=300;
    int barW=200;
    int barH=30;

    //set volume
    volumeLabel =new QLabel("Volume:50",this);
    volumeLabel->setFont(font);
    volumeLabel->move(labelX,100);
    volumeLabel->setFixedSize(150,60);
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
    bgmChangedLabel->setFont(font);
    bgmChangedLabel->move(labelX,300);
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

    //init layout
    //QVBoxLayout *layout =new QVBoxLayout(this);
    // layout->addWidget(volumeLabel);
    // layout->addWidget(volumeSlider);
    // layout->addWidget(hardModeLabel);
    // layout->addWidget(hardModeComboBox);
    // layout->addWidget(bgmChangedLabel);
    // layout->addWidget(bgmChangedComboBox);
    // layout->setSpacing(20);
    // layout->setContentsMargins(100,50,100,50);
    // setLayout(layout);
}

void SettingsMenu::paintEvent(QPaintEvent *event){
    QPainter painter(this);

    //QPixmap pix()
    QPixmap pixMainMenuBackground(":/img/asset/otherMenu.jpg");
    painter.drawPixmap(0,0,this->width(),this->height(),pixMainMenuBackground);
}

SettingsMenu::~SettingsMenu(){
}
