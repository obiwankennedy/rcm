#include "tableswizard.h"
#include <QTime>
#include <QDebug>
#include <QJsonObject>

#include "ui_eventproperties.h"

TablesWizard::TablesWizard(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EventProperties)
{
    ui->setupUi(this);
    connect(ui->m_dayCount,SIGNAL(valueChanged(int)),this, SLOT(numberOfDayChanged()));
    connect(ui->m_tableCount,SIGNAL(valueChanged(int)),this,SLOT(tableCountChanged()));

    ui->m_tableName->setEditTriggers(QAbstractItemView::DoubleClicked);
    ui->m_tableName->setAlternatingRowColors(true);
}

TablesWizard::~TablesWizard()
{
    delete ui;
}
QList<EventDay *> *TablesWizard::getSchedule()
{
    QList<EventDay*>* result = new QList<EventDay*>();

    int day = ui->m_dayCount->value();

    for(auto key : m_editors.keys())
    {
        auto value = m_editors.value(key);

        auto time = key->time();
        value->setData(Qt::DisplayRole,time);
    }

    for(int i = 0; i < day ; ++i)
    {
        auto itemStart = ui->tableWidget->item(i,0);
        auto itemEnd = ui->tableWidget->item(i,1);

        auto event = new EventDay();
        event->setId(i);
        QTime time1 = itemStart->data(Qt::DisplayRole).toTime();
        int time1Min = time1.minute()+time1.hour()*60;
        event->setStartTime(time1Min);

        QTime time2 = itemEnd->data(Qt::DisplayRole).toTime();
        int time2Min = time2.minute()+time2.hour()*60;
        event->setEndTime(time2Min);

        result->append(event);
    }


    return result;
}

int TablesWizard::getTableCount() const
{
    return ui->m_tableCount->value();
}

QStringList TablesWizard::getNameTable()
{
    QStringList data;

    for(int i = 0; i < ui->m_tableName->count();++i)
    {
        auto item = ui->m_tableName->item(i);
        data << item->data(Qt::DisplayRole).toString();
    }
    return data;
}

#include <QHeaderView>
void TablesWizard::numberOfDayChanged()
{
    int day = ui->m_dayCount->value();
    m_editors.clear();
    ui->tableWidget->clear();
    ui->tableWidget->setRowCount(0);
    ui->tableWidget->setColumnCount(0);
    ui->tableWidget->clearContents();
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

        QTime time(8,0);
        QTime time2(20,0);
        auto timeEdit = new QTimeEdit(time);
        auto timeEdit2 = new QTimeEdit(time2);

        m_editors.insert(timeEdit,start);
        m_editors.insert(timeEdit2,end);
        ui->tableWidget->setCellWidget(i,0,timeEdit);
        ui->tableWidget->setCellWidget(i,1,timeEdit2);

        start->setFlags(Qt::ItemIsEnabled | Qt::ItemIsEditable | Qt::ItemIsSelectable);
        end->setFlags(Qt::ItemIsEnabled | Qt::ItemIsEditable | Qt::ItemIsSelectable);
    }
}

void TablesWizard::tableCountChanged()
{
    int tableCount = ui->m_tableCount->value();
    ui->m_tableName->clear();
    QStringList names;


    for(int i = 0 ; i < tableCount ; i++)
    {
        names << QString("");
    }

    ui->m_tableName->addItems(names);

    for(int i = 0; i < ui->m_tableName->count();++i)
    {
        auto item = ui->m_tableName->item(i);
        item->setFlags(item->flags() | Qt::ItemIsEditable);
    }


}
//////////////////////////////////////////
/// \brief EventDay::getStartTime
/// \return
/////////////////////////////////////////*
EventDay::EventDay()
{

}
EventDay::EventDay(EventDay* day)
{
    m_startTime = day->getStartTime();
    m_id = day->getId();
    m_endTime = day->getEndTime();
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

int EventDay::getDuration()
{
    return (m_endTime - m_startTime);
}

int EventDay::getId() const
{
    return m_id;
}

void EventDay::setId(int id)
{
    m_id = id;
}

void EventDay::readFromData(QDataStream &)
{

}

void EventDay::writeToData(QDataStream &) const
{

}

void EventDay::writeDataToJson(QJsonObject & obj)
{
    obj["id"]=m_id;
    obj["endTime"]=m_endTime;
    obj["startTime"]=m_startTime;
}

void EventDay::readDataFromJson(QJsonObject & obj)
{
    m_id = obj["id"].toInt();
    m_endTime = obj["endTime"].toInt();
    m_startTime = obj["startTime"].toInt();
}

QDomElement EventDay::writeDataToXml(QDomDocument &)
{

}

void EventDay::readDataFromXml(QDomNode &)
{

}

