#ifndef SKELETON_H
#define SKELETON_H

#include <QGraphicsItem>
#include <QPixmap>
#include <QGraphicsPixmapItem>
#include <QObject>
#include <QTimer>

class Skeleton : public QObject,public QGraphicsPixmapItem
{
    Q_OBJECT
private:
    int hp;
    int looking = 1;
    int fall_moment = 0;
    int walking_moment = 0;
    float fallspeed = 0;
    float walkingspeed = 0;
    bool shouldfall = false;
    bool gettinghit = false;
    bool fell = false;
    int invincibility_frame = 0;

    QTimer * movement;
    QTimer * attacktimer;
    QTimer * falling;

public:
    Skeleton(QGraphicsItem *parent = 0);
    void getHit(int a = 1);
    void getHit(int a, int b);
    int getLook() {return looking;};

public slots:
    void Attack();
    void move();
    void finishhit() {gettinghit = false; setPixmap(QPixmap(":/images/skeletonleft"));};
    void fall();
    void lookagain();
};

#endif // SKELETON_H
