#ifndef SETTINGSMENU_H
#define SETTINGSMENU_H

#include <QWidget>
#include <QSlider>
#include <QLabel>
#include <QVBoxLayout>
#include <QComboBox>

class SettingsMenu : public QWidget
{
    Q_OBJECT
public:
    explicit SettingsMenu(QWidget *parent = nullptr);
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
