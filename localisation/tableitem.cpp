#include "tableitem.h"
#include <QPainter>
#include <QDebug>
#include <QGraphicsScene>
#include <QPen>
#include <QJsonObject>
#include <QJsonArray>

TableItem::TableItem()
 :  QGraphicsObject(),m_day(nullptr)
{
    m_idTable =1;
}

TableItem::~TableItem()
{
    if(nullptr != m_day)
    {
        delete m_day;
    }
}
QRectF TableItem::boundingRect() const
{
    qreal width = scene()->width();
    qreal height = scene()->height()/m_tableCount;

    return QRectF(0,0,width,height);
}

void TableItem::paint(QPainter *painter, const QStyleOptionGraphicsItem */*option*/, QWidget */*widget*/)
{
    qreal width = scene()->width();
    qreal height = scene()->height()/m_tableCount;
    int duration = m_day->getDuration();
    int startHour = m_day->getStartTime()/60;

    QPen pen = painter->pen();
    if(duration!=0)
    {
        qreal fiveMinutes = 5*width/duration;
        qreal marginY = 0.2*(height);
        qreal marginY2 = 0.8*(height);

        emit heightChanged(marginY2-marginY);
        emit minuteWidthChanged(width/duration);

        if(m_name.isEmpty())
        {
            painter->drawText(0,marginY,tr("J%2:Table #%1").arg(m_idTable+1).arg(m_day->getId()+1));
        }
        else
        {
            painter->drawText(0,marginY,tr("J%2:Table %1").arg(m_name).arg(m_day->getId()+1));
        }
        painter->drawLine(0,marginY,width,marginY);
        painter->drawLine(0,marginY2,width,marginY2);

        int j = 0;
        int h = 0;
        for(int i = 0; i < width; i += fiveMinutes)
        {
            pen.setWidth(1);
            pen.setColor(Qt::black);
            painter->setPen(pen);
            painter->drawLine(i,marginY,i,marginY2);

            if(j%3 == 0)
            {
                pen.setWidth(2);
                pen.setColor(Qt::green);
                painter->setPen(pen);
                painter->drawLine(i,marginY,i,marginY2);
            }
            if(j%6 == 0)
            {
                pen.setWidth(3);
                pen.setColor(Qt::blue);
                painter->setPen(pen);
                painter->drawLine(i,marginY,i,marginY2);
            }
            if(j%12 == 0)
            {
                pen.setWidth(4);
                pen.setColor(Qt::red);
                painter->setPen(pen);
                painter->drawLine(i,marginY,i,marginY2);
                pen.setWidth(1);
                painter->drawText(i,height,tr("%1h").arg(startHour+h));
                h++;
            }
            j++;
        }

    }
}

EventDay *TableItem::day() const
{
    return m_day;
}

void TableItem::setDay(EventDay *day)
{
    if(nullptr != m_day)
    {
        delete m_day;
        m_day = nullptr;
    }
    m_day = new EventDay(day);
}

int TableItem::idTable() const
{
    return m_idTable;
}

void TableItem::setIdTable(int idTable)
{
    m_idTable = idTable;
}

int TableItem::tableCount() const
{
    return m_tableCount;
}

void TableItem::setTableCount(int tableCount)
{
    m_tableCount = tableCount;
}

QString TableItem::name() const
{
    return m_name;
}

void TableItem::setName(const QString &name)
{
    m_name = name;
}

void TableItem::readFromData(QDataStream &)
{

}

void TableItem::writeToData(QDataStream &) const
{

}

QDomElement TableItem::writeDataToXml(QDomDocument &)
{

}

void TableItem::readDataFromXml(QDomNode &)
{

}

void TableItem::readDataFromJson(QJsonObject & obj)
{
    qreal x = obj["x"].toDouble();
    qreal y = obj["y"].toDouble();
    setPos(x,y);
    m_idTable= obj["idTable"].toInt();
    m_tableCount= obj["tableCount"].toInt();
    m_name= obj["name"].toString();

    QJsonObject dayJson = obj["day"].toObject();
    m_day = new EventDay();
    m_day->readDataFromJson(dayJson);

    QJsonArray array = obj["scenarios"].toArray();
    QJsonArray::Iterator it;
    for(it = array.begin(); it != array.end(); ++it)
    {
         QJsonObject obj = (*it).toObject();
         Scenario* sce = new Scenario();
         sce->readDataFromJson(obj);
         m_scenarioList.append(sce);
    }

}

void TableItem::writeDataToJson(QJsonObject & obj)
{
    QPointF posi = pos();
    obj["x"]=posi.x();
    obj["y"]=posi.y();
    obj["idTable"]=m_idTable;
    obj["tableCount"]=m_tableCount;
    obj["name"]=m_name;

    QJsonObject dayJson;
    m_day->writeDataToJson(dayJson);
    obj["day"]=dayJson;

    QJsonArray array;
    for(auto sce : m_scenarioList)
    {
        QJsonObject sceJson;
        sce->writeDataToJson(sceJson);
        array.append(sceJson);
    }
    obj["scenarios"]=array;

}

