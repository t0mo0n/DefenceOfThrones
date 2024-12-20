QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Archer.cpp \
    Button.cpp \
    Dragon.cpp \
    GameScene.cpp \
    DragonBall.cpp \
    DragonFlame.cpp \
    FireArrow.cpp \
    JohnSnow.cpp \
    MainMenu.cpp \
    Map.cpp \
    PathCell.cpp \
    Projectile.cpp \
    Stone.cpp \
    StoneThrower.cpp \
    TowerCell.cpp \
    TowerFrame.cpp \
    TowerSelectMenu.cpp \
    Wolf.cpp \
    main.cpp \
    GameController.cpp \
    Enemy.cpp \
    GreyjoySoldier.cpp \
    KingSlayer.cpp \
    LannisterSoldier.cpp \
    Melisandre.cpp \
    Mountain.cpp \
    NightKing.cpp \
    Obstacle.cpp \
    Player.cpp \
    Vesalion.cpp \
    Wilder.cpp \
    Deadalive.cpp \


HEADERS += \
    Archer.h \
    Button.h \
    Dragon.h \
    DragonBall.h \
    DragonFlame.h \
    FireArrow.h \
    GameController.h \
    GameScene.h \
    JohnSnow.h \
    MainMenu.h \
    Map.h \
    PathCell.h \
    Projectile.h \
    Stone.h \
    StoneThrower.h \
    TowerCell.h \
    TowerFrame.h \
    TowerSelectMenu.h \
    Wolf.h \
    Enemy.h \
    GreyjoySoldier.h \
    KingSlayer.h \
    LannisterSoldier.h \
    Melisandre.h \
    Mountain.h \
    NightKing.h \
    Obstacle.h \
    Player.h \
    Vesalion.h \
    Wilder.h \
    Deadalive.h \

FORMS += \
    mainmenu.ui\

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    asset.qrc
