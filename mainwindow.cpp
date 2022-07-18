#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "choosecharacter.h"
#include "commands.h"
#include <QDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->floor->setPixmap(QPixmap(":/images/mainmenubg.png"));
    ui->startbg->setPixmap(QPixmap(":/images/startgamebutton.png"));
    ui->quitbg->setPixmap(QPixmap(":/images/quit.png"));
    ui->controlsbg->setPixmap(QPixmap(":/images/controls"));
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_quit_clicked()
{
    close();
}

void MainWindow::on_startbutton_clicked()
{
    close();
    ChooseCharacter window;
    window.setModal(true);
    window.exec();
}

void MainWindow::on_controls_clicked()
{
    commands commandswindow;
    commandswindow.setModal(true);
    commandswindow.exec();
}
