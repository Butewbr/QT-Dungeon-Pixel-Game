#include "meteor.h"
#include "game.h"

extern Game * game;

Meteor::Meteor(QGraphicsItem *parent)
{
    setPixmap(QPixmap(":/images/meteorbig.png"));

    QTimer * timer = new QTimer();
    connect(timer,SIGNAL(timeout()),this,SLOT(move()));
    timer->start(17);
}

void Meteor::move()
{
    QList<QGraphicsItem *> colliding_item = collidingItems();

    for(int i = 0, n = colliding_item.size(); i < n; i++)
    {
        if(typeid(*(colliding_item[i])) == typeid(Carbunis))
        {
            scene()->removeItem(this);

            game->mage->hpdecrease(9);

            delete this;

            return;
        }
        if(typeid(*(colliding_item[i])) == typeid(Hitbox))
        {
            scene()->removeItem(this);

            game->warrior->hpdecrease(8);

            delete this;

            return;
        }
        if(typeid(*(colliding_item[i])) == typeid(Skeleton))
        {
            scene()->removeItem(this);

            Skeleton* aux = dynamic_cast<Skeleton*> (colliding_item[i]);

            aux->getHit(9);

            delete this;

            return;
        }
    }

    setPos(x(),y()+15);

    if(pos().y() > 455)
    {
        scene()->removeItem(this);
        delete this;
    }
}
