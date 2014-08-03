#ifndef ROOMITEM_H
#define ROOMITEM_H

#include <QGraphicsItem>

class RoomItem : public QGraphicsItem
{
public:
    RoomItem();

private:
    QString m_id;
    int m_roomCount;
    int m_tableCount;
};

#endif // ROOMITEM_H
