#include "obiunam.h"
#include "game.h"
#include "slash3d.h"
#include <QGraphicsScene>
#include <QObject>
#include <QGraphicsItem>
#include <QDebug>
#include <QKeyEvent>
#include <QTimer>

extern Game * game;

Obiunam::Obiunam(QGraphicsItem *parent): QGraphicsPixmapItem(parent)
{
    hp = 35;
    setPixmap(QPixmap(":/images/obiunamdir.png"));

    timerMove = new QTimer();
    connect(timerMove, SIGNAL(timeout()), this, SLOT(move()));
    timerMove->start(17);

    focus = new QTimer();
    connect(focus, SIGNAL(timeout()), this, SLOT(refocus()));
    focus->start(16);

    animation = new QTimer();
    connect(animation, SIGNAL(timeout()), this, SLOT(animate()));
    animation->start(17);

    hitbox = new Hitbox();
    hitbox->setPos(x(), y());
    //scene()->addItem(hitbox);
}

void Obiunam::refocus()
{
    setFocus();
    if(!hitboxput)
    {
        scene()->addItem(hitbox);
        hitboxput = true;
    }
}

void Obiunam::animate()
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
            setPixmap(QPixmap(":/images/obright1.png"));
        }
        if(right_walking_moment == 11)
        {
            setPixmap(QPixmap(":/images/obright2.png"));
        }
        if(right_walking_moment == 21)
        {
            setPixmap(QPixmap(":/images/obiunamdir.png"));
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
            setPixmap(QPixmap(":/images/obleft1.png"));
        }
        if(left_walking_moment == 11)
        {
            setPixmap(QPixmap(":/images/obleft2.png"));
        }
        if(left_walking_moment == 21)
        {
            setPixmap(QPixmap(":/images/obiunamesq.png"));
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
            setPixmap(QPixmap(":/images/obslash1big"));
        }
        else if(attack_moment == 1 and looking == 0)
        {
            setPixmap(QPixmap(":/images/obslash1bigleft"));
        }
        if(attack_moment == 3 and looking == 1)
        {
            setPixmap(QPixmap(":/images/obslash2big"));
        }
        else if(attack_moment == 3 and looking == 0)
        {
            setPixmap(QPixmap(":/images/obslash2bigleft"));
        }
        else if(attack_moment == 5 and looking == 0)
        {
            setPixmap(QPixmap(":/images/obiunamesq"));
        }
        else if(attack_moment == 5 and looking == 1)
        {
            setPixmap(QPixmap(":/images/obiunamdir"));
        }
    }
    if(wanttospecialattack)
    {
        if(looking == 1)
        {
            setPixmap(QPixmap(":/images/obiunamblockingdir"));
        }
        else if(looking == 0)
        {
            setPixmap(QPixmap(":/images/obiunamblockingesq"));
        }
    }
}

void Obiunam::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Left and !blocking)
    {
        if(left_walking_moment == 0)
            setPixmap(QPixmap(":/images/obiunamesq.png"));


        if(looking == 1)
        {
            setPos(x()-119, y());
            hitbox->posatt(x()-119,y());
        }

        dir_left = true;
        looking = 0;
    }
    else if(event->key() == Qt::Key_Right and !blocking)
    {
        if(!event->isAutoRepeat())
        {
            hitbox->posatt(x(),y());
        }
        if(right_walking_moment == 0)
            setPixmap(QPixmap(":/images/obiunamdir.png"));

        if(looking == 0)
        {
            setPos(x()+119, y());
            hitbox->posatt(x()+119,y());
        }

        dir_right = true;
        looking = 1;
    }
    else if(event->key() == Qt::Key_Up and !blocking)
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

void Obiunam::keyReleaseEvent(QKeyEvent *event)
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
        //hitbox->posatt(x()+119,y());

        setPixmap(QPixmap(":/images/obiunamesq.png"));

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

        setPixmap(QPixmap(":/images/obiunamdir.png"));

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
        blocking = false;
        if(looking == 0)
            setPixmap(QPixmap(":/images/obiunamesq"));
        else
            setPixmap(QPixmap(":/images/obiunamdir"));
    }
}

