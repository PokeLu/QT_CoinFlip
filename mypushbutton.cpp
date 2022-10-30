#include "mypushbutton.h"

#include <QPixmap>
#include <QMessageBox>
#include <QPropertyAnimation>

MyPushButton::MyPushButton(QString normalImg, QString pressedImg, QWidget* parent):
    QPushButton(parent)
{
    normalImgPath_ = normalImg;
    pressedImgPath_ = pressedImg;
    iconLoad(normalImg);
}

void MyPushButton::iconLoad(QString path) {
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

void MyPushButton::animationJump() {
    QPropertyAnimation *animation =new QPropertyAnimation(this, "geometry", this);
    animation->setDuration(200);
    animation->setStartValue(QRect(this->x(), this->y(), this->width(), this->height()));
    animation->setEndValue(QRect(this->x(), this->y()+10, this->width(), this->height()));
    animation->setEasingCurve(QEasingCurve::OutBounce);
    animation->start();
}

void MyPushButton::animationFall() {
    QPropertyAnimation *animation =new QPropertyAnimation(this, "geometry", this);
    animation->setDuration(200);
    animation->setStartValue(QRect(this->x(), this->y()+10, this->width(), this->height()));
    animation->setEndValue(QRect(this->x(), this->y(), this->width(), this->height()));
    animation->setEasingCurve(QEasingCurve::OutBounce);
    animation->start();
}

void MyPushButton::animationPress() {
    animationJump();
    animationFall();
}

void MyPushButton::mousePressEvent(QMouseEvent *event) {
    if (pressedImgPath_.length()!=0) iconLoad(pressedImgPath_);
    return QPushButton::mousePressEvent(event);
}

void MyPushButton::mouseReleaseEvent(QMouseEvent *event) {
    if (pressedImgPath_.length()!=0) iconLoad(normalImgPath_);
    return QPushButton::mouseReleaseEvent(event);
}
