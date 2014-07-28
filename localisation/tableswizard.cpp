#include "tableswizard.h"
#include "ui_tableswizard.h"

TablesWizard::TablesWizard(QWidget *parent) :
    QWizard(parent),
    ui(new Ui::TablesWizard)
{
    ui->setupUi(this);
}

TablesWizard::~TablesWizard()
{
    delete ui;
}
