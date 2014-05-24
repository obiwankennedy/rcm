/***************************************************************************
* Copyright (C) 2014 by Renaud Guezennec                                   *
* http://renaudguezennec.homelinux.org/accueil,3.html                      *
*                                                                          *
*  This file is part of rcm                                                *
*                                                                          *
* Rcm is free software; you can redistribute it and/or modify              *
* it under the terms of the GNU General Public License as published by     *
* the Free Software Foundation; either version 2 of the License, or        *
* (at your option) any later version.                                      *
*                                                                          *
* This program is distributed in the hope that it will be useful,          *
* but WITHOUT ANY WARRANTY; without even the implied warranty of           *
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the             *
* GNU General Public License for more details.                             *
*                                                                          *
* You should have received a copy of the GNU General Public License        *
* along with this program; if not, write to the                            *
* Free Software Foundation, Inc.,                                          *
* 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.                 *
***************************************************************************/
#include <QDataStream>
#include <QDateTime>
#include <QDebug>

#include "scenario.h"

Scenario::Scenario()
    : m_scenarioId(QUuid().toString()),m_duration(60),m_level(BEGINNER),m_maximumPlayers(6),m_minimumPlayers(2),m_currentPlayers(0)
{

}
void Scenario::setReferenceScenario(const Scenario* a)
{
    //m_scenarioId = a.getScenarioId();
    m_state = a->getState();
    m_duration = a->getDuration();
    m_description = a->getDescription();
    m_level = a->getLevel();
    m_gameId = a->getGameId();
    m_gameMasterId = a->getGameMasterId();
    m_maximumPlayers = a->getMaximumPlayers();
    m_minimumPlayers = a->getMinimumPlayers();
    m_title = a->getTitle();
}

Scenario::~Scenario()
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


QString Scenario::getGameId() const
{
    return m_gameId;
}

QString Scenario::getGameMasterId()const
{
    return m_gameMasterId;
}

quint64 Scenario::getDuration()const
{
    return m_duration;
}

quint32 Scenario::getTableNumber()const
{
    return m_tableNumber;
}

QDateTime Scenario::getDateTime()const
{
    return m_startTime;
}
Scenario::LEVEL  Scenario::getLevel() const
{
    return m_level;
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
QString Scenario::getTitle() const
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

void Scenario::writeToData(QDataStream& to) const
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
    to << m_description;
    to << m_state;
}
QString Scenario::getDescription() const
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
Scenario::STATE Scenario::getState() const
{
    return m_state;
}
void Scenario::setState(Scenario::STATE m)
{
    m_state=m;
    if(m_state==Scenario::RUNNING)
    {
        m_startTime = QDateTime::currentDateTime();
    }

}
QDataStream &operator>>(QDataStream &in, Scenario &myObj)
{
    myObj.readFromData(in);
    return in;
}

QDataStream &operator<<(QDataStream &out, const Scenario &myObj)
{
    myObj.writeToData(out);
    return out;
}
void Scenario::increaseCurrentPlayerCount(quint32 i)
{
    m_currentPlayers+=i;
}

void Scenario::decreaseCurrentPlayerCount(quint32 i)
{
    m_currentPlayers-=i;
}
quint32 Scenario::getCurrentPlayers() const
{
    return m_currentPlayers;
}
void Scenario::setCurrentPlayers(quint32 m)
{
    m_currentPlayers = m;
}
QString Scenario::getScenarioId() const
{
    return m_scenarioId;
}
void Scenario::setScenarioId(QString m)
{
    m_scenarioId = m;
}
quint32 Scenario::getRestingTime() const
{
    QDateTime now(QDateTime::currentDateTime());
    int seconds = m_startTime.secsTo(now);
    int min = m_duration-(seconds/60);

    return min < 0 ? 0 : min;
}
