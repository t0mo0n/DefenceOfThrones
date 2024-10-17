QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Archer.cpp \
    Dragon.cpp \
    JohnSnow.cpp \
    Projectile.cpp \
    StoneThrower.cpp \
    TowerFrame.cpp \
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
    main.cpp \
    mainwindow.cpp \
     Deadalive.cpp \


HEADERS += \
    Archer.h \
    Dragon.h \
    GameController.h \
    JohnSnow.h \
    Projectile.h \
    StoneThrower.h \
    TowerFrame.h \
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

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    asset.qrc
