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
QString PlayerInformationFormDialog::getInfo()
{
    QString result;
    result=tr("%1;%2;%3").arg(ui->m_firstNameEdit->text()).arg(ui->m_nameEdit->text()).arg(ui->m_phoneEdit->text());
    return result;
}
int PlayerInformationFormDialog::getPlayerCount()
{
    return ui->m_playerCount->value();
}
