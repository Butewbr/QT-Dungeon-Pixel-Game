#include "attack.h"
#include "game.h"
#include "slime.h"

extern Game * game;

Attack::Attack(QGraphicsItem *parent): QObject(), QGraphicsPixmapItem(parent)
{
    direction = game->mage->getLook();
    if(direction == 1)
    {
        setPixmap(QPixmap(":/images/slash2.png"));
        QTimer * timer = new QTimer();
        connect(timer,SIGNAL(timeout()),this,SLOT(move()));
        timer->start(17);
    }
    else
    {
        setPixmap(QPixmap(":/images/slashleft.png"));
        QTimer * timer = new QTimer();
        connect(timer,SIGNAL(timeout()),this,SLOT(move()));
        timer->start(17);
    }
}

void Attack::move()
{
    QList<QGraphicsItem *> colliding_item = collidingItems();
    for(int i = 0, n = colliding_item.size(); i < n; i++)
    {
        if(typeid(*(colliding_item[i])) == typeid(Slime))
        {
            scene()->removeItem(this);

            Slime* aux = dynamic_cast<Slime*> (colliding_item[i]);

            aux->getHit(4);

            //game->slime->getHit(5);

            delete this;

            return;
        }
        if(typeid(*(colliding_item[i])) == typeid(Skeleton))
        {
            scene()->removeItem(this);

            Skeleton* aux = dynamic_cast<Skeleton*> (colliding_item[i]);

            aux->getHit(4);

            //game->skeleton->getHit(5);
            delete this;

            return;
        }
        if(typeid(*(colliding_item[i])) == typeid(Demon))
        {
            scene()->removeItem(this);

            Demon* aux = dynamic_cast<Demon*> (colliding_item[i]);

            aux->getHit(3.75);

            //game->skeleton->getHit(5);
            delete this;

            return;
        }
    }
    if(moment == 0)
    {
        begincoordinate = pos().x();
        moment++;
    }
    if(direction == 1)
    {
        setPos(x()+15,y());

        if(pos().x() > begincoordinate + 75)
        {
            scene()->removeItem(this);
            delete this;
        }
    }
    else
    {
        setPos(x()-15,y());

        if(pos().x() < begincoordinate - 75)
        {
            scene()->removeItem(this);
            delete this;
        }
    }
}
