#ifndef CHEST_H
#define CHEST_H

#include <QGraphicsItem>
#include <QPixmap>
#include <QGraphicsPixmapItem>
#include <QObject>
#include <QTimer>

class Chest: public QObject,public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Chest(QGraphicsItem *parent = 0);
    bool opened = false;
    int timer;

    QTimer * motion;

public slots:
    void open();
};

#endif // CHEST_H
