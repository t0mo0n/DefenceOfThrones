#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include <QWidget>

class GameController : public QWidget
{
    Q_OBJECT

public:
    GameController(QWidget *parent = nullptr);
    ~GameController();
};
#endif // GAMECONTROLLER_H
