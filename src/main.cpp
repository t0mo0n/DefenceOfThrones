#include "GameController.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    GameController w;
    w.show();
    return a.exec();
}