void Obiunam::move()
{
    if(dir_left and !blocking)
    {
        if(pos().x() > 0)
        {
            //qDebug()<<(this->getspeed());
            setPos(x()-this->getspeed(),y());
            hitbox->posatt(x()-this->getspeed()+125, y());
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
                hitbox->posatt(x()-this->getspeed()+125, y()-16);
                degrau--;
            }
            else if(pos().x() > 1148 and degrau == 2)
            {
                setPos(x()-this->getspeed(), y()-16);
                hitbox->posatt(x()-this->getspeed()+125, y()-16);
                degrau--;
            }
            else if(pos().x() > 1172 and degrau == 3)
            {
                setPos(x()-this->getspeed(), y()-16);
                hitbox->posatt(x()-this->getspeed()+125, y()-16);
                degrau--;
            }
            else if(pos().x() > 1196 and degrau == 4)
            {
                setPos(x()-this->getspeed(), y()-16);
                hitbox->posatt(x()-this->getspeed()+125, y()-16);
                degrau--;
            }
        }
    }
    if(dir_right and !blocking)
    {
        //qDebug()<<(this->getspeed());
        setPos(x()+this->getspeed(),y());
        hitbox->posatt(x()+this->getspeed(), y());

        if(this->getspeed() < 10)
        {
            this->acceleration();
        }
        if(game->getFloor() == 1)
        {
            if(game->slimedied and pos().x() > 1196)
            {
                hitbox->posatt(0,368);
                game->Game::ChangeFloor(game->getFloor());
            }
            else if (pos().x() > 1196 and !game->slimedied)
            {
                setPos(1196, y());
                hitbox->posatt(x(),y());
            }
        }
        else if(game->getFloor() == 2)
        {
            if(pos().x() > 1124 and degrau == 0)
            {
                setPos(x()+this->getspeed(), y()+16);
                hitbox->posatt(x()+this->getspeed(), y()+16);
                degrau++;
            }
            else if(pos().x() > 1148 and degrau == 1)
            {
                setPos(x()+this->getspeed(), y()+16);
                hitbox->posatt(x()+this->getspeed(), y()+16);
                degrau++;
            }
            else if(pos().x() > 1172 and degrau == 2)
            {
                setPos(x()+this->getspeed(), y()+16);
                hitbox->posatt(x()+this->getspeed(), y()+16);
                degrau++;
            }
            else if(pos().x() > 1196 and degrau == 3 and game->skeletondied)
            {
                //setPos(x()+this->getspeed(), y()+16);
                hitbox->posatt(0, 368);
                game->Game::ChangeFloor(game->getFloor());
            }
            else if(pos().x() > 1196 and !game->skeletondied)
            {
                setPos(1196, y());
                hitbox->posatt(x(), y());
            }
        }
        else if(game->floor == 4)
        {
            if(pos().x() > 1000 and game->demondied == false)
            {
                setPos(1000, y());
                hitbox->posatt(1000, y());
            }
            if(pos().x() > 1196 and game->demondied == true)
            {
                hitbox->posatt(0,368);
                game->Game::ChangeFloor(game->getFloor());
            }
        }
        else if(pos().x() > 1196)
        {
            hitbox->posatt(0,368);
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
        {
            setPos(x(), y()-jumpspeed);
            if(looking == 1)
                hitbox->posatt(x(), y()-jumpspeed);
            else
                hitbox->posatt(x()+125, y()-jumpspeed);
        }
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

        if(pos().y()+fallspeed > 368)
        {
            setPos(x(), 368);

            if(looking == 1)
                hitbox->posatt(x(), 368);
            else
                hitbox->posatt(x()+125, 368);
        }
        else
        {
            setPos(x(), y()+fallspeed);

            if(looking == 1)
                hitbox->posatt(x(), y()+jumpspeed);
            else
                hitbox->posatt(x()+125, y()+jumpspeed);

            fallspeed += 1;
        }
        if(fall_moment == 24)
        {
            finishjump();
            dir_down = false;
        }
    }
    if(wanttoattack and !blocking)
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
                Slash * slash = new Slash();
                slash->setPos(x()+154,y()+60);
                scene()->addItem(slash);
            }
            else if(looking == 0)
            {
                Slash * slash = new Slash();
                slash->setPos(x()-50,y()+60);
                scene()->addItem(slash);
            }
        }

        attacking = true;
    }
    if(wanttospecialattack)
    {
        blocking = true;
    }
}

void Obiunam::hpdecrease(int a, int b)
{
    if(!gettinghit)
    {
        if(looking == 1)
        {
            setPixmap(QPixmap(":/images/obiunamdirhit"));
        }
        else
        {
            setPixmap(QPixmap(":/images/obiunamesqhit"));
        }
        if(b == 1)
        {
            this->setPos(x()-60, y()-60);
            hitbox->posatt(x()-60, y()-60);
            dir_down = true;
        }
        else
        {
            this->setPos(x()+60, y()-60);
            hitbox->posatt(x()+60, y()-60);
            dir_down = true;
        }
        gettinghit = true;
        int blocking_damage = a/4;

        if(!blocking)
            hp -= a;
        else
            hp -= blocking_damage;

        game->health->att(hp);

        if(hp < 1)
        {
            blocking = false;
            wanttoattack = false;
            specialattacking = false;
            wanttospecialattack = false;
            looking = 1;
            gettinghit = false;
            attacking = false;
            dir_down = false;
            dir_up = false;
            dir_right = false;
            dir_left = false;

            delete hitbox;

            setPixmap(QPixmap(":/images/obiunamhitbox"));

            game->endgame(0);
        }
    }
}

void Obiunam::heal(int a)
{
    if(looking == 0)
        setPixmap(QPixmap(":/images/obiunamesqheal"));
    else
        setPixmap(QPixmap(":/images/obiunamdirheal"));

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

float Obiunam::getxposition()
{
    if(looking == 1)
    {
        return pos().x();
    }
    else
    {
        return pos().x()+119;
    }
}
