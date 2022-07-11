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

QString PlayerInformationFormDialog::name() const
{
    return ui->m_nameEdit->text();
}
QString PlayerInformationFormDialog::firstName() const
{
    return ui->m_firstNameEdit->text();
}
QString PlayerInformationFormDialog::phone() const
{
    return ui->m_phoneEdit->text();
}
int PlayerInformationFormDialog::getPlayerCount() const
{
    return ui->m_playerCount->value();
}
