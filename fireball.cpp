#include "fireball.h"
#include "game.h"

extern Game * game;

FireBall::FireBall(QGraphicsItem *parent)
{
    direction = game->demon->getLook();

    QTimer * timer = new QTimer();
    connect(timer,SIGNAL(timeout()),this,SLOT(move()));
    timer->start(17);
}

void FireBall::move()
{
    QList<QGraphicsItem *> colliding_item = collidingItems();

    for(int i = 0, n = colliding_item.size(); i < n; i++)
    {
        if(typeid(*(colliding_item[i])) == typeid(Carbunis))
        {
            scene()->removeItem(this);

            game->mage->hpdecrease(8);

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
    }
    if(direction == 1)
    {
        setPixmap(QPixmap(":/images/fireballrightbig"));

        setPos(x()+12,y());

        if(pos().x() > 1279)
        {
            scene()->removeItem(this);
            delete this;
        }
    }
    else
    {
        setPixmap(QPixmap(":/images/fireballleftbig"));
        setPos(x()-12,y());

        if(pos().x() < -150)
        {
            scene()->removeItem(this);
            delete this;
        }
    }
}
