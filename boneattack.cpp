#include "boneattack.h"
#include "game.h"

extern Game * game;

BoneAttack::BoneAttack(QGraphicsItem *parent): QObject(), QGraphicsPixmapItem(parent)
{
    attack_frame = 1;
    direction = game->skeleton->getLook();
    setPixmap(QPixmap(":/images/boneattack1big"));

    QTimer * timer = new QTimer();
    connect(timer,SIGNAL(timeout()),this,SLOT(move()));
    timer->start(17);
}

void BoneAttack::move()
{
    QList<QGraphicsItem *> colliding_item = collidingItems();

    if(attack_frame == 1)
    {
        setPixmap(QPixmap(":/images/boneattack1big"));
        attack_frame++;
    }
    else
    {
        setPixmap(QPixmap(":/images/boneattack2big"));
        attack_frame = 1;
    }

    for(int i = 0, n = colliding_item.size(); i < n; i++)
    {
        if(typeid(*(colliding_item[i])) == typeid(Carbunis))
        {
            scene()->removeItem(this);

            game->mage->hpdecrease(6);

            delete this;

            return;
        }
        if(typeid(*(colliding_item[i])) == typeid(Hitbox))
        {
            scene()->removeItem(this);

            game->warrior->hpdecrease(6);

            delete this;

            return;
        }
    }
    if(direction == 1)
    {
        setPos(x()+12,y());

        if(pos().x() > 1279)
        {
            scene()->removeItem(this);
            delete this;
        }
    }
    else
    {
        setPos(x()-12,y());

        if(pos().x() < 1)
        {
            scene()->removeItem(this);
            delete this;
        }
    }
}
