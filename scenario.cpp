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
Scenario::STATE Scenario::getState() const
{
    return m_state;
}
void Scenario::setState(Scenario::STATE m)
{
    m_state=m;
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
