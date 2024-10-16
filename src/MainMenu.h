#ifndef MAINMENU_H
#define MAINMENU_H


#include <QWidget>
#include <QPushButton>
#include <QPaintEvent>
#define WIDTH 1200
#define HIGTH 800


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

private:
    Ui::MainMenu *ui;
    QList<QPushButton*> buttons={new QPushButton("START",this),
                                new QPushButton("SELECT LEVEL",this),
                                new QPushButton("SETTING",this),
                                new QPushButton("EXIT",this)};
    //TODO:
    QStringList buttonsPix={":/img/asset/1.png",
                               ":/img/asset/1.png",
                               ":/img/asset/1.png",
                                ":/img/asset/1.png",};
    //0:startButton 1:levelSelectButton 2:settingButton 4:exitButton;
public slots:

};

#endif // MAINMENU_H
