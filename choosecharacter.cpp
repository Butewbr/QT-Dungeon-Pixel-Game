#include "choosecharacter.h"
#include "ui_choosecharacter.h"
#include "game.h"

Game * game;

ChooseCharacter::ChooseCharacter(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChooseCharacter)
{
    ui->setupUi(this);
    ui->carbunis->setPixmap(QPixmap(":/images/bigcarbunis.png"));
    ui->obiunam->setPixmap(QPixmap(":/images/bigobiunam.png"));
    ui->background->setPixmap(QPixmap(":/images/background.gif"));
}

ChooseCharacter::~ChooseCharacter()
{
    delete ui;
}

void ChooseCharacter::on_choosecarb_clicked()
{
    close();
    game = new Game(1);
    game->show();
}

void ChooseCharacter::on_chooseob_clicked()
{
    close();
    game = new Game(2);
    game->show();
}
