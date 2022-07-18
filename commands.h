#ifndef COMMANDS_H
#define COMMANDS_H

#include <QDialog>

namespace Ui {
class commands;
}

class commands : public QDialog
{
    Q_OBJECT

public:
    explicit commands(QWidget *parent = nullptr);
    ~commands();

private:
    Ui::commands *ui;
};

#endif // COMMANDS_H
