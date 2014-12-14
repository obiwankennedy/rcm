#include "playerinformationformdialog.h"
#include "ui_playerinformationformdialog.h"

PlayerInformationFormDialog::PlayerInformationFormDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PlayerInformationFormDialog)
{
    ui->setupUi(this);
}

PlayerInformationFormDialog::~PlayerInformationFormDialog()
{
    delete ui;
}
