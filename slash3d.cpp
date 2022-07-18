#include "slash3d.h"
#include "game.h"
#include "slime.h"

extern Game * game;

Slash::Slash(QGraphicsItem *parent): QObject(), QGraphicsPixmapItem(parent)
{
    direction = game->warrior->getLook();
    if(direction == 1)
    {
        setPixmap(QPixmap(":/images/slashobright.png"));
        QTimer * timer = new QTimer();
        connect(timer,SIGNAL(timeout()),this,SLOT(move()));
        timer->start(17);
    }
    else
    {
        setPixmap(QPixmap(":/images/slashobleft.png"));
        QTimer * timer = new QTimer();
        connect(timer,SIGNAL(timeout()),this,SLOT(move()));
        timer->start(17);
    }
}

void Slash::move()
{
    QList<QGraphicsItem *> colliding_item = collidingItems();
    for(int i = 0, n = colliding_item.size(); i < n; i++)
    {
        if(typeid(*(colliding_item[i])) == typeid(Slime))
        {
            Slime* aux = dynamic_cast<Slime*> (colliding_item[i]);

            aux->getHit(4);

            //game->slime->getHit(5);
        }
        if(typeid(*(colliding_item[i])) == typeid(Skeleton))
        {
            Skeleton* aux = dynamic_cast<Skeleton*> (colliding_item[i]);

            aux->getHit(4, direction);

            //game->skeleton->getHit(5);
        }
        if(typeid(*(colliding_item[i])) == typeid(Demon))
        {
            Demon* aux = dynamic_cast<Demon*> (colliding_item[i]);

            aux->getHit(1.3);

            //game->skeleton->getHit(5);
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

        if(pos().x() > begincoordinate + 80)
        {
            scene()->removeItem(this);
            delete this;
        }
    }
    else
    {
        setPos(x()-15,y());

        if(pos().x() < begincoordinate - 80)
        {
            scene()->removeItem(this);
            delete this;
        }
    }
}
