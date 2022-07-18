#ifndef CHOOSECHARACTER_H
#define CHOOSECHARACTER_H

#include <QDialog>

namespace Ui {
class ChooseCharacter;
}

class ChooseCharacter : public QDialog
{
    Q_OBJECT

public:
    explicit ChooseCharacter(QWidget *parent = nullptr);
    ~ChooseCharacter();

private slots:
    void on_choosecarb_clicked();

    void on_chooseob_clicked();

private:
    Ui::ChooseCharacter *ui;
};

#endif // CHOOSECHARACTER_H
