#include "abstractscene.h"

#include <QMenuBar>
#include <QMenu>
#include <QPainter>
#include <QPixmap>
#include <QSoundEffect>

AbstractScene::AbstractScene(QWidget *parent)
    : QMainWindow{parent}
{
    //set the main size
    setFixedSize(320, 588);
    setWindowIcon(QIcon(":/Coin0001.png"));
    setWindowTitle("Can you flip the coin?");
    setBackButton();

    menuBar_ = menuBar();
    setMenuBar(menuBar_);
    menuStart_ = menuBar_->addMenu("Start");
    actionStart_ = menuStart_->addAction("Exit");
    connect(actionStart_, &QAction::triggered, this, &AbstractScene::close);

    backButtonSound_ = new QSoundEffect(this);
    backButtonSound_->setSource(QUrl::fromLocalFile(":/BackButtonSound.wav"));
}

void AbstractScene::paint(QString bgImgDir, double headerScaling, bool setHeaderMid) {
    QPainter painter(this);
    QPixmap pixmap(bgImgDir);
    painter.drawPixmap(0, 0, this->width(), this->height(), pixmap);
    pixmap.load(":/Title.png");
    pixmap = pixmap.scaled(headerScaling*pixmap.width(), headerScaling*pixmap.height());
    if (!setHeaderMid) painter.drawPixmap(10, 30, pixmap);
    else painter.drawPixmap(0.5*this->width()-0.5*pixmap.width(), 30, pixmap);
}

void AbstractScene::paintEvent(QPaintEvent *) {
    paint(":/PlayLevelSceneBg.png");
}

void AbstractScene::setBackButton() {
    backButton_ = new MyPushButton(":/BackButton.png", ":/BackButtonSelected.png", this);
    backButton_->move(this->width()-backButton_->width(), this->height()-backButton_->height());
    connect(backButton_, &MyPushButton::clicked, this, [=](){
        backButtonSound_->play();
        emit backSignal();
    });
}


