#include "commands.h"
#include "ui_commands.h"

commands::commands(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::commands)
{
    ui->setupUi(this);
    ui->left->setPixmap(QPixmap(":/images/keyleft"));
    ui->right->setPixmap(QPixmap(":/images/keyright"));
    ui->up->setPixmap(QPixmap(":/images/keyup"));
    ui->attack->setPixmap(QPixmap(":/images/keyz"));
    ui->specialattack->setPixmap(QPixmap(":/images/keyx"));
    ui->bg->setPixmap(QPixmap(":/images/backgroundoutsidewithcloudsbig"));
}

commands::~commands()
{
    delete ui;
}
