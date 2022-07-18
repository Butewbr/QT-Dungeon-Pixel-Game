#include "specialattack.h"
#include "game.h"

extern Game * game;

SpecialAttack::SpecialAttack(QGraphicsItem *parent): QObject(), QGraphicsPixmapItem(parent)
{
    direction = game->mage->getLook();
    if(direction == 1)
    {
        setPixmap(QPixmap(":/images/spright.png"));
        QTimer * timer = new QTimer();
        connect(timer,SIGNAL(timeout()),this,SLOT(move()));
        timer->start(17);
    }
    else
    {
        setPixmap(QPixmap(":/images/spleft.png"));
        QTimer * timer = new QTimer();
        connect(timer,SIGNAL(timeout()),this,SLOT(move()));
        timer->start(17);
    }
}

void SpecialAttack::move()
{
    QList<QGraphicsItem *> colliding_item = collidingItems();

    for(int i = 0, n = colliding_item.size(); i < n; i++)
    {
        if(typeid(*(colliding_item[i])) == typeid(Slime))
        {
            scene()->removeItem(this);

            Slime* aux = dynamic_cast<Slime*> (colliding_item[i]);

            aux->getHit(10);

            //game->slime->getHit(10);

            delete this;

            return;
        }
        if(typeid(*(colliding_item[i])) == typeid(Skeleton))
        {
            scene()->removeItem(this);

            Skeleton* aux = dynamic_cast<Skeleton*> (colliding_item[i]);

            aux->getHit(10);

            //game->skeleton->getHit(10);

            delete this;

            return;
        }
        if(typeid(*(colliding_item[i])) == typeid(Demon))
        {
            scene()->removeItem(this);

            Demon* aux = dynamic_cast<Demon*> (colliding_item[i]);

            aux->getHit(10);

            //game->skeleton->getHit(10);

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

        if(pos().x() < -284)
        {
            scene()->removeItem(this);
            delete this;
        }
    }
}
