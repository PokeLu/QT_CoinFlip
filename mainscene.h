#ifndef MAINSCENE_H
#define MAINSCENE_H

#include <QMainWindow>
#include <QSoundEffect>

#include <abstractscene.h>
#include <mypushbutton.h>
#include <chooselevelscene.h>


class MainScene : public AbstractScene
{
    Q_OBJECT

public:
    MainScene(QWidget *parent = nullptr);

    void startEvent();
    void backEvent();

    MyPushButton *startButton_=nullptr;
    ChooseLevelScene *chooseLevelScene_=nullptr;

private:
    QSoundEffect *startButtonSound = nullptr;
};
#endif // MAINSCENE_H
