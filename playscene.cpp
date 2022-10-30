#include "playscene.h"
#include "abstractscene.h"
#include "coin.h"

#include <QLabel>
#include <QDebug>
#include <QPropertyAnimation>

PlayScene::PlayScene(int level, QVector<QVector<int>> data, QWidget *parent):
    AbstractScene{parent}, dataMatrix_{data}
{
    setBackButton();
    level_ = level;
    setLabel();
    setCoins();

    winBGM_ = new QSoundEffect(this);
    winBGM_->setSource(QUrl::fromLocalFile(":/LevelWinSound.wav"));

    coinFlipSound_ = new QSoundEffect(this);
    coinFlipSound_->setSource(QUrl::fromLocalFile(":/ConFlipSound.wav"));

    connect(this, &PlayScene::win, this, &PlayScene::winEvent);

//    QObjectList pList = this->children();
//    for (auto &ptr:pList) {
//        qDebug() << typeid(*ptr).name();
//    }
}

void PlayScene::setLabel() {
    QLabel *label = new QLabel(QString("Level: %1").arg(level_), this);
    QFont font;
    font.setFamily("LucidaMathStd");
    font.setPointSize(20);
    label->setFont(font);
    label->setGeometry(30, this->height()-50, 180, 50);

    winLabel_ = new QLabel(this);
    QPixmap pixmap = QPixmap(":/LevelCompletedDialogBg.png");
    winLabel_->setGeometry(0.5*this->width()-0.5*pixmap.width(), -pixmap.height(), pixmap.width(), pixmap.height());
    winLabel_->setPixmap(pixmap);
}

void PlayScene::setCoins() {
    for (int i=0;i<4;i++) {
        for (int j=0;j<4;j++) {
            QLabel *label = new QLabel("", this);
            label->setGeometry(0, 0, 50, 50);
            label->setPixmap(QPixmap(":/BoardNode.png"));
            int interval_X = 50, interval_Y=50, offset_X=57, offset_Y=200;
            label->move(offset_X+i*interval_X, offset_Y+j*interval_Y);

            Coin *coin = nullptr;
            if (dataMatrix_[i][j]==1) {
                coin = new Coin(":/Coin0001.png", label);
                coin->setProperty(i, j, true);
            }
            else {
                coin = new Coin(":/Coin0008.png", label);
                coin->setProperty(i, j, false);
            }
            coin->move(2, 4);
            coinPoiterMatrix_[i][j]=coin;
        }
    }

    setCoinConnections();
}

void PlayScene::setCoinConnections() {
    for (const auto &vec:coinPoiterMatrix_) {
        for (const auto &ptr:vec) {
            if (ptr->posX+1<4) ptr->setConnection(coinPoiterMatrix_[ptr->posX+1][ptr->posY]);
            if (ptr->posX-1>=0) ptr->setConnection(coinPoiterMatrix_[ptr->posX-1][ptr->posY]);
            if (ptr->posY+1<4) ptr->setConnection(coinPoiterMatrix_[ptr->posX][ptr->posY+1]);
            if (ptr->posY-1>=0) ptr->setConnection(coinPoiterMatrix_[ptr->posX][ptr->posY-1]);

            connect(ptr, &Coin::flipped, this, &PlayScene::checkStatus);
            connect(ptr, &Coin::pressing, this, &PlayScene::disableCoinsPressing);
            connect(ptr, &Coin::animationOver, this, &PlayScene::enableCoinsPressing);
            connect(ptr, &Coin::clicked, this, [=](){
                coinFlipSound_->play();
            });
        }
    }
}

void PlayScene::checkStatus() {
    for (const auto &vec:coinPoiterMatrix_) {
        for (const auto &ptr:vec) {
            if (!ptr->isGold()) return;
        }
    }

    for (const auto &vec:coinPoiterMatrix_) {
        for (const auto &ptr:vec) {
            ptr->pressDisable();
        }
    }

    emit win();
}

void PlayScene::winEvent() {
    QPropertyAnimation *animation = new QPropertyAnimation(winLabel_, "geometry");
    animation->setDuration(1000);
    animation->setStartValue(QRect(winLabel_->x(), winLabel_->y(), winLabel_->width(), winLabel_->height()));
    animation->setEndValue(QRect(winLabel_->x(), winLabel_->y()+114, winLabel_->width(), winLabel_->height()));
    animation->setEasingCurve(QEasingCurve::OutBounce);
    animation->start();

    winBGM_->play();
}

void PlayScene::disableCoinsPressing() {
    for (const auto &vec:coinPoiterMatrix_) {
        for (const auto &ptr:vec) {
            ptr->pressDisable();
        }
    }
}

void PlayScene::enableCoinsPressing() {
    for (const auto &vec:coinPoiterMatrix_) {
        for (const auto &ptr:vec) {
            ptr->pressEnable();
        }
    }
}

