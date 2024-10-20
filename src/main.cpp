#include "GameController.h"
#include "Map.h"

#include <QApplication>

int main(int argc, char *argv[])
{

    QApplication a(argc,argv);
    Map map1;
    map1.load(1,false);
    GameController w;
    return a.exec();
}
