#include "scenarioitem.h"
#include <QPainter>

ScenarioItem::ScenarioItem()
{

}

QRectF ScenarioItem::boundingRect() const
{
    return QRectF(0,0,(*m_minutesInPixel)*m_data->getDuration(),*m_tableInPixel);
}

void ScenarioItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QRectF rect = boundingRect();

    painter->fillRect(rect,Qt::white);

    painter->setPen(Qt::black);
    painter->drawRect(rect);

    painter->drawText(rect.center().x(),rect.topLeft().y(),m_data->getTitle());
    painter->drawText(rect.center(),m_data->getTitle());


    painter->drawText(rect.bottomRight(),QString("%1/%2").arg(m_data->getCurrentPlayers(),m_data->getMaximumPlayers()));




}

int *ScenarioItem::minutesInPixel() const
{
    return m_minutesInPixel;
}

void ScenarioItem::setMinutesInPixel(int *minutesInPixel)
{
    m_minutesInPixel = minutesInPixel;
}

Scenario *ScenarioItem::data() const
{
    return m_data;
}

void ScenarioItem::setData(Scenario *data)
{
    m_data = data;
}
