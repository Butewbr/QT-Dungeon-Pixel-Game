#include "carbunis.h"
#include "game.h"
#include "specialattack.h"
#include "attack.h"
#include <QGraphicsScene>
#include <QObject>
#include <QGraphicsItem>
#include <QDebug>
#include <QKeyEvent>
#include <QTimer>

extern Game * game;

Carbunis::Carbunis(QGraphicsItem *parent): QGraphicsPixmapItem(parent)
{
    hp = 35;
    setPixmap(QPixmap(":/images/carbunisdir.png"));

    timerMove = new QTimer();
    connect(timerMove, SIGNAL(timeout()), this, SLOT(move()));
    timerMove->start(17);

    focus = new QTimer();
    connect(focus, SIGNAL(timeout()), this, SLOT(refocus()));
    focus->start(16);

    /*mFallTimer = new QTimer();
    connect(mFallTimer, SIGNAL(timeout()), this, SLOT(fall()));
    mFallTimer->start(17);*/

    animation = new QTimer();
    connect(animation, SIGNAL(timeout()), this, SLOT(animate()));
    animation->start(17);
}

void Carbunis::refocus()
{
    setFocus();
}

void Carbunis::animate()
{
    invincibility_frame++;
    if(invincibility_frame == 40)
    {
        finishhit();
        invincibility_frame = 0;
    }
    if(dir_right)
    {
        right_walking_moment += 1;
        if(right_walking_moment == 1)
        {
            setPixmap(QPixmap(":/images/cbright1.png"));
        }
        if(right_walking_moment == 11)
        {
            setPixmap(QPixmap(":/images/cbright2.png"));
        }
        if(right_walking_moment == 21)
        {
            setPixmap(QPixmap(":/images/carbunisdir.png"));
        }
        if(right_walking_moment == 31)
        {
            right_walking_moment = 0;
        }
    }
    if(dir_left)
    {
        left_walking_moment += 1;
        if(left_walking_moment == 1)
        {
            setPixmap(QPixmap(":/images/cbleft1.png"));
        }
        if(left_walking_moment == 11)
        {
            setPixmap(QPixmap(":/images/cbleft2.png"));
        }
        if(left_walking_moment == 21)
        {
            setPixmap(QPixmap(":/images/carbunisesq.png"));
        }
        if(left_walking_moment == 31)
        {
            left_walking_moment = 0;
        }
    }
    if(wanttoattack)
    {
        if(attack_moment == 1 and looking == 1)
        {
            setPixmap(QPixmap(":/images/carbunisslash1"));
        }
        else if(attack_moment == 1 and looking == 0)
        {
            setPixmap(QPixmap(":/images/carbunisslash1left"));
        }
        if(attack_moment == 3 and looking == 1)
        {
            setPixmap(QPixmap(":/images/carbunisslash2"));
        }
        else if(attack_moment == 3 and looking == 0)
        {
            setPixmap(QPixmap(":/images/carbunisslash2left"));
        }
        else if(attack_moment == 5 and looking == 0)
        {
            setPixmap(QPixmap(":/images/carbunisesq"));
        }
        else if(attack_moment == 5 and looking == 1)
        {
            setPixmap(QPixmap(":/images/carbunisdir"));
        }
    }
    if(wanttospecialattack)
    {
        if(looking == 1)
        {
            if(specialattack_moment == 1)
            {
                setPixmap(QPixmap(":/images/cbspright1"));
            }
            if(specialattack_moment == 25)
            {
                setPixmap(QPixmap(":/images/cbspright2"));
            }
            if(specialattack_moment == 50)
            {
                setPixmap(QPixmap(":/images/cbspright3"));
            }
            if(specialattack_moment == 75)
            {
                setPixmap(QPixmap(":/images/cbspright4"));
            }
            if(specialattack_moment == 95)
            {
                setPixmap(QPixmap(":/images/carbunisslash2"));
            }
            if(specialattack_moment == 100)
            {
                setPixmap(QPixmap(":/images/carbunisdir"));
            }

        }
        else if(looking == 0)
        {
            if(specialattack_moment == 1)
            {
                setPixmap(QPixmap(":/images/cbspleft1"));
            }
            if(specialattack_moment == 25)
            {
                setPixmap(QPixmap(":/images/cbspleft2"));
            }
            if(specialattack_moment == 50)
            {
                setPixmap(QPixmap(":/images/cbspleft3"));
            }
            if(specialattack_moment == 75)
            {
                setPixmap(QPixmap(":/images/cbspleft4"));
            }
            if(specialattack_moment == 95)
            {
                setPixmap(QPixmap(":/images/carbunisslash2left"));
            }
            if(specialattack_moment == 100)
            {
                setPixmap(QPixmap(":/images/carbunisesq"));
            }
        }
    }
}

