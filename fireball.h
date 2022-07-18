#ifndef FIREBALL_H
#define FIREBALL_H

#include <QGraphicsItem>
#include <QPixmap>
#include <QGraphicsPixmapItem>
#include <QObject>
#include <QTimer>

class FireBall: public QObject,public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    FireBall(QGraphicsItem *parent = 0);
    int direction;

public slots:
    void move();
};

#endif // FIREBALL_H
