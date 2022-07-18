#include "demon.h"
#include "game.h"
#include "meteor.h"
#include "fireball.h"
#include "skeleton.h"
#include "slime.h"

extern Game * game;

Demon::Demon(QGraphicsItem *parent)
{
    setPixmap(QPixmap(":/images/demonhuge"));

    hp = 350;

    movementcd = new QTimer();
    connect(movementcd, SIGNAL(timeout()), this, SLOT(move()));
    movementcd->start(17);

    flycd = new QTimer();
    connect(flycd, SIGNAL(timeout()), this, SLOT(fly()));
    flycd->start(10000);

    meteorcd = new QTimer();
    connect(meteorcd, SIGNAL(timeout()), this, SLOT(meteorattack()));
    meteorcd->start(1250);

    attackcd = new QTimer();
    connect(attackcd, SIGNAL(timeout()), this, SLOT(attack()));
    attackcd->start(2500);

    spawncd = new QTimer();
    connect(spawncd, SIGNAL(timeout()), this, SLOT(spawn()));
    spawncd->start(13000);

    blinkcd = new QTimer();
    connect(blinkcd, SIGNAL(timeout()), this, SLOT(tp()));
    blinkcd->start(6000);
}

void Demon::move()
{
    if(game->isitmage)
    {
        if(game->mage->getxposition() < this->pos().x())
        {
            look = 0;

            if(floating)
            {
                if(!displacement)
                {
                    setPos(x()-72, y()-80);
                    displacement = true;
                }
                setPixmap(QPixmap(":/images/demonwaurahuge"));
            }
            else if(!gettinghit)
                setPixmap(QPixmap(":/images/demonhuge"));
            else
                setPixmap(QPixmap(":/images/demonhit"));
        }
        else
        {
            look = 1;

            if(floating)
            {
                if(!displacement)
                {
                    setPos(x()-72, y()-80);
                    displacement = true;
                }
                setPixmap(QPixmap(":/images/demonwaurahugeright"));
            }
            else if(!gettinghit)
                setPixmap(QPixmap(":/images/demonhugeright"));
            else
                setPixmap(QPixmap(":/images/demonhitright"));
        }
    }
    else
    {
        if(game->warrior->getxposition() < this->pos().x())
        {
            look = 0;

            if(floating)
            {
                if(!displacement)
                {
                    setPos(x()-72, y()-80);
                    displacement = true;
                }
                setPixmap(QPixmap(":/images/demonwaurahuge"));
            }
            else if(!gettinghit)
                setPixmap(QPixmap(":/images/demonhuge"));
            else
                setPixmap(QPixmap(":/images/demonhit"));
        }
        else
        {
            look = 1;

            if(floating)
            {
                if(!displacement)
                {
                    setPos(x()-72, y()-80);
                    displacement = true;
                }
                setPixmap(QPixmap(":/images/demonwaurahugeright"));
            }
            else if(!gettinghit)
                setPixmap(QPixmap(":/images/demonhugeright"));
            else
                setPixmap(QPixmap(":/images/demonhitright"));
        }
    }

    if(floating)
    {
        can_be_hit = false;
        if(floating_moment < 100)//faz 100x isso
        {
            setPos(x(), y()-0.5);
        }
        else if(floating_moment >= 100 and floating_moment < 200)//faz 100x isso
        {
            setPos(x(), y()+0.5);
        }

        floating_moment++;

        if(floating_moment == 200)
        {
            floating_moment = 0;
            floatingloop++;
        }
        if(floatingloop == 3)
        {
            floatingloop = 0;
            floating = false;
            justfloated = true;
            displacement = false;
            finishedfalling = false;

            setPos(x()+72, y()+80);

            if(look == 0)
            {
                setPixmap(QPixmap(":/images/demonhuge"));
            }
            else
            {
                setPixmap(QPixmap(":/images/demonhugeright"));
            }
            can_be_hit = true;
        }
    }
    if(flying)
    {
        flying_moment++;

        setPos(x(), y()-flying_speed);
        flying_speed--;

        if(flying_moment == 19)
        {
            flying_speed = 20;
            flying_moment = 0;
            floating = true;
            flying = false;
        }
    }
    if(justfloated)
    {
        fall_moment += 1;

        if(pos().y()+fallspeed > 220)
        {
            setPos(x(), 220);
            finishedfalling = true;
            QTimer::singleShot(6000, this, SLOT(canflyagain()));
        }
        else
        {
            setPos(x(), y()+fallspeed);
            fallspeed += 1;
        }
        if(finishedfalling)
        {
            fallspeed = 0;
            fall_moment = 0;
            justfloated = false;
        }
    }
}

void Demon::fly()
{
    if(!justflew)
    {
        flying = true;
        justflew = true;
    }
}

void Demon::meteorattack()
{
    if(floating)
    {
        Meteor * meteoro = new Meteor();
        if(game->isitmage)
        {
            meteoro->setPos(game->mage->getxposition(), -132);
        }
        else
        {
            meteoro->setPos(game->warrior->getxposition(), -132);
        }
        scene()->addItem(meteoro);
    }
}

void Demon::attack()
{
    if(!floating and !flying and !justfloated)
    {
        FireBall * fireball = new FireBall();

        if(look == 0 and highattack)
            fireball->setPos(x()-100,y()+80);
        else if(look == 1 and highattack)
            fireball->setPos(x()+150,y()+80);

        if(look == 0 and !highattack)
            fireball->setPos(x()-100,y()+250);
        else if(look == 1 and !highattack)
            fireball->setPos(x()+150,y()+250);

        scene()->addItem(fireball);
    }
    if(highattack)
    {
        highattack = false;
        return;
    }
    else
    {
        highattack = true;
        return;
    }
}

void Demon::spawn()
{
    int random_number = 200+rand()%800;
    Skeleton * esqueleto = new Skeleton();
    esqueleto->setPos(random_number, 370);
    scene()->addItem(esqueleto);
    esqueleto->getHit(78);
}

void Demon::getHit(float a)
{
    if(can_be_hit)
    {
        gettinghit = true;
        hp -= a;
        QTimer::singleShot(850, this, SLOT(finishhit()));
    }

    if(hp < 1)
    {
        game->demondied = true;
        scene()->removeItem(this);

        delete this;
    }
}

void Demon::tp()
{
    int random_number = 0+rand()%800;
    if(hp < 170)
    {
        setPos(random_number, y());
        spawncd->start(3500);
    }
}
