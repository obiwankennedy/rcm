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
#include "game.h"
#include <QUuid>

Game::Game()
    : m_uuid(QUuid::createUuid().toString())
{


}
void Game::readFromData(QDataStream& from)
{
    from >> m_title;
    from >> m_punchLine;
    from >> m_description;
    from >> m_uuid;
}

void Game::writeToData(QDataStream& to) const
{
    to << m_title;
    to << m_punchLine;
    to << m_description;
    to << m_uuid;

}
QDomElement& Game::writeDataToXml(QDomDocument&)
{

}

void Game::readDataFromXml(QDomDocument&)
{

}

void Game::setTitle(QString title)
{
    m_title = title;
}


QString  Game::getTitle() const
{
    return m_title;
}

void Game::setPunchLine(QString line)
{
    m_punchLine = line;
}

void Game::setDescription(QString title)
{
    m_description = title;
}

void Game::setUuid(QString id)
{
    m_uuid = id;
}
QString Game::getPunchLine() const
{
    return m_punchLine;
}
QString Game::getDescription() const
{
    return m_description;
}
QString Game::getUuid() const
{
    return m_uuid;
}
