#include "GameController.h"
#include "MainMenu.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    GameController w;
    MainMenu m;
    m.show();
    return a.exec();
}
