#include "chest.h"
#include "game.h"
#include "QDebug"

extern Game * game;

Chest::Chest(QGraphicsItem *parent): QObject(), QGraphicsPixmapItem(parent)
{
    setPixmap(QPixmap(":/images/chestbig.png"));

    motion = new QTimer();
    connect(motion, SIGNAL(timeout()), this, SLOT(open()));
    motion->start(17);
}

void Chest::open()
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
        timer++;
        if(!opened)
        {
            setPos(x(), y()-48);
            setPixmap(QPixmap(":/images/chestopenedbig.png"));
            opened = true;
            timer = 0;
        }
        if(timer == 50 and opened)
        {
            game->endgame(1);
        }
        else if(timer == 50)
        {
            timer = 0;
        }
    }
}
