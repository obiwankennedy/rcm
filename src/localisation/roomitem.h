#ifndef ROOMITEM_H
#define ROOMITEM_H

#include <QGraphicsItem>

class RoomItem : public QGraphicsItem
{
public:
    RoomItem();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,QWidget *widget);
    void setSize(int w, int h);
    void setName(QString str);
private:
    QString m_id;
    int m_roomCount;
    int m_tableCount;
    int m_w;
    int m_h;
};

#endif // ROOMITEM_H
