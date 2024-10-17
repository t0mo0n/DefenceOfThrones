#include "SettingsMenu.h"

SettingsMenu::SettingsMenu(QWidget *parent)
    : QWidget{parent}
{
    //set volume
    QVBoxLayout *layout =new QVBoxLayout(this);

    volumeLabel =new QLabel("Volume:50",this);
    layout->addWidget(volumeLabel);

    volumeSlider=new QSlider(Qt::Horizontal,this);
    volumeSlider->setRange(0,100);
    volumeSlider->setValue(50);
    layout->addWidget(volumeSlider);

    connect(volumeSlider,&QSlider::valueChanged,this,[=](int value){
        volumeLabel->setText(QString("Volume:%1").arg(value));
        emit volumeChanged(value/100.0);
    });

    //set hard mode
    hardModeComboBox=new QComboBox(this);
    hardModeComboBox->addItem("Easy");
    hardModeComboBox->addItem("Hard");

    hardModeLabel =new QLabel("Mode:",this);
    layout->addWidget(hardModeLabel);
    layout->addWidget(hardModeComboBox);

    connect(hardModeComboBox,&QComboBox::currentTextChanged,this,
            [=](QString text){
        if(text=="Easy"){
            emit hardModeChanged(false);
        }else{
            emit hardModeChanged(true);
        }
    });

    //set bgm
    bgmChangedComboBox=new QComboBox(this);
    bgmChangedComboBox->addItem("Jenny of Oldstones");
    bgmChangedComboBox->addItem("Light of Nibel");
    bgmChangedComboBox->addItem("Light of the Seven");
    bgmChangedComboBox->addItem("the Night King");
    bgmChangedComboBox->addItem("the Rains of Castamere");

    bgmChangedLabel =new QLabel("BGM:");
    layout->addWidget(bgmChangedComboBox);
    layout->addWidget(bgmChangedLabel);

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

    setLayout(layout);
}

SettingsMenu::~SettingsMenu(){
}
