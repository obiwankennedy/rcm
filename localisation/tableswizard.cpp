#include "tableswizard.h"
#include "ui_tableswizard.h"

#include <QDebug>
TablesWizard::TablesWizard(QWidget *parent) :
    QWizard(parent),
    ui(new Ui::TablesWizard)
{
    ui->setupUi(this);


    connect(ui->m_roomCountSpin,SIGNAL(valueChanged(int)),this,SLOT(currentRoomCount(int)));

    ui->m_roomCountSpin->setKeyboardTracking(true);


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

        break;
    case 1:
        manageRoomPage();
        break;
    case 2:
        manageTableInRooms();
        break;
    }
}


void TablesWizard::manageRoomPage()
{
     ui->m_roomCountSpin->clearFocus();
     m_roomCount = ui->m_roomCountSpin->value();
     m_modelRoom = new RoomModel(m_roomCount);
     ui->m_roomTableView->setModel();


}
void TablesWizard::manageTableInRooms()
{
    QMap<QSting,int> data = m_modelRoom->getDataMap();
}

void TablesWizard::currentRoomCount(int a)
{
    m_roomCount = a;
}
