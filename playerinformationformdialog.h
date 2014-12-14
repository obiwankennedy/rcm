#ifndef PLAYERINFORMATIONFORMDIALOG_H
#define PLAYERINFORMATIONFORMDIALOG_H

#include <QDialog>

namespace Ui {
class PlayerInformationFormDialog;
}

class PlayerInformationFormDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PlayerInformationFormDialog(QWidget *parent = 0);
    ~PlayerInformationFormDialog();

private:
    Ui::PlayerInformationFormDialog *ui;
};

#endif // PLAYERINFORMATIONFORMDIALOG_H
