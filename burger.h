#ifndef BURGER_H
#define BURGER_H

#include <QGraphicsItem>
#include <QPixmap>
#include <QGraphicsPixmapItem>
#include <QObject>
#include <QTimer>

class Burger: public QObject,public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Burger(QGraphicsItem *parent = 0);
    float burgerspeed = 5;

    QTimer * motion;

public slots:
    void pickup();
};

#endif // BURGER_H
