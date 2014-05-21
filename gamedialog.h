#ifndef ADDGAMEDIALOG_H
#define ADDGAMEDIALOG_H

#include <QDialog>

namespace Ui {
class GameDialog;
}

class GameDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit GameDialog(QWidget *parent = 0);
    ~GameDialog();

    QString getTitle();
    QString getPunchLine();
    QString getDescription();


    
private:
    Ui::GameDialog *ui;
};

#endif // ADDGAMEDIALOG_H
