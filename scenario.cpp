#include "scenario.h"

Scenario::Scenario()
    : m_scenarioId(QUuid().toString()),m_duration(60),m_level(BEGINNER),m_maximumPlayers(6),m_minimumPlayers(2)
{

}
void Scenario::setGameId(QString id)
{
    m_gameId = id;
}

void Scenario::setGameMasterId(QString id)
{
    m_gameMasterId = id;
}

void Scenario::setDuration(quint64 id)
{
    m_duration = id;
}

void Scenario::setTableNumber(quint32 number)
{
    m_tableNumber = number;
}

void Scenario::setDateTime(QDateTime time)
{
    m_startTime = time;
}


QString Scenario::getGameId()
{
    return m_gameId;
}

QString Scenario::getGameMasterId()
{
return m_gameMasterId;
}

quint64 Scenario::getDuration()
{
    return m_duration;
}

quint32 Scenario::getTableNumber()
{
    return m_tableNumber;
}

QDateTime Scenario::getDateTime()
{
    return m_startTime;
}
Scenario::LEVEL  Scenario::getLevel() const
{
    return m_level;
}
quint64  Scenario::getDuration() const
{
    return m_duration;

}
quint32  Scenario::getMaximumPlayers() const
{
    return m_maximumPlayers;
}
quint32  Scenario::getMinimumPlayers() const
{
    return m_minimumPlayers;
}


void Scenario::setMaximumPlayer(quint32 m)
{
    m_maximumPlayers = m;
}

void Scenario::setMinimumPlayer(quint32 m)
{
    m_minimumPlayers = m;
}
void Scenario::setLevel(Scenario::LEVEL lvl)
{
    m_level = lvl;
}
QString Scenario::getTitle()
{
    return m_title;
}

void Scenario::readFromData(QDataStream& from)
{
    int i;
    from >> m_gameId;
    from >> m_title;
    from >> m_gameMasterId;
    from >> m_scenarioId;
    from >> m_duration;
    from >> m_tableNumber;
    from >>i;
    m_level=(Scenario::LEVEL)i;
    from >> m_startTime;
    from >> m_maximumPlayers;
    from >> m_minimumPlayers;
    from >> m_currentPlayers;
    from >> m_description;

    from >> i;
    m_state=(Scenario::STATE)i;
}

void Scenario::writeToData(QDataStream& to)
{
    to << m_gameId;
    to << m_title;
    to << m_gameMasterId;
    to << m_scenarioId;
    to << m_duration;
    to << m_tableNumber;
    to << m_level;
    to << m_startTime;
    to << m_maximumPlayers;
    to << m_minimumPlayers;
    to << m_currentPlayers;
    to << m_state;
}
QString Scenario::getDescription()
{
    return m_description;
}
void Scenario::setTitle(QString m)
{
    m_title = m;
}
void Scenario::setDescription(QString m)
{
    m_description = m;
}
