#ifndef SETTINGSMENU_H
#define SETTINGSMENU_H

#include <QDialog>
#include <QSlider>
#include <QLabel>
#include <QVBoxLayout>
#include <QComboBox>
#include <QPaintEvent>
#include <QPainter>

class SettingsMenu : public QDialog
{
    Q_OBJECT
public:
    explicit SettingsMenu(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *event);
    ~SettingsMenu();
signals:
    void volumeChanged(float volumn);
    void hardModeChanged(bool hardmode);
    void gameBgmChanged(int index);
private:
    QSlider *volumeSlider;
    QComboBox *hardModeComboBox;
    QComboBox *bgmChangedComboBox;

    QLabel *volumeLabel;
    QLabel *hardModeLabel;
    QLabel *bgmChangedLabel;
};

#endif // SETTINGSMENU_H
