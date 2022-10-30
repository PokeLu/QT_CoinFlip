#ifndef PLAYSCENE_H
#define PLAYSCENE_H

#include <abstractscene.h>
#include <dataconfig.h>
#include <coin.h>

#include <QVector>
#include <QLabel>
#include <QSoundEffect>

class PlayScene : public AbstractScene
{
    Q_OBJECT
public:
    explicit PlayScene(int level, QVector<QVector<int>> data, QWidget *parent = nullptr);
    void setLabel();
    void setCoins();
    void setCoinConnections();
    void checkStatus();
    void winEvent();
    void disableCoinsPressing();
    void enableCoinsPressing();
    void tempDisableCoinsPressing();

    int level_;
    const QVector<QVector<int>> dataMatrix_=QVector<QVector<int>>(4, QVector<int>(4));
    QVector<QVector<Coin*>> coinPoiterMatrix_ = QVector<QVector<Coin*>>(4, QVector<Coin*>(4));
    QLabel *winLabel_ = nullptr;
    QSoundEffect *winBGM_=nullptr;
    QSoundEffect *coinFlipSound_=nullptr;

signals:
    void win();
};

#endif // PLAYSCENE_H
