#include "scenarioitem.h"
#include <QPainter>


#include <QGraphicsPixmapItem>

ScenarioItem::ScenarioItem()
{
    m_lockUp = false;
    scheduleGame();
    setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemSendsGeometryChanges);

    m_idTranslator = IdTranslator::getInstance();



    m_locker = new QGraphicsPixmapItem(this);

    m_locker->setPixmap(QPixmap(":/resources/cadenas_open.png"));




}

QRectF ScenarioItem::boundingRect() const
{

    return QRectF(0,0,(*m_minutesInPixel)*m_data->getDuration(),*m_tableInPixel);
}
#include <QStyleOptionGraphicsItem>
void ScenarioItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QRectF rect = boundingRect();

    if(nullptr != m_idTranslator)
    {

        Game* game = m_idTranslator->getGameById(m_data->getGameId());
        GameMaster* master = m_idTranslator->getGameMasterById(m_data->getGameMasterId());

        if(nullptr != master)
        {
            QColor color = master->getColor();
            if(Done==m_state)
            {
                color = QColor(80,80,80);
            }


            painter->fillRect(rect,color);
        }
        m_locker->setPos(rect.right()*0.8,rect.center().y()-m_locker->boundingRect().height()/2);

        painter->setPen(Qt::black);
        painter->drawRect(rect);

        if(option->state & QStyle::State_Selected )
        {
            painter->save();
            painter->setPen(Qt::red);
            painter->drawRect(rect);
            painter->restore();
        }


        if((game != nullptr)&&(nullptr != master))
        {
            painter->drawText(rect.center().x(),rect.topLeft().y(),m_data->getTitle());
            painter->drawText(0,rect.center().y(),game->getTitle());
            painter->drawText(rect,Qt::AlignTop | Qt::AlignLeft,tr("GM: %1 - tel: %2").arg(master->getNickName()).arg(master->getPhoneNumber()));
            painter->drawText(rect,Qt::AlignBottom | Qt::AlignRight,QString("%1 min").arg(m_data->getDuration()));
            painter->drawText(0,rect.bottom(),QString("%1/%2").arg(m_data->getCurrentPlayers()).arg(m_data->getMaximumPlayers()));
            painter->drawText(rect.topRight(),tr("State: %1").arg(stateToString()));

        }
    }

}
#include "localisationview.h"
QVariant ScenarioItem::itemChange(GraphicsItemChange change, const QVariant &value)
{

    if (change == ItemPositionChange )
    {

        auto schedule = dynamic_cast<Schedules*>(scene());

        QPointF newPos = schedule->computeClosePoint(value.toPointF());
        if(newPos != value.toPointF())
        {
            return newPos;
        }
    }

    return QGraphicsItem::itemChange(change, value);
}

void ScenarioItem::readFromData(QDataStream &)
{

}

void ScenarioItem::writeToData(QDataStream & in) const
{
    in << m_color;
    in << m_state;
    m_data->writeToData(in);

}

void ScenarioItem::readDataToJson(QJsonObject &)
{

}

void ScenarioItem::writeDataToJson(QJsonObject &)
{

}

QDomElement ScenarioItem::writeDataToXml(QDomDocument &)
{

}

void ScenarioItem::readDataFromXml(QDomNode &)
{

}
QString ScenarioItem::stateToString()
{
    switch(m_state)
    {
    case Done:
        return QStringLiteral("Done");
    case Running:
        return QStringLiteral("Running");
    case Scheduled:
        return QStringLiteral("Scheduled");
    }
    return "";
}

void ScenarioItem::startGame()
{
    m_state = Running;
    update();
}

void ScenarioItem::endGame()
{
    m_state = Done;
    update();
}

void ScenarioItem::scheduleGame()
{
    m_state = Scheduled;
    update();
}

void ScenarioItem::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    if(event->button() == Qt::LeftButton)
    {
        auto children = childItems();
        QPointF position = event->scenePos();
        for(auto child : children)
        {
            QPointF newPos = child->mapFromScene(position);
            if(child->contains(newPos))
            {
                if(child == m_locker)
                {
                    m_lockUp=!m_lockUp;
                    if(m_lockUp)
                    {
                        m_locker->setPixmap(QPixmap(":/resources/cadenas_closed.png"));
                        setFlags( QGraphicsItem::ItemIsSelectable);
                        update();
                    }
                    else
                    {
                        m_locker->setPixmap(QPixmap(":/resources/cadenas_open.png"));
                        setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemSendsGeometryChanges);
                        update();
                    }
                }
            }
        }
    }
}
qreal *ScenarioItem::minutesInPixel() const
{
    return m_minutesInPixel;
}
#include <QDebug>
void ScenarioItem::setMinutesInPixel(qreal* minutesInPixel)
{
    qDebug() << "ScenarioItem minute in pixel"<< minutesInPixel;
    m_minutesInPixel = minutesInPixel;
    update();
}

Scenario *ScenarioItem::data() const
{
    return m_data;
}

void ScenarioItem::setData(Scenario *data)
{
    m_data = data;
}

qreal *ScenarioItem::tableInPixel() const
{
    return m_tableInPixel;
}

void ScenarioItem::setTableInPixel(qreal *tableInPixel)
{
    m_tableInPixel = tableInPixel;
    update();
}
