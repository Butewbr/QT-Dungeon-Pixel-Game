#ifndef GROUND_H
#define GROUND_H

#include <QObject>
#include <QGraphicsPixmapItem>


class Ground : public QObject, public QGraphicsPixmapItem
{
public:
    Ground();
    void changeGround(int a);
    float getHeight();
};

#endif // GROUND_H
