#include "playersinformationdialog.h"
#include "ui_playersinformationdialog.h"

PlayersInformationDialog::PlayersInformationDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PlayersInformationDialog)
{
    ui->setupUi(this);
}

PlayersInformationDialog::~PlayersInformationDialog()
{
    delete ui;
}
