#include "mainscene.h"

#include <QPainter>
#include <QPixmap>
#include <QTimer>
#include <QSoundEffect> //should be added to .pro file

#include <mypushbutton.h>

MainScene::MainScene(QWidget *parent)
    : AbstractScene(parent)
{
    startButton_ = new MyPushButton(":/MenuSceneStartButton.png", "", this);
    startButton_->move(0.5*this->width()-0.5*startButton_->width(), 0.7*this->height());
    connect(startButton_, &QPushButton::clicked, this, &MainScene::startEvent);

    startButtonSound = new QSoundEffect(this);
    startButtonSound->setSource(QUrl::fromLocalFile(":/TapButtonSound.wav"));

    chooseLevelScene_ = new ChooseLevelScene;
    connect(chooseLevelScene_, &ChooseLevelScene::backSignal, this, &MainScene::backEvent);
//    connect(chooseLevelScene_, &ChooseLevelScene::exit, this, &MainScene::close);
}

void MainScene::startEvent(){
    startButton_->animationPress();
    startButtonSound->play();

    QTimer::singleShot(100, this, [=](){
        chooseLevelScene_->setGeometry(this->geometry());
        chooseLevelScene_->show();
        hide();
    });
}

void MainScene::backEvent(){
    QTimer::singleShot(100, this, [=](){
        setGeometry(chooseLevelScene_->geometry());
        show();
        chooseLevelScene_->hide();
    });
}

