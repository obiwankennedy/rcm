#include "tableitem.h"
#include <QPainter>
#include <QDebug>
#include <QGraphicsScene>
#include <QPen>

TableItem::TableItem()
 :  QGraphicsObject(),m_day(nullptr)
{
    m_idTable =1;
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


        painter->drawText(0,marginY,tr("J%2:Table #%1").arg(m_idTable+1).arg(m_day->getId()+1));
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
    m_day = day;
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

