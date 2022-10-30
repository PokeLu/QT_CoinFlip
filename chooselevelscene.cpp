#include "chooselevelscene.h"
#include <QTimer>
#include <QLabel>
#include <QSoundEffect>
#include <QDebug>

#include <abstractscene.h>
#include <mypushbutton.h>
#include <dataconfig.h>

ChooseLevelScene::ChooseLevelScene(QWidget *parent)
    : AbstractScene{parent}
{
    setBackButton();
    dataConfig_ = new dataConfig(this);
    tapButtonSound_ = new QSoundEffect(this);
    tapButtonSound_->setSource(QUrl::fromLocalFile(":/TapButtonSound.wav"));

    int interval_x=70, interval_y=70, offset_x=25, offset_y=130;
    for(int i=0;i<20;i++) {
        MyPushButton *levelButton = new MyPushButton(":/LevelIcon.png", "", this);
        levelButton->move(offset_x+interval_x*(i%4), offset_y+interval_y*(i/4));
        connect(levelButton, &MyPushButton::clicked, this, [=](){
            tapButtonSound_->play();

            playScene = new PlayScene(i+1, dataConfig_->mData[i+1]);
            playScene->setGeometry(this->geometry());
            playScene->show();
            hide();

            connect(playScene, &PlayScene::exit, this, &ChooseLevelScene::close);
            connect(playScene, &PlayScene::backSignal, this, [=](){
                setGeometry(playScene->geometry());
                QTimer::singleShot(200, this, [=](){
                    show();
                    delete playScene;
                    playScene = nullptr;
                });
            });
        });

        QLabel *label = new QLabel(QString::number(i+1), this);
        label->setFixedSize(levelButton->size());
        label->setAlignment(Qt::AlignCenter);
        label->move(offset_x+interval_x*(i%4)-1, offset_y+interval_y*(i/4)-2);
        label->setAttribute(Qt::WA_TransparentForMouseEvents);
    }
}

void ChooseLevelScene::paintEvent(QPaintEvent *) {
    paint(":/OtherSceneBg.png", 1, true);
}

