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
    explicit PlayerInformationFormDialog(QWidget *parent = nullptr);
    ~PlayerInformationFormDialog();

    //QString getInfo();
    QString name() const;
    QString firstName() const;
    QString phone() const;
    int getPlayerCount() const;

private:
    Ui::PlayerInformationFormDialog *ui;
};

#endif // PLAYERINFORMATIONFORMDIALOG_H
