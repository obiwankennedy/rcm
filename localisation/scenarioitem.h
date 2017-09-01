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

    int* minutesInPixel() const;
    void setMinutesInPixel(int* minutesInPixel);

    Scenario* data() const;
    void setData(Scenario* data);

private:
    Scenario* m_data;
    int* m_minutesInPixel;
    int* m_tableInPixel;
};

#endif // SCENARIOITEM_H
