#include "roomitem.h"
#include <QPainter>
#include <QDebug>

#define RADIUS 10
RoomItem::RoomItem()
{
    m_w=800;
    m_h=400;
}
QRectF RoomItem::boundingRect() const
{
    return QRectF(0,0,m_w,m_h);
}

void RoomItem::paint(QPainter *painter, const QStyleOptionGraphicsItem */*option*/,QWidget */*widget*/)
{
    painter->drawRoundedRect(boundingRect(),RADIUS,RADIUS);
    painter->drawText(RADIUS,RADIUS,m_id);
}
void RoomItem::setSize(int w, int h)
{
    m_w=w;
    m_h=h;
}
void RoomItem::setName(QString str)
{
    m_id = str;
}
