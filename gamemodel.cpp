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
#include "gamemodel.h"

#include <QDataStream>

GameModel::GameModel(QObject *parent) :
    QAbstractListModel(parent)
{
}
int GameModel::rowCount ( const QModelIndex &  ) const
{
    return m_gameList.count();
}

QVariant GameModel::data ( const QModelIndex & index, int role ) const
{
    if(!index.isValid())
        return QVariant();

    if((Qt::DisplayRole == role)||(Qt::EditRole == role))
    {
        return m_gameList[index.row()]->getTitle();
    }


    return QVariant();
}

void GameModel::append(Game* tmp)
{
    beginInsertRows(QModelIndex(),m_gameList.size(),m_gameList.size());

    m_gameList.append(tmp);
    m_gameMap.insert(tmp->getUuid(),tmp);

    endInsertRows();

}
void GameModel::readFromData(QDataStream& from)
{
    int size;
    from >> size;
    for(int i = 0; i < size;++i)
    {
        Game* tmp = new Game();
        tmp->readFromData(from);
        append(tmp);
    }

}

void GameModel::writeToData(QDataStream& to)
{
    to << m_gameList.count();

    foreach(Game* tmp,m_gameList)
    {
        tmp->writeToData(to);
    }
}
QMap<QString,Game*>& GameModel::getGameMap()
{
    return m_gameMap;
}
QList<Game*>& GameModel::getGameList()
{
    return m_gameList;
}
