#ifndef SCENARIOITEM_H
#define SCENARIOITEM_H

#include <QGraphicsObject>

#include "scenario.h"

class ScenarioItem : public QGraphicsObject
{
public:
    explicit ScenarioItem();

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    qreal* minutesInPixel() const;
    void setMinutesInPixel(qreal* minutesInPixel);

    Scenario* data() const;
    void setData(Scenario* data);

    qreal *tableInPixel() const;
    void setTableInPixel(qreal *tableInPixel);

private:
    Scenario* m_data;
    qreal* m_minutesInPixel;
    qreal* m_tableInPixel;
};

#endif // SCENARIOITEM_H