void Carbunis::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Left)
    {
        if(left_walking_moment == 0)
            setPixmap(QPixmap(":/images/carbunisesq.png"));

        dir_left = true;
        looking = 0;
    }
    else if(event->key() == Qt::Key_Right)
    {
        if(right_walking_moment == 0)
            setPixmap(QPixmap(":/images/carbunisdir.png"));

        dir_right = true;
        looking = 1;
    }
    else if(event->key() == Qt::Key_Up)
    {
        dir_up = true;
        wanttojump = true;
    }
    if(event->key() == Qt::Key_Z)
    {
        wanttoattack = true;
    }
    if(event->key() == Qt::Key_X)
    {
        wanttospecialattack = true;
    }
}

void Carbunis::keyReleaseEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Left)
    {
        if (event->isAutoRepeat())
        {
            return;
        }
        dir_left = false;
        left_walking_moment = 0;
        looking = 0;

        setPixmap(QPixmap(":/images/carbunisesq.png"));

        this->deacceleration();
    }
    else if(event->key() == Qt::Key_Right)
    {
        if (event->isAutoRepeat())
        {
            return;
        }
        dir_right = false;
        right_walking_moment = 0;
        looking = 1;

        setPixmap(QPixmap(":/images/carbunisdir.png"));

        this->deacceleration();
    }
    else if(event->key() == Qt::Key_Up)
    {
        if (event->isAutoRepeat())
        {
            return;
        }
        wanttojump = false;
    }
    if(event->key() == Qt::Key_Z)
    {
        if (event->isAutoRepeat())
        {
            return;
        }
        wanttoattack = false;
    }
    if(event->key() == Qt::Key_X)
    {
        if (event->isAutoRepeat())
        {
            return;
        }
        wanttospecialattack = false;
    }
}

