#ifndef BONEATTACK_H
#define BONEATTACK_H

#include <QGraphicsItem>
#include <QPixmap>
#include <QGraphicsPixmapItem>
#include <QObject>
#include <QTimer>

class BoneAttack: public QObject,public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    BoneAttack(QGraphicsItem *parent = 0);
    int direction;
    int attack_frame;

public slots:
    void move();
};

#endif // BONEATTACK_H
