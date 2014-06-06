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
#include "gamemaster.h"
#include <QUuid>
#include <QDataStream>

GameMaster::GameMaster()
    : m_id(QUuid::createUuid().toString())
{
    m_isPresent = false;
    m_scenarioList = new QList<Scenario*>();
}

void GameMaster::insertScenario(Scenario* game)
{
   m_scenarioList->append(game);

}

void GameMaster::removeScenario(Scenario* game)
{
    m_scenarioList->removeOne(game);
}

void GameMaster::setName(QString name)
{
    m_name = name;
}

void GameMaster::setFirstName(QString fn)
{
    m_firstName=fn;
}

void GameMaster::setNickName(QString fn)
{
    m_nickname=fn;
}

void GameMaster::setPhoneNumber(QString pn)
{
    m_phoneNumber = pn;
}

void GameMaster::setMailAddress(QString pn)
{
    m_mailAddress=pn;
}

QString GameMaster::getName() const
{
    return m_name;
}
QString GameMaster::getFirstName()const
{
    return m_firstName;
}

QString GameMaster::getNickName()const
{
    return m_nickname;
}
QString GameMaster::getPhoneNumber()const
{
    return m_phoneNumber;
}
QString GameMaster::getMailAddress()const
{
    return m_mailAddress;
}
void GameMaster::readFromData(QDataStream& from)
{
   from >> m_name;
   from >> m_phoneNumber;
   from >> m_firstName;
   from >> m_nickname;
   from >> m_mailAddress;
   from >> m_isPresent;
   from >> m_id;

   m_isPresent = false;
   int size;
   from >> size;
   for(int i = 0; i<size;++i)
   {
       Scenario* tmp = new Scenario();
       tmp->readFromData(from);
       insertScenario(tmp);
   }
}

void GameMaster::writeToData(QDataStream& to) const
{
    to << m_name;
    to << m_phoneNumber;
    to << m_firstName;
    to << m_nickname;
    to << m_mailAddress;
    to << m_isPresent;
    to << m_id;

    to << getScenarioCount();
    foreach(Scenario* tmp,*m_scenarioList)
    {
        tmp->writeToData(to);
    }


}
QDomElement GameMaster::writeDataToXml(QDomDocument& doc)
{
    QDomElement parent = doc.createElement("GameMaster");
    QDomElement idF = doc.createElement("gameMasterId");
    idF.appendChild(doc.createTextNode(m_id));

    QDomElement nameF = doc.createElement("name");
    nameF.appendChild(doc.createTextNode(m_name));

    QDomElement phoneNumberF = doc.createElement("phoneNumber");
    phoneNumberF.appendChild(doc.createTextNode(m_phoneNumber));

    QDomElement firstnameF = doc.createElement("firstname");
    firstnameF.appendChild(doc.createTextNode(m_firstName));

    QDomElement nickNameF = doc.createElement("nickname");
    nickNameF.appendChild(doc.createTextNode(m_nickname));

    QDomElement mailF = doc.createElement("mail");
    mailF.appendChild(doc.createTextNode(m_mailAddress));

    QDomElement isPresentF = doc.createElement("present");
    isPresentF.appendChild(doc.createTextNode(m_isPresent ? "y":"n"));



    parent.appendChild(idF);
    parent.appendChild(nameF);
    parent.appendChild(phoneNumberF);
    parent.appendChild(firstnameF);
    parent.appendChild(nickNameF);
    parent.appendChild(mailF);
    parent.appendChild(isPresentF);

    foreach(Scenario* tmp,*m_scenarioList)
    {
        parent.appendChild(tmp->writeDataToXml(doc));
    }


    return parent;
}

void GameMaster::readDataFromXml(QDomDocument&)
{

}
int GameMaster::getScenarioCount() const
{
   return m_scenarioList->count();
}



bool GameMaster::isPresent()
{
    return m_isPresent;
}

void GameMaster::setPresent(bool b)
{
    m_isPresent = b;
}
QString GameMaster::getId() const
{
    return m_id;
}
QList<Scenario*>*  GameMaster::getGMScenarios() const
{
    return m_scenarioList;
}
void  GameMaster::setGMScenario(QList<Scenario*>* l)
{
    m_scenarioList = l;
}
