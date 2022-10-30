#include "coin.h"

#include <QPushButton>
#include <QMessageBox>
#include <QDebug>
#include <QSoundEffect>

Coin::Coin(QString iconPath, QWidget *parent)
    : QPushButton{parent}
{
    iconLoad(iconPath);

    flipOverTimer_ = new QTimer(this);
    flipUpTimer_ = new QTimer(this);
    connect(this, &Coin::clicked, this, &Coin::flipEvent);
    connect(flipOverTimer_, &QTimer::timeout, this, [=](){
        QString path = QString(":/Coin%1.png").arg(flipOverAnimationImagePathIndex_++, 4, 10, QChar('0'));
        iconLoad(path);
        if(flipOverAnimationImagePathIndex_>flipUpAnimationImagePathIndex_) {
            flipOverAnimationImagePathIndex_=1;
            flipOverTimer_->stop();
            isAnimating_ = false;
        }
    });
    connect(flipUpTimer_, &QTimer::timeout, this, [=](){
        QString path = QString(":/Coin%1.png").arg(flipUpAnimationImagePathIndex_--, 4, 10, QChar('0'));
        iconLoad(path);
        if(flipOverAnimationImagePathIndex_>flipUpAnimationImagePathIndex_) {
            flipUpAnimationImagePathIndex_=8;
            flipUpTimer_->stop();
            isAnimating_ = false;
        }
    });
}

void Coin::iconLoad(QString path) {
    QPixmap pixmap;
    bool ret = pixmap.load(path);
    if (!ret) {
        QMessageBox::warning(this, "Error", QString("No such file directory for the image: %1").arg(path));
        return;
    }
    setFixedSize(pixmap.width(), pixmap.height());

    //set irregular-sized icon to the push button
    setStyleSheet("QPushButton{border:0px}");

    setIcon(pixmap);
    setIconSize(pixmap.size());
}

void Coin::setProperty(int x, int y, bool isGlod) {
    posX=x, posY=y, isGold_=isGlod;
}

void Coin::flip() {
    QTimer* timerPointer = isGold_ ? flipOverTimer_:flipUpTimer_;
    isGold_ = !isGold_;
    emit flipped();
    timerPointer->start(30);
    isAnimating_ = true;
}

void Coin::mousePressEvent(QMouseEvent *e) {
    if (isAnimating_ | !pressEnabled_) return;
    emit pressing();
    return QPushButton::mousePressEvent(e);
}

void Coin::setConnection(Coin *coin) {
    connections.emplaceBack(coin);
}

void Coin::flipSurrondings() {
    QTimer::singleShot(300, this, [=](){
        for (const auto &neighbor:connections) {
            neighbor->flip();
        }
    });
}

void Coin::flipEvent() {    
    flip();
    flipSurrondings();
    QTimer::singleShot(300, this, [=](){
        emit animationOver();
    });
}

bool Coin::isGold() {
    return isGold_;
}

void Coin::pressDisable() {
    pressEnabled_=false;
}

void Coin::pressEnable() {
     pressEnabled_=true;
}
