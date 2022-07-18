#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>
#include <QWidget>
#include <QGraphicsScene>
#include <QTimer>
#include "carbunis.h"
#include "obiunam.h"
#include "ground.h"
#include "slime.h"
#include "skeleton.h"
#include "entrance.h"
#include "demon.h"
#include "burger.h"
#include "healthpoints.h"
#include "chest.h"
#include "mainwindow.h"

class Game: public QGraphicsView
{
public:
    Game(int a);
    ~Game() {delete scene;};
    int getFloor() {return floor;};
    void ChangeFloor(int b = 1);
    void endgame(int a);
    void displayEndGamewindow(QString w);
    void Rectangle(int x, int y, int width, int height, QColor color, double opacity);

    bool isitmage = false;
    bool slimedied = false;
    bool skeletondied = false;
    bool demondied = false;

    QGraphicsScene * scene;
    Carbunis * mage;
    Obiunam * warrior;
    Ground * ground;
    Slime * slime;
    Entrance * entrance;
    Skeleton * skeleton;
    Slime * slime2;
    Slime * slime3;
    Demon * demon;
    HealthPoints * health;
    Chest * chest;

    int floor;

public slots:
    void openMainMenu();
};

#endif // GAME_H
