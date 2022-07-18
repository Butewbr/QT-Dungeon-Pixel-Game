#include "burger.h"
#include "game.h"
#include "QDebug"

extern Game * game;

Burger::Burger(QGraphicsItem *parent): QObject(), QGraphicsPixmapItem(parent)
{
    setPixmap(QPixmap(":/images/bigburger.png"));

    motion = new QTimer();
    connect(motion, SIGNAL(timeout()), this, SLOT(pickup()));
    motion->start(17);
}

void Burger::pickup()
{
    float distance;
    if(game->isitmage)
    {
        if(game->mage->getxposition() > this->pos().x())
            distance = game->mage->getxposition() - this->pos().x();
        else
            distance = this->pos().x() - game->mage->getxposition();
    }
    else
    {
        if(game->warrior->getxposition() > this->pos().x())
            distance = game->warrior->getxposition() - this->pos().x();
        else
            distance = this->pos().x() - game->warrior->getxposition();
    }

    //qDebug() << distance;

    if(distance < 200)
    {
        setPos(x(), y()-burgerspeed);
        burgerspeed -= 0.5;

        if(burgerspeed == 0)
        {
            if(game->isitmage)
                game->mage->heal(5);
            else
                game->warrior->heal(5);

            scene()->removeItem(this);
            delete this;
        }
    }
}
