#ifndef TABLEITEM_H
#define TABLEITEM_H

#include <QGraphicsItem>
#include "table.h"

class TableItem : public QGraphicsItem
{

public:
    explicit TableItem();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void setSize(int,int);

    void setTable(Table*);

signals:

public slots:
private:
    int m_w;
    int m_h;
    Table* m_table;
};

#endif // TABLEITEM_H
