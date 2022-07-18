#ifndef SLIME_H
#define SLIME_H

#include <QGraphicsItem>
#include <QPixmap>
#include <QGraphicsPixmapItem>
#include <QObject>
#include <QTimer>

class Slime: public QObject,public QGraphicsPixmapItem
{
    Q_OBJECT
private:
    int hp;
    int fall_moment = 0;
    int walking_moment = 0;
    float fallspeed = 0;
    float walkingspeed = 0;
    bool shouldfall = false;
    bool gettinghit = false;
    bool fell = false;
    bool dashed = false;
    int dashcd;
    int invincibility_frame = 0;

    QTimer * movement;
    QTimer * invincibility;

public:
    Slime(QGraphicsItem *parent = 0);
    void getHit(int a = 1);

public slots:
    void move();
    void finishdash() {dashed = false;};
    void finishhit();
};

#endif // SLIME_H
