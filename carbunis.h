#ifndef CARBUNIS_H
#define CARBUNIS_H

#include <QGraphicsItem>
#include <QPixmap>
#include <QGraphicsPixmapItem>
#include <QObject>
#include <QTimer>

class Carbunis : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
private:
    bool dir_right = false;
    bool dir_left = false;
    bool dir_down = false;
    bool dir_up = false;
    bool isitfalling = false;
    int looking = 1;
    int hp;
    int degrau = 0;
    float currentspeed = 0.3;
    float fallingspeed;
    float jumpspeed = 20;
    float fallspeed = 0;
    bool jumping = false;
    bool wanttojump = false;
    bool attacking = false;
    bool specialattacking = false;
    bool wanttoattack = false;
    bool wanttospecialattack = false;
    bool gettinghit = false;
    int attack_moment = 0;
    int specialattack_moment = 0;
    int jump_moment = 0;
    int fall_moment = 0;
    int right_walking_moment = 0;
    int left_walking_moment = 0;
    int invincibility_frame = 0;

    QTimer * mFallTimer;
    QTimer * timerMove;
    QTimer * focus;
    QTimer * animation;

public:
    Carbunis(QGraphicsItem *parent = 0);
    int getHP() {return hp;};
    int getLook() {return looking;};
    void keyPressEvent(QKeyEvent * event);
    void keyReleaseEvent(QKeyEvent *event);
    void hpdecrease(int a = 1, int b = 1);
    void acceleration() {currentspeed+=0.3;};
    void deacceleration() {currentspeed=0.3;};
    float getspeed() {return currentspeed;};
    float getxposition() {return pos().x();};
    float getyposition() {return pos().y();};

public slots:
    void finishjump() {jumping = false; dir_up = false; dir_down = true; jump_moment = 19;};
    void finishattack() {attacking = false;};
    void finishspecialattack() {specialattacking = false;};
    void finishhit() {gettinghit = false;};
    void move();
    void refocus();
    void animate();
    void heal(int a);
};

#endif // CARBUNIS_H
