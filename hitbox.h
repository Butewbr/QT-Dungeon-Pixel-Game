#ifndef HITBOX_H
#define HITBOX_H

#include <QGraphicsItem>
#include <QPixmap>
#include <QGraphicsPixmapItem>
#include <QObject>
#include <QTimer>

class Hitbox : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Hitbox(QGraphicsItem *parent = 0);
    void posatt(float a, float b);
};

#endif // HITBOX_H
