#ifndef ABSTRACTSCENE_H
#define ABSTRACTSCENE_H

#include <QMainWindow>
#include <QMenu>
#include <QAction>
#include <QSoundEffect>

#include <mypushbutton.h>

class AbstractScene : public QMainWindow
{
    Q_OBJECT
public:
    explicit AbstractScene(QWidget *parent = nullptr);
    virtual void paintEvent(QPaintEvent *ev);
    void paint(QString bgImgDir, double headerScaling=0.5, bool setHeaderMid=false);
    void setBackButton();

    QMenuBar *menuBar_=nullptr;
    QMenu *menuStart_=nullptr;
    QAction *actionStart_=nullptr;
    MyPushButton *backButton_=nullptr;
    QSoundEffect *backButtonSound_ = nullptr;

signals:
    void backSignal();
};

#endif // ABSTRACTSCENE_H
