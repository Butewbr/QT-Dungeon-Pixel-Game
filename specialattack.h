#ifndef SPECIALATTACK_H
#define SPECIALATTACK_H

#include <QGraphicsItem>
#include <QPixmap>
#include <QGraphicsPixmapItem>
#include <QObject>
#include <QTimer>

class SpecialAttack: public QObject,public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    SpecialAttack(QGraphicsItem *parent = 0);
    int direction;

public slots:
    void move();
};

#endif // SPECIALATTACK_H
