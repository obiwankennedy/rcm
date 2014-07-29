#include "tableswizard.h"
#include "ui_tableswizard.h"

TablesWizard::TablesWizard(QWidget *parent) :
    QWizard(parent),
    ui(new Ui::TablesWizard)
{
    ui->setupUi(this);
    connect(this,SIGNAL(currentIdChanged(int)),this,SLOT(currentPageChanged(int)));
}

TablesWizard::~TablesWizard()
{
    delete ui;
}


void TablesWizard::currentPageChanged(int i)
{
    switch(i)
    {
    case 0:
        manageRoomPage();
        break;
    case 1:
        manageTableInRooms();
        break;
    case 2:
        managePersonPerTable();
        break;
    }
}


void TablesWizard::manageRoomPage()
{
    m_roomCount = ui->m_roomCountSpin->value();

}
void TablesWizard::manageTableInRooms()
{

}

void TablesWizard::managePersonPerTable()
{

}