void Carbunis::move()
{
    /*qDebug() << getxposition();
    qDebug() << getyposition();*/

    if(dir_left)
    {
        if(pos().x() > 0)
        {
            //qDebug()<<(this->getspeed());
            setPos(x()-this->getspeed(),y());
            if(this->getspeed() < 10)
            {
                this->acceleration();
            }
        }
        if(game->floor == 2)
        {
            if(pos().x() > 1124 and degrau == 1)
            {
                setPos(x()-this->getspeed(), y()-16);
                degrau--;
            }
            else if(pos().x() > 1148 and degrau == 2)
            {
                setPos(x()-this->getspeed(), y()-16);
                degrau--;
            }
            else if(pos().x() > 1172 and degrau == 3)
            {
                setPos(x()-this->getspeed(), y()-16);
                degrau--;
            }
            else if(pos().x() > 1196 and degrau == 4)
            {
                setPos(x()-this->getspeed(), y()-16);
                degrau--;
            }
        }
    }
    if(dir_right)
    {
        //qDebug()<<(this->getspeed());
        setPos(x()+this->getspeed(),y());
        if(this->getspeed() < 10)
        {
            this->acceleration();
        }
        if(game->getFloor() == 1)
        {
            if(game->slimedied and pos().x() > 1196)
            {
                game->Game::ChangeFloor(game->getFloor());
            }
            else if (pos().x() > 1196 and !game->slimedied)
            {
                setPos(1196, y());
            }
        }
        if(game->getFloor() == 2)
        {
            if(pos().x() > 1124 and degrau == 0)
            {
                setPos(x()+this->getspeed(), y()+16);
                degrau++;
            }
            else if(pos().x() > 1148 and degrau == 1)
            {
                setPos(x()+this->getspeed(), y()+16);
                degrau++;
            }
            else if(pos().x() > 1172 and degrau == 2)
            {
                setPos(x()+this->getspeed(), y()+16);
                degrau++;
            }
            else if(pos().x() > 1196 and degrau == 3 and game->skeletondied)
            {
                //setPos(x()+this->getspeed(), y()+16);
                game->Game::ChangeFloor(game->getFloor());
            }
            else if(pos().x() > 1196 and degrau == 3 and !game->skeletondied)
            {
                setPos(1196, y());
            }
        }
        else if(game->floor == 4)
        {
            if(pos().x() > 1196 and game->demondied == false)
            {
                setPos(1196, y());
            }
            if(pos().x() > 1196 and game->demondied == true)
            {
                game->Game::ChangeFloor(game->getFloor());
            }
        }
        else if(pos().x() > 1196)
        {
            game->Game::ChangeFloor(game->getFloor());
        }
    }
    if(dir_up == true and jumping == false)
    {
        if(jump_moment == 19)
        {
            jumpspeed = 20;
            jump_moment = 0;
        }

        jump_moment += 1;

        if(wanttojump)
            setPos(x(), y()-jumpspeed);

        jumpspeed -= 1;


        if(jump_moment == 18)
        {
            //this->fall();
            jumping = true;
            dir_down = true;
            //QTimer::singleShot(jumpcd, this, SLOT(finishjump()));
        }
    }
    if(dir_down)
    {
        if(fall_moment == 24)
        {
            fallspeed = 0;
            fall_moment = 0;
        }

        fall_moment += 1;

        if(pos().y()+fallspeed > 354)
        {
            setPos(x(), 354);
        }
        else
        {
            setPos(x(), y()+fallspeed);
            fallspeed += 1;
        }
        if(fall_moment == 24)
        {
            finishjump();
            dir_down = false;
        }
    }
    if(wanttoattack)
    {
        if(attack_moment == 22)
        {
            attack_moment = 0;
            finishattack();
        }

        attack_moment++;

        if(!attacking and !specialattacking)
        {
            if(looking == 1)
            {
                Attack * attack = new Attack();
                attack->setPos(x()+154,y()+60);
                scene()->addItem(attack);
            }
            else if(looking == 0)
            {
                Attack * attack = new Attack();
                attack->setPos(x()-50,y()+60);
                scene()->addItem(attack);
            }
        }

        attacking = true;
    }
    if(wanttospecialattack)
    {
        if(specialattack_moment == 100)
        {
            specialattack_moment = 0;
            finishspecialattack();
        }

        specialattack_moment++;

        if(!specialattacking and specialattack_moment == 99)
        {
            if(looking == 1)
            {
                SpecialAttack * specialattack = new SpecialAttack();
                specialattack->setPos(x()+154,y()+60);
                scene()->addItem(specialattack);
            }
            else if(looking == 0)
            {
                SpecialAttack * specialattack = new SpecialAttack();
                specialattack->setPos(x()-277,y()+60);
                scene()->addItem(specialattack);
            }
        }
    }
}

void Carbunis::hpdecrease(int a, int b)
{
    if(!gettinghit)
    {
        if(looking == 1)
        {
            setPixmap(QPixmap(":/images/carbunisdirhit"));
        }
        else
        {
            setPixmap(QPixmap(":/images/carbunisesqhit"));
        }
        if(b == 1)
        {
            this->setPos(x()-60, y()-60);
            dir_down = true;
        }
        else
        {
            this->setPos(x()+60, y()-60);
            dir_down = true;
        }
        gettinghit = true;
        //QTimer::singleShot(invincibility, this, SLOT(finishhit()));

        hp -= a;

        game->health->att(hp);

        if(hp < 1)
        {
            delete this;
            game->endgame(0);
        }
    }
}

void Carbunis::heal(int a)
{
    if(looking == 0)
        setPixmap(QPixmap(":/images/carbunisesqheal"));
    else
        setPixmap(QPixmap(":/images/carbunisdirheal"));

    if(hp + a > 35)
    {
        hp = 35;
    }
    else
    {
        hp += a;
    }

    game->health->att(hp);
}
