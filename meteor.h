#ifndef METEOR_H
#define METEOR_H

#include <QGraphicsItem>
#include <QPixmap>
#include <QGraphicsPixmapItem>
#include <QObject>
#include <QTimer>

class Meteor: public QObject,public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Meteor(QGraphicsItem *parent = 0);

public slots:
    void move();
};

#endif // METEOR_H
