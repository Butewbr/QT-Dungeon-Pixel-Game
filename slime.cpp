#include "slime.h"
#include "game.h"
#include "carbunis.h"
#include "obiunam.h"
#include "burger.h"

extern Game * game;

Slime::Slime(QGraphicsItem *parent)
{
    setPixmap(QPixmap(":/images/bigslimeupsidedown"));
    hp = 30;
    dashcd = 6000;

    movement = new QTimer();
    connect(movement, SIGNAL(timeout()), this, SLOT(move()));
    movement->start(17);

    invincibility = new QTimer();
    connect(invincibility, SIGNAL(timeout()), this, SLOT(finishhit()));
    invincibility->start(17);
}

void Slime::move()
{
    QList<QGraphicsItem *> colliding_item = collidingItems();

    if(game->isitmage)
    {
        if(game->mage->getxposition() > this->pos().x()-100)
        {
            shouldfall = true;
        }
    }
    else
    {
        if(game->warrior->getxposition() > this->pos().x()-100)
        {
            shouldfall = true;
        }
    }
    if(shouldfall)
    {
        if(fall_moment == 100)
        {
            shouldfall = false;
            fallspeed = 0;
            fall_moment = 0;
        }

        fall_moment += 1;

        if(fall_moment > 10 and gettinghit == false)
        {
            setPixmap(QPixmap(":/images/bigslime"));
        }

        if(pos().y()+fallspeed > 390)
        {
            setPos(x(), 390);
            shouldfall = false;
            fell = true;
        }
        else
        {
            setPos(x(), y()+fallspeed);
            fallspeed += 0.5;
        }

    }
    if(!shouldfall)
    {
        float dist;
        if(game->isitmage)
            dist = this->pos().x()-game->mage->getxposition();
        else
            dist = this->pos().x()-game->warrior->getxposition();

        if(dist > 0) //se o jogador ta a esquerda
        {
            for(int i = 0, n = colliding_item.size(); i < n; i++)
            {
                if(typeid(*(colliding_item[i])) == typeid(Carbunis))
                {
                    game->mage->hpdecrease(8, 1);

                    return;
                }
                if(typeid(*(colliding_item[i])) == typeid(Hitbox))
                {
                    game->warrior->hpdecrease(8, 1);

                    return;
                }
            }
            walking_moment++;

            if(dist < 600 and fell == true and dashed == false and walking_moment == 15)
            {
                walkingspeed += 6;
                dashed = true;
            }

            if(walking_moment > 0 and walking_moment < 20)
            {
                setPos(x()-walkingspeed,y());
            }

            if(walkingspeed < 2)
            {
                walkingspeed += 0.2;
            }
            if(walking_moment == 100)
            {
                walkingspeed = 0;
                walking_moment = 0;
            }
            QTimer::singleShot(dashcd, this, SLOT(finishdash()));
        }
        else
        {
            for(int i = 0, n = colliding_item.size(); i < n; i++)
            {
                if(typeid(*(colliding_item[i])) == typeid(Carbunis))
                {
                    game->mage->hpdecrease(5, 0);

                    return;
                }
                if(typeid(*(colliding_item[i])) == typeid(Hitbox))
                {
                    game->warrior->hpdecrease(5, 0);

                    return;
                }
            }

            walking_moment++;

            if(dist > -400 and fell == true and dashed == false)
            {
                walkingspeed += 10;
                dashed = true;
            }


            if(walking_moment > 0 and walking_moment < 20)
            {
                setPos(x()+walkingspeed,y());
            }

            if(walkingspeed < 2)
            {
                walkingspeed += 0.2;
            }
            if(walking_moment == 100)
            {
                walkingspeed = 0;
                walking_moment = 0;
            }
            QTimer::singleShot(dashcd, this, SLOT(finishdash()));
        }
    }
}

void Slime::getHit(int a)
{
    if(!gettinghit)
    {
        setPixmap(QPixmap(":/images/bigslimehit"));
        hp -= a;

        if(game->isitmage)
        {
            if(game->mage->getxposition() < this->pos().x())
                setPos(x()+30, y()-60);
            else
                setPos(x()-30, y()-60);
        }
        else
        {
            if(game->warrior->getxposition() < this->pos().x())
                setPos(x()+10, y()-60);
            else
                setPos(x()-10, y()-60);
        }

        shouldfall = true;
        gettinghit = true;
    }

    //QTimer::singleShot(invincibility, this, SLOT(finishhit()));

    if(hp < 1)
    {
        Burger * burger = new Burger();
        burger->setPos(x(),560);
        scene()->addItem(burger);

        game->slimedied = true;
        scene()->removeItem(this);
        //delete this;
    }
}

void Slime::finishhit()
{
    invincibility_frame++;
    if(invincibility_frame == 10)
    {
        gettinghit = false;
        //setPixmap(QPixmap(":/images/bigslime"));
        invincibility_frame = 0;
    }
}
