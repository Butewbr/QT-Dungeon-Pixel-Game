#include "ground.h"

Ground::Ground()
{
    setPixmap(QPixmap(":/images/ground0.png"));
}


void Ground::changeGround(int a)
{
    if(a == 2)
    {
        setPixmap(QPixmap(":/images/ground1.png"));
    }
    if(a == 3)
    {
        setPixmap(QPixmap(":/images/ground3big.png"));
    }
    if(a == 4)
    {
        return;
    }
    if(a == 5)
    {
        setPixmap(QPixmap(":/images/groundfinalbig.png"));
    }
}
