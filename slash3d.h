#ifndef SLASH_H
#define SLASH_H

#include <QGraphicsItem>
#include <QPixmap>
#include <QGraphicsPixmapItem>
#include <QObject>
#include <QTimer>
#include "slime.h"

class Slash: public QObject,public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Slash(QGraphicsItem *parent = 0);
    int direction;
    int begincoordinate;
    int moment = 0;
    void bedeleted() {delete this;};

public slots:
    void move();
};

#endif // SLASH_H
