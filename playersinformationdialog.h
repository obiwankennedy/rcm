#ifndef PLAYERSINFORMATIONDIALOG_H
#define PLAYERSINFORMATIONDIALOG_H

#include <QDialog>

namespace Ui {
class PlayersInformationDialog;
}

class PlayersInformationDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PlayersInformationDialog(QWidget *parent = 0);
    ~PlayersInformationDialog();

private:
    Ui::PlayersInformationDialog *ui;
};

#endif // PLAYERSINFORMATIONDIALOG_H
