#include "tableswizard.h"
#include "ui_eventproperties.h"

#include <QDebug>
TablesWizard::TablesWizard(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EventProperties)
{
    ui->setupUi(this);
    connect(ui->m_dayCount,SIGNAL(valueChanged(int)),this, SLOT(numberOfDayChanged()));
}

TablesWizard::~TablesWizard()
{
    delete ui;
}
QList<EventDay *> *TablesWizard::getSchedule()
{

}

int TablesWizard::getTableCount() const
{
    return ui->m_tableCount->value();
}
#include <QTimeEdit>
#include <QHeaderView>
void TablesWizard::numberOfDayChanged()
{
    int day = ui->m_dayCount->value();
    ui->tableWidget->clear();
    ui->tableWidget->insertColumn(0);
    ui->tableWidget->insertColumn(1);
    QStringList header;
    header << tr("Start Time") << tr("End Time");
    ui->tableWidget->setHorizontalHeaderLabels(header);
    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);
    for(int i = 0; i < day; i++)
    {
        ui->tableWidget->insertRow(i);
        QTableWidgetItem* start = new QTableWidgetItem();
        QTableWidgetItem* end = new QTableWidgetItem();

        ui->tableWidget->setItem(i,0,start);
        ui->tableWidget->setItem(i,1,end);

        ui->tableWidget->setCellWidget(i,0,new QTimeEdit());
        ui->tableWidget->setCellWidget(i,1,new QTimeEdit());

        start->setFlags(Qt::ItemIsEnabled | Qt::ItemIsEditable | Qt::ItemIsSelectable);
        end->setFlags(Qt::ItemIsEnabled | Qt::ItemIsEditable | Qt::ItemIsSelectable);
    }
}

int EventDay::getStartTime() const
{
    return m_startTime;
}

void EventDay::setStartTime(int startTime)
{
    m_startTime = startTime;
}

int EventDay::getEndTime() const
{
    return m_endTime;
}

void EventDay::setEndTime(int endTime)
{
    m_endTime = endTime;
}

int EventDay::getId() const
{
    return m_id;
}

void EventDay::setId(int id)
{
    m_id = id;
}

