#include "hitbox.h"

Hitbox::Hitbox(QGraphicsItem *parent): QObject(), QGraphicsPixmapItem(parent)
{   
    setPixmap(QPixmap(":/images/obiunamhitbox"));
    //setPixmap(QPixmap(":/images/hitboxdebug"));
}

void Hitbox::posatt(float a, float b)
{
    setPos(a, b);
}
