#ifndef TABLEITEM_H
#define TABLEITEM_H

#include <QGraphicsObject>
#include "table.h"
#include "scenario.h"
#include "tableswizard.h"

class TableItem : public QGraphicsObject
{
    Q_OBJECT
public:
    explicit TableItem();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);



    EventDay* day() const;
    void setDay(EventDay* day);

    int idTable() const;
    void setIdTable(int idTable);

    int tableCount() const;
    void setTableCount(int tableCount);

signals:
    void heightChanged(qreal );
    void minuteWidthChanged(qreal );

private:
    QList<Scenario*> m_scenarioList;
    EventDay* m_day;
    int m_idTable;
    int m_tableCount;
};

#endif // TABLEITEM_H
