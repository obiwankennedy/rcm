#include "roomitem.h"
#include <QPainter>

RoomItem::RoomItem()
{
}
QRectF RoomItem::boundingRect() const
{
    return QRectF(0,0,400,800);
}

void RoomItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,QWidget *widget)
{
    painter->drawRoundedRect(-10, -10, 20, 20, 5, 5);
}
