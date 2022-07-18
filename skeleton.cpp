#include "skeleton.h"
#include "game.h"
#include "carbunis.h"
#include "obiunam.h"
#include "boneattack.h"
#include "burger.h"
#include "hitbox.h"

extern Game * game;

Skeleton::Skeleton(QGraphicsItem *parent)
{
    setPixmap(QPixmap(":/images/skeleton"));
    hp = 100;

    movement = new QTimer();
    connect(movement, SIGNAL(timeout()), this, SLOT(move()));
    movement->start(1500);

    QTimer * changelook = new QTimer();
    connect(changelook, SIGNAL(timeout()), this, SLOT(lookagain()));
    changelook->start(17);

    falling = new QTimer();
    connect(falling, SIGNAL(timeout()), this, SLOT(fall()));
    falling->start(17);

    attacktimer = new QTimer();
    connect(attacktimer, SIGNAL(timeout()), this, SLOT(Attack()));
    attacktimer->start(3000);
}

void Skeleton::Attack()
{
    BoneAttack * boneattack = new BoneAttack();
    if(looking == 0)
        boneattack->setPos(x(),y()+100);
    else
        boneattack->setPos(x()+163, y()+100);

    scene()->addItem(boneattack);
}

void Skeleton::move()
{
    int random_number = 0+rand()%30-10;
    float player_position;
    if(game->isitmage)
    {
        player_position = game->mage->getxposition(); //se é menor que 0 significa que o jogador ta à direita
    }
    else
    {
        player_position = game->warrior->getxposition();
    }
    if(player_position > this->pos().x())//ta a direita do esqueleto
    {
        looking = 1;
        if(walking_moment < 2)
        {
            setPixmap(QPixmap(":/images/skeleton"));
            setPos(x()+random_number, y());
            walking_moment++;
        }
        else if(this->pos().x() > 100)
        {
            setPos(x()-random_number, y());
            walking_moment++;
            if(walking_moment == 4)
            {
                finishhit();
                walking_moment = 0;
            }
        }
        else
        {
            setPos(x()+20, y());
            walking_moment++;

            if(walking_moment == 4)
            {
                walking_moment = 0;
            }
        }
    }
    if(player_position < this->pos().x())
    {
        if(walking_moment < 2)
        {
            looking = 0;
            setPixmap(QPixmap(":/images/skeletonleft"));
            setPos(x()-random_number, y());
            walking_moment++;
        }
        else if(this->pos().x() < 1000)
        {
            looking = 0;
            setPos(x()+random_number, y());
            walking_moment++;
            if(walking_moment == 4)
            {
                walking_moment = 0;
            }
        }
        else
        {
            looking = 0;
            setPos(x()-40, y());
            walking_moment++;

            if(walking_moment == 4)
            {
                walking_moment = 0;
            }
        }
    }
}

void Skeleton::getHit(int a) //hit by mage/demon
{
    if(!gettinghit)
    {
        hp -= a;

        if(game->isitmage)
        {
            if(game->mage->getxposition() < this->pos().x())
            {
                if(pos().x() < 1000)
                    setPos(x()+30, y()-60);
                setPixmap(QPixmap(":/images/skeletonhit"));
            }
            else
            {
                if(pos().x() > 100)
                    setPos(x()-30, y()-60);
                setPixmap(QPixmap(":/images/skeletonhitright"));
            }
        }

        shouldfall = true;
    }
    gettinghit = true;

    //QTimer::singleShot(invincibility, this, SLOT(finishhit()));

    if(hp < 1)
    {
        Burger * burger = new Burger();
        burger->setPos(x(),560);
        scene()->addItem(burger);

        game->skeletondied = true;
        scene()->removeItem(this);
        delete this;
    }
}

void Skeleton::getHit(int a, int b) //hit by warrior
{
    if(!gettinghit)
    {
        hp -= a;

        if(b == 1)
        {
            if(pos().x() < 1000)
                setPos(x()+10, y()-15);
            setPixmap(QPixmap(":/images/skeletonhit"));
        }
        else
        {
            if(pos().x() > 100)
                setPos(x()-10, y()-15);
            setPixmap(QPixmap(":/images/skeletonhitright"));
        }

        shouldfall = true;
    }
    gettinghit = true;

    if(hp < 1)
    {
        Burger * burger = new Burger();
        burger->setPos(x(),560);
        scene()->addItem(burger);

        game->skeletondied = true;
        scene()->removeItem(this);
        delete this;
    }
}

void Skeleton::fall()
{
    if(shouldfall)
    {
        if(fall_moment == 100)
        {
            shouldfall = false;
            fallspeed = 0;
            fall_moment = 0;
        }

        fall_moment += 1;

        if(pos().y()+fallspeed > 370)
        {
            setPos(x(), 370);
            shouldfall = false;
            fell = true;
        }
        else
        {
            setPos(x(), y()+fallspeed);
            fallspeed += 0.5;
        }

    }
}

void Skeleton::lookagain()
{
    invincibility_frame++;
    if(invincibility_frame == 10)
    {
        finishhit();
        invincibility_frame = 0;
    }
    float player_position;
    if(game->isitmage)
    {
        player_position = game->mage->getxposition(); //se é menor que 0 significa que o jogador ta à direita
    }
    else
    {
        player_position = game->warrior->getxposition();
    }
    if(player_position < this->pos().x())
    {
        looking = 0;
        if(!gettinghit)
            setPixmap(QPixmap(":/images/skeletonleft"));
        else
            setPixmap(QPixmap(":/images/skeletonhit"));
    }
    else
    {
        looking = 1;
        if(!gettinghit)
            setPixmap(QPixmap(":/images/skeleton"));
        else
            setPixmap(QPixmap(":/images/skeletonhitright"));
    }
}
