#ifndef MYPUSHBUTTON_H
#define MYPUSHBUTTON_H

#include <QPushButton>

class MyPushButton : public QPushButton
{
    Q_OBJECT
public:
    MyPushButton(QString normalImg, QString pressedImg="", QWidget* parent=nullptr);
    void animationPress();
    QString normalImgPath_;
    QString pressedImgPath_;
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

private:
    void iconLoad(QString path);
    void animationJump();
    void animationFall();

signals:

};

#endif // MYPUSHBUTTON_H
