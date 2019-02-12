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
    : m_scenarioId(QUuid::createUuid().toString()),m_duration(60),m_level(BEGINNER),m_maximumPlayers(6),m_minimumPlayers(2),m_currentPlayers(0),m_tableNumber(0)
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
    m_startTime = a->getDateTime();
    m_currentPlayers = a->getCurrentPlayers();
    m_playerInformation = a->getPlayerInformation();
}
void Scenario::reset()
{
    m_currentPlayers = 0;
    m_startTime = QDateTime();
    m_state=Scenario::AVAILABLE;
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
    from >> m_playerInformation;

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
    to << m_playerInformation;
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
quint32 Scenario::getRestingTimeInSecond() const
{
    QDateTime now(QDateTime::currentDateTime());
    int seconds = m_startTime.secsTo(now);
    int min = m_duration*60-seconds;

    return min < 0 ? 0 : min;
}
QDomElement Scenario::writeDataToXml(QDomDocument& t)
{
    QDomDocument doc;
    QDomElement parent = doc.createElement("scenerio");
    QDomElement gameIdF = doc.createElement("gameId");
    gameIdF.appendChild(doc.createTextNode(m_gameId));

    QDomElement gameMasterIdF = doc.createElement("gameMasterId");
    gameMasterIdF.appendChild(doc.createTextNode(m_gameMasterId));

    QDomElement durationF = doc.createElement("duration");
    durationF.appendChild(doc.createTextNode(QString().setNum(m_duration)));

    QDomElement tableNumberF = doc.createElement("tableNumber");
    tableNumberF.appendChild(doc.createTextNode(QString().setNum(m_tableNumber)));

    QDomElement startTimeF = doc.createElement("startTime");
    startTimeF.appendChild(doc.createTextNode(m_startTime.toString("dd.MM.yyyy:hh:mm:ss")));
    qDebug() << "start time" << m_startTime << m_startTime.toString("dd.MM.yyyy:hh:mm:ss");

    QDomElement levelF = doc.createElement("level");
    levelF.appendChild(doc.createTextNode(QString().setNum(m_level)));

    QDomElement maxF = doc.createElement("maximumPlayers");
    maxF.appendChild(doc.createTextNode(QString().setNum(m_maximumPlayers)));

    QDomElement minF = doc.createElement("minimumPlayers");
    minF.appendChild(doc.createTextNode(QString().setNum(m_minimumPlayers)));

    QDomElement titleF = doc.createElement("title");
    titleF.appendChild(doc.createTextNode(m_title));

    QDomElement descriptionF = doc.createElement("description");
    descriptionF.appendChild(doc.createTextNode(m_description));

    QDomElement currentF = doc.createElement("currentPlayers");
    currentF.appendChild(doc.createTextNode(QString().setNum(m_currentPlayers)));

    QDomElement stateF = doc.createElement("state");
    stateF.appendChild(doc.createTextNode(QString().setNum(m_state)));


    QDomElement playerF = doc.createElement("playersInfo");
    titleF.appendChild(doc.createTextNode(m_playerInformation.join('\n')));


    parent.appendChild(gameIdF);
    parent.appendChild(gameMasterIdF);
    parent.appendChild(durationF);
    parent.appendChild(startTimeF);
    parent.appendChild(tableNumberF);
    parent.appendChild(levelF);
    parent.appendChild(maxF);
    parent.appendChild(minF);
    parent.appendChild(titleF);
    parent.appendChild(descriptionF);
    parent.appendChild(currentF);
    parent.appendChild(stateF);
    parent.appendChild(playerF);
    //doc.appendChild(parent);

    return parent;



}

void Scenario::readDataFromXml(QDomNode& node)
{
    QDomElement tmpElement = node.firstChildElement("gameMasterId");
    m_gameMasterId = tmpElement.text();
    tmpElement = node.firstChildElement("gameId");
    m_gameId =tmpElement.text();
    tmpElement = node.firstChildElement("duration");
    m_duration = tmpElement.text().toInt();
    tmpElement = node.firstChildElement("level");
    m_level = (LEVEL)tmpElement.text().toInt();
    tmpElement = node.firstChildElement("maximumPlayers");
    m_maximumPlayers = tmpElement.text().toInt();
    tmpElement = node.firstChildElement("minimumPlayers");
    m_minimumPlayers = tmpElement.text().toInt();
    tmpElement = node.firstChildElement("title");
    m_title = tmpElement.text();
    tmpElement = node.firstChildElement("description");
    m_description = tmpElement.text();
    tmpElement = node.firstChildElement("currentPlayers");
    m_currentPlayers = tmpElement.text().toInt();
    tmpElement = node.firstChildElement("state");
    m_state = (STATE)tmpElement.text().toInt();
    tmpElement = node.firstChildElement("startTime");
    m_startTime = QDateTime::fromString(tmpElement.text(),"dd.MM.yyyy:hh:mm:ss");
    tmpElement = node.firstChildElement("tableNumber");
    m_tableNumber = tmpElement.text().toInt();
    tmpElement = node.firstChildElement("playersInfo");
    m_playerInformation = tmpElement.text().split('\n');

}
#include <QJsonObject>

void Scenario::readDataFromJson(QJsonObject & obj)
{
    m_gameMasterId=obj["gameMasterId"].toString();
    m_gameId=obj["gameId"].toString();
    if(m_gameId.isEmpty())
        m_gameId=QString::number(obj["gameId"].toInt());
    m_duration=static_cast<quint64>(obj["duration"].toInt());
    m_level= static_cast<LEVEL>(obj["level"].toInt());
    m_maximumPlayers=static_cast<quint32>(obj["maximumPlayers"].toInt());
    m_minimumPlayers=static_cast<quint32>(obj["minimumPlayers"].toInt());
    m_title=obj["title"].toString();
    m_description=obj["description"].toString();
    m_currentPlayers=static_cast<quint32>(obj["currentPlayers"].toInt());
    m_state= static_cast<STATE>(obj["state"].toInt());
    m_startTime=QDateTime::fromString(obj["startTime"].toString(),"dd.MM.yyyy:hh:mm:ss");
    m_tableNumber=static_cast<quint32>(obj["tableNumber"].toInt());
    m_playerInformation=obj["playersInfo"].toString().split('\n');

}

void Scenario::writeDataToJson(QJsonObject & obj)
{
    obj["gameMasterId"]=m_gameMasterId;
    obj["gameId"]=m_gameId;
    obj["duration"]=(int)m_duration;
    obj["level"]=m_level;
    obj["maximumPlayers"]=(int)m_maximumPlayers;
    obj["minimumPlayers"]=(int)m_minimumPlayers;
    obj["title"]=m_title;
    obj["description"]=m_description;
    obj["currentPlayers"]=(int)m_currentPlayers;
    obj["state"]=m_state;
    obj["startTime"]=m_startTime.toString("dd.MM.yyyy:hh:mm:ss");
    obj["tableNumber"]=(int)m_tableNumber;
    obj["playersInfo"]=m_playerInformation.join('\n');


}

void Scenario::writeDataToCsv(QTextStream& out)
{
    out << m_gameMasterId << ";"<<m_gameMasterId << ";"<<m_gameId << ";"<<m_duration << ";"<< m_level << ";"<< m_maximumPlayers << ";"
        <<m_minimumPlayers  << ";" << m_title  << ";"<< m_description  << ";"<< m_currentPlayers  << ";"<< m_state  << ";"<< m_startTime.toString("dd.MM.yyyy:hh:mm:ss")<< "\n";

}

void Scenario::readDataFromCsv(QTextStream&)
{

}

void Scenario::setAvailableTime(QDateTime a)
{
    m_availableTime = a;
}
QDateTime Scenario::getAvailableTime() const
{
    return m_availableTime;
}
void Scenario::setPlayerInformation(QStringList m)
{
    m_playerInformation=m;
}
QStringList Scenario::getPlayerInformation() const
{
    return m_playerInformation;
}
void Scenario::addPlayerInfo(QString info)
{
    m_playerInformation.append(info);
}
