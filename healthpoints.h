#ifndef HEALTHPOINTS_H
#define HEALTHPOINTS_H

#include <QGraphicsTextItem>

class HealthPoints: public QGraphicsTextItem
{
public:
    HealthPoints(QGraphicsItem *parent = 0);

private:
    int currenthp;

public slots:
    void att(int a);
};

#endif // HEALTHPOINTS_H
