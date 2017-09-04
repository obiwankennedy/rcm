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
#include <QDebug>
#ifdef __QT_QUICK_2_
GameModel::GameModel(GameImageProvider* gameImageProvider, QObject *parent) :
    QAbstractListModel(parent),m_gameImgProvider(gameImageProvider)
  #else
GameModel::GameModel(QObject *parent) :
    QAbstractListModel(parent)
#endif
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
    }//enum CustomRole {PunchLine = Qt::UserRole+1,Description,IMAGE_URL,TYPE};
    else if(GameModel::PunchLine == role)
    {
        return m_gameList[index.row()]->getPunchLine();
    }
    else if(GameModel::Description == role)
    {
        return m_gameList[index.row()]->getDescription();
    }
    else if(GameModel::IMAGE_URL == role)
    {
        return m_gameList[index.row()]->getImageUrl();
    }
    else if(GameModel::TYPE == role)
    {
        return m_gameList[index.row()]->getType();
    }
    return QVariant();
}

void GameModel::append(Game* tmp)
{
    int position = -1;
  //  bool unfound = true;
    int start = 0;
    int end = m_gameList.size();
    int tmpPosition = 0;
    while (start!=end)
    {
        tmpPosition = (start + end )/2;
        if(m_gameList[tmpPosition]->getTitle().compare(tmp->getTitle(),Qt::CaseInsensitive)>0)
        {
            end = tmpPosition;
        }
        else
        {
            if(start==tmpPosition)
            {
                ++tmpPosition;
            }
            start = tmpPosition;
        }
    }
    position = start;
    beginInsertRows(QModelIndex(),position,position);
    #ifdef __QT_QUICK_2_
    QObject::connect(tmp,SIGNAL(pixmapChanged(QString,QPixmap*)),m_gameImgProvider,SLOT(insertPixmap(QString,QPixmap*)));
#endif

    m_gameList.insert(position,tmp);
    m_gameMap.insert(tmp->getUuid(),tmp);

    #ifdef __QT_QUICK_2_
    m_gameImgProvider->insertPixmap(tmp->getIdImage(),tmp->getPixmap());
#endif
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

void GameModel::writeToData(QDataStream& to) const
{
    to << m_gameList.count();

    foreach(Game* tmp,m_gameList)
    {
        tmp->writeToData(to);
    }
}

void GameModel::readDataToJson(QJsonObject &)
{

}

void GameModel::writeDataToJson(QJsonObject &)
{

}
QMap<QString,Game*>& GameModel::getGameMap()
{
    return m_gameMap;
}
QList<Game*>& GameModel::getGameList()
{
    return m_gameList;
}
void GameModel::removeItem(QModelIndex& index)
{
    beginRemoveRows(QModelIndex(),index.row(),index.row());

    Game* tmp = m_gameList.at(index.row());
    m_gameMap.remove(tmp->getUuid());
    m_gameList.removeAll(tmp);
    endRemoveRows();
}
QDomElement GameModel::writeDataToXml(QDomDocument& doc)
{
    QDomElement gameList = doc.createElement("GamList");
    foreach(Game* tmp,m_gameList)
    {
        gameList.appendChild(tmp->writeDataToXml(doc));
    }
    return gameList;
}

void GameModel::readDataFromXml(QDomNode& doc)
{

   QDomElement gameList = doc.firstChildElement("GamList");
   QDomElement elt = gameList.firstChildElement("game");
    for (; !elt.isNull(); elt = elt.nextSiblingElement("game"))
    {
        Game* tmp = new Game();
        tmp->readDataFromXml(elt);
        append(tmp);
    }

}
void GameModel::resetData()
{
    beginResetModel();
    m_gameList.clear();
    m_gameMap.clear();
    #ifdef __QT_QUICK_2_
    m_gameImgProvider->resetData();
    #endif
    endResetModel();
}
void GameModel::writeSettings(QSettings& settings)
{
    settings.beginGroup("games");
    settings.beginWriteArray("games");

    for (int i = 0; i < m_gameList.size(); ++i)
    {
        Game* game = m_gameList.at(i);
        settings.setArrayIndex(i);
        settings.setValue("title", game->getTitle());
        settings.setValue("punchline", game->getPunchLine());
        settings.setValue("description", game->getDescription());
        settings.setValue("uuid", game->getUuid());
        settings.setValue("type", game->getType());
        settings.setValue("imageUrl", game->getImageUrl());
        QPixmap* map = game->getPixmap();
        QVariant var = *map;
        settings.setValue("image",var);
    }
    settings.endArray();
    settings.endGroup();
}

void GameModel::readSettings(QSettings& settings)
{
    settings.beginGroup("games");
    int size = settings.beginReadArray("games");

   for (int i = 0; i < size; ++i)
   {
        settings.setArrayIndex(i);
        Game* game = new Game();
        game->setTitle(settings.value("title").toString());
        game->setPunchLine(settings.value("punchline").toString());
        game->setDescription(settings.value("description").toString());
        game->setUuid(settings.value("uuid").toString());
        game->setType(settings.value("type").toString());
        game->setImageUrl(settings.value("imageUrl").toString());
        QPixmap* pix = new QPixmap();
        *pix = settings.value("image").value<QPixmap>();
        game->setPixmap(pix);

        m_gameList.append(game);
        m_gameMap.insert(game->getUuid(),game);

        m_gameImgProvider->insertPixmap(game->getIdImage(),game->getPixmap());

   }
   settings.endArray();
   settings.endGroup();
}
