#ifndef MAINMENU_H
#define MAINMENU_H


#include <QWidget>
#include <QPushButton>
#include <QPaintEvent>
#include <QFontDatabase>
#include <QTimer>
#include <QPainter>
#include <QVBoxLayout>
#include <QLabel>
#include <QSlider>
#include <QComboBox>
#include <QDebug>

#define WIDTH 1200
#define HIGTH 800

#define BTNW 165
#define BTNH 93

#define OriginSize 14

namespace Ui {
class MainMenu;
}

class MainMenu : public QWidget
{
    Q_OBJECT
public:
    explicit MainMenu(QWidget *parent = nullptr);
    ~MainMenu();
    void paintEvent(QPaintEvent *event);

signals:
    void startNewGame();
    void openLevelMenu();
    void openSettingMenu();
    void exitGame();

    void volumeChanged(float volumn);
    void hardModeChanged(bool hardmode);
    void gameBgmChanged(int index);

    void selectLevel(int level);

private:
    Ui::MainMenu *ui;
    QList<QPushButton*> buttons={new QPushButton("START",this),
                                new QPushButton("SELECT LEVEL",this),
                                new QPushButton("SETTING",this),
                                new QPushButton("EXIT",this)};
    QStringList buttonsPix={":/img/asset/button3.png",
                               ":/img/asset/button3.png",
                               ":/img/asset/button3.png",
                                ":/img/asset/button3.png",};
    //0:startButton 1:levelSelectButton 2:settingButton 4:exitButton;
    QPixmap pixMainMenuBackground;
    QPixmap pixShield;

    //Timer
    int yOffset=0;

    //Layout
    QVBoxLayout *mainMenuLayout;
    QVBoxLayout *settingLayout;
    QVBoxLayout *levelSelectMenu;

    //SettingMenu
    QSlider *volumeSlider;
    QComboBox *hardModeComboBox;
    QComboBox *bgmChangedComboBox;
    QPushButton *backMainMenu1;

    QLabel *volumeLabel;
    QLabel *hardModeLabel;
    QLabel *bgmChangedLabel;

    //LevelSelect Menu
    QList<QPushButton*> levelButtons={new QPushButton{"LEVEL 1",this},
                                         new QPushButton{"LEVEL 2",this},
                                         new QPushButton{"LEVEL 3",this}};
    QPushButton *backMainMenu2;
    int maxLevel=0;


public slots:
    void updateOffset(){
        yOffset-=1;
        update();
    }

    void showSettings(){
        for (int var = 0; var < 4; ++var) {
            buttons[var]->hide();
        }
        volumeLabel->show();
        hardModeLabel->show();
        bgmChangedLabel->show();
        volumeSlider->show();
        hardModeComboBox->show();
        bgmChangedComboBox->show();
        backMainMenu1->show();
    }

    void hideSettings(){
        for (int var = 0; var < 4; ++var) {
            buttons[var]->show();
        }
        volumeLabel->hide();
        hardModeLabel->hide();
        bgmChangedLabel->hide();
        volumeSlider->hide();
        hardModeComboBox->hide();
        bgmChangedComboBox->hide();
        backMainMenu1->hide();
    }

    void showLevelSelect(){
        for (int var = 0; var < 4; ++var) {
            buttons[var]->hide();
        }
        for (int var = 0; var < maxLevel; ++var) {
            levelButtons[var]->show();
        }
        backMainMenu2->show();
    }

    void hideLevelSelect(){
        for (int var = 0; var < 4; ++var) {
            buttons[var]->show();
        }
        for (int var = 0; var < maxLevel; ++var) {
            levelButtons[var]->hide();
        }
        backMainMenu2->hide();
    }

    void recieveMaxLevel(int maxLevel_){
        maxLevel=maxLevel_;
    }

};

#endif // MAINMENU_H
