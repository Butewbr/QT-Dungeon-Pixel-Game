#ifndef DEMON_H
#define DEMON_H

#include <QGraphicsItem>
#include <QPixmap>
#include <QGraphicsPixmapItem>
#include <QObject>
#include <QTimer>

class Demon : public QObject,public QGraphicsPixmapItem
{
    Q_OBJECT
private:
    float hp;
    int spawn_moment = 0;
    int look;
    int flying_moment = 0;
    int fall_moment = 0;
    bool highattack = true;
    float fallspeed;
    int floatingloop = 0;
    bool displacement = false;
    bool floating = false;
    bool upanimation = false;
    bool downanimation = false;
    bool flying = false;
    bool justfloated = false;
    bool finishedfalling = false;
    bool can_be_hit = true;
    bool gettinghit = false;
    bool justflew = false;
    float flying_speed = 20;
    int floating_moment = 0;

    QTimer * attackcd;
    QTimer * blinkcd;
    QTimer * movementcd;
    QTimer * flycd;
    QTimer * spawncd;
    QTimer * meteorcd;

public:
    Demon(QGraphicsItem *parent = 0);
    int getLook() {return look;};
    void getHit(float a = 1);

public slots:
    void finishhit() {gettinghit = false;};
    void move();
    void spawn();
    void attack();
    void tp();
    void meteorattack();
    void fly();
    void canflyagain() {justflew = false;};
};

#endif // DEMON_H
