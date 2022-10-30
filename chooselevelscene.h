#ifndef CHOOSELEVELSCENE_H
#define CHOOSELEVELSCENE_H

#include <QMainWindow>
#include <QSoundEffect>

#include <abstractscene.h>
#include <mypushbutton.h>
#include <playscene.h>
#include <dataconfig.h>

class ChooseLevelScene : public AbstractScene
{
    Q_OBJECT
public:
    explicit ChooseLevelScene(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *ev);
    void backEvent();

    PlayScene *playScene=nullptr;
    dataConfig *dataConfig_=nullptr;
    QSoundEffect *tapButtonSound_=nullptr;

signals:

};

#endif // CHOOSELEVELSCENE_H
