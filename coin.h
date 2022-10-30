#ifndef COIN_H
#define COIN_H

#include <QPushButton>
#include <QTimer>
#include <QSoundEffect>

class Coin : public QPushButton
{
    Q_OBJECT
public:
    QVector<Coin*> connections;
    Coin(QString iconPath, QWidget *parent);
    void iconLoad(QString path);
    void setProperty(int posX, int posY, bool isGlod);
    void setConnection(Coin *coin);
    bool isGold();
    void pressDisable();
    void pressEnable();

    int posX, posY;

private:
    bool isGold_;
    QTimer *flipOverTimer_;
    QTimer *flipUpTimer_;
    int flipOverAnimationImagePathIndex_=1;
    int flipUpAnimationImagePathIndex_=8;
    bool isAnimating_ = false;
    bool pressEnabled_ = true;

    void flip();
    void flipSurrondings();
    void flipEvent();
    void mousePressEvent(QMouseEvent *e);

signals:
    void flipped();
    void pressing();
    void animationOver();
};

#endif // COIN_H
