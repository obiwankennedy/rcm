#include "gamedialog.h"
#include "ui_gamedialog.h"

GameDialog::GameDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GameDialog)
{
    ui->setupUi(this);
}

GameDialog::~GameDialog()
{
    delete ui;
}

QString GameDialog::getTitle()
{
    return ui->m_titleEdit->text();
}

QString GameDialog::getPunchLine()
{
    return ui->m_punchLineEdit->text();
}

QString GameDialog::getDescription()
{
    return ui->m_descriptionEdit->toPlainText();
}


