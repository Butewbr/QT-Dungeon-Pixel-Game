#include <QGraphicsTextItem>
#include <QTimer>
#include <QImage>
#include <QBrush>
#include "game.h"

Game::Game(int a)
{
    scene = new QGraphicsScene();
    scene->setSceneRect(0,0,1280,720);
    scene->setBackgroundBrush(QBrush(QImage(":/images/backgroundoutsidewentrancebig")));

    //aaaaaaaaaaaaaaaaaaaaaaaaa
    /*demon = new Demon();
    demon->setPos(700, 220);
    scene->addItem(demon);*/
    //testandooooooooooooooooooo

    ground = new Ground();
    ground->setPos(0, 619);
    scene->addItem(ground);

    entrance = new Entrance();
    entrance->setPos(558,0);
    entrance->setZValue(2);
    scene->addItem(entrance);

    floor = 0;

    setScene(scene);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(1280,720);

    if(a == 1)
    {
        isitmage = true;
        mage = new Carbunis();
        mage->setPos(120, 354);
        mage->setFlag(QGraphicsItem::ItemIsFocusable);
        mage->setFocus();
        scene->addItem(mage);
    }
    if(a == 2)
    {
        isitmage = false;
        warrior = new Obiunam();
        warrior->setPos(120, 368);
        warrior->setZValue(1);
        warrior->setFlag(QGraphicsItem::ItemIsFocusable);
        warrior->setFocus();
        scene->addItem(warrior);
    }

    health = new HealthPoints();
    health->setPos(health->x()+25, health->y()+25);
    scene->addItem(health);

    show();
}

void Game::ChangeFloor(int b)//b é o floor do momento; a é a direção, se tá indo pro próximo ou voltando
{
    if(b == 0)
    {
        if(isitmage)
            mage->setPos(0,354);
        else
            warrior->setPos(0,368);

        slime = new Slime();
        slime->setPos(740, -20);
        scene->addItem(slime);

        scene->setBackgroundBrush(QBrush(QImage(":/images/wall2big")));

        delete entrance;

        floor++;
        ground->Ground::changeGround(floor);
    }
    if(b == 1)
    {
        delete slime;

        floor++;

        if(isitmage)
            mage->setPos(0, 354);
        else
            warrior->setPos(0,368);

        skeleton = new Skeleton();
        skeleton->setPos(800, 370);
        scene->addItem(skeleton);

        ground->Ground::changeGround(floor);
    }
    if(b == 2)
    {
        floor++;

        scene->setBackgroundBrush(QBrush(QImage(":/images/bghell")));

        if(!skeletondied)
        {
            scene->removeItem(skeleton);
            delete skeleton;
        }

        if(isitmage)
            mage->setPos(0, 354);
        else
            warrior->setPos(0, 368);

        slime2 = new Slime();
        slime2->setPos(740, -20);
        scene->addItem(slime2);

        slime3 = new Slime();
        slime3->setPos(430, -20);
        scene->addItem(slime3);

        ground->Ground::changeGround(floor);
    }
    if(b == 3)
    {
        delete slime2;
        delete slime3;

        floor++;
        if(isitmage)
            mage->setPos(0, 354);
        else
            warrior->setPos(0, 368);

        demon = new Demon();
        demon->setPos(860, 220);
        scene->addItem(demon);
    }
    if(b == 4 and demondied)
    {
        floor++;
        if(isitmage)
            mage->setPos(0, 354);
        else
            warrior->setPos(0, 368);

        scene->setBackgroundBrush(QBrush(QImage(":/images/bgfinalbig")));

        chest = new Chest();
        chest->setPos(540, 420);
        chest->setZValue(-1);
        scene->addItem(chest);

        ground->Ground::changeGround(floor);
    }
}

void Game::Rectangle(int x, int y, int width, int height, QColor color, double opacity)
{
    QGraphicsRectItem* panel = new QGraphicsRectItem(x,y,width,height);
    QBrush brush;

    brush.setStyle(Qt::SolidPattern);
    brush.setColor(color);

    panel->setBrush(brush);
    panel->setOpacity(opacity);
    panel->setZValue(1);

    scene->addItem(panel);
}

void Game::endgame(int a)
{
    QString message;

    if(a == 0)
    {
        message = "you died";
    }
    else
    {
        message = "the end";
    }
    displayEndGamewindow(message);
}

void Game::displayEndGamewindow(QString w)
{
    for(int i = 0, n = scene->items().size(); i < n; i++)
    {
        scene->items()[i]->setEnabled(false);
    }

    if(w == "you died")
    {
        Rectangle(0,0,1280,720,Qt::black,0.65);
        Rectangle(0, 200, 1280, 300, Qt::black, 0.75);
    }
    else
    {
        Rectangle(0,0,1280,720,Qt::white,0.65);
        Rectangle(0, 200, 1280, 300, Qt::white, 0.75);
    }

    QGraphicsTextItem * whathappened = new QGraphicsTextItem(w);
    whathappened->setFont(QFont("calligraphr",55));
    whathappened->setDefaultTextColor(Qt::darkRed);
    whathappened->setPos(450, 275);
    whathappened->setZValue(3);
    scene->addItem(whathappened);

    QTimer::singleShot(5000, this, SLOT(close()));
}
