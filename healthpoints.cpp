#include "healthpoints.h"
#include "game.h"
#include "QTimer"

extern Game * game;

HealthPoints::HealthPoints(QGraphicsItem *parent):QGraphicsTextItem(parent)
{
    currenthp = 35;

    setPlainText(QString("❤ ") + QString::number(currenthp));
    setDefaultTextColor(Qt::red);
    setFont(QFont("calligraphr",26));
}

void HealthPoints::att(int a)
{
    currenthp = a;

    setPlainText(QString("❤ ") + QString::number(currenthp));
    setDefaultTextColor(Qt::red);
    setFont(QFont("calligraphr",26));
}

