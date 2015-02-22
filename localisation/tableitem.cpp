#include "tableitem.h"
#include <QPainter>
#include <QDebug>

TableItem::TableItem() :
    QGraphicsItem(),m_table(NULL)
{
    m_w=16;
    m_h=16;
}
QRectF TableItem::boundingRect() const
{
    return QRectF(0,0,m_w,m_h);
}
void TableItem::paint(QPainter *painter, const QStyleOptionGraphicsItem */*option*/, QWidget */*widget*/)
{
    painter->fillRect(boundingRect(),Qt::red);
    if(NULL!=m_table)
    {
        painter->drawText(boundingRect(),Qt::AlignCenter,QString("%1").arg(m_table->getId()));
    }
}
void TableItem::setSize(int w,int h)
{
    m_w=w;
    m_h=h;
   // qDebug() << "TableItem size:" <<m_h << m_w;
}
void TableItem::setTable(Table* table)
{
    m_table= table;
}
