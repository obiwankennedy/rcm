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
     ui->m_roomTableView->setModel(m_modelRoom);
}
void TablesWizard::manageTableInRooms()
{
    QMap<QString,int>* data = m_modelRoom->getDataMap();

    m_modelTable = new TableModel(data);

    ui->m_tablePersonView->setModel(m_modelTable);
}

void TablesWizard::currentRoomCount(int a)
{
    m_roomCount = a;
}
QList<Table*>* TablesWizard::getData()
{
    return m_modelTable->getDataList();
}
int TablesWizard::getRoomCount() const
{
    return m_roomCount;
}
