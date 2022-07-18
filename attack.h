#ifndef ATTACK_H
#define ATTACK_H

#include <QGraphicsItem>
#include <QPixmap>
#include <QGraphicsPixmapItem>
#include <QObject>
#include <QTimer>
#include "slime.h"

class Attack: public QObject,public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Attack(QGraphicsItem *parent = 0);
    int direction;
    int begincoordinate;
    int moment = 0;

public slots:
    void move();
};

#endif // ATTACK_H
