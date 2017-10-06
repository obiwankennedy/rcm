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
#include "gamemastermodel.h"
#include <QJsonArray>
#include <QJsonObject>
#include <QColor>
#include <QVariant>
#include <QDataStream>

GameMasterModel::GameMasterModel(QObject *parent) :
    QAbstractListModel(parent)
{
}
int GameMasterModel::rowCount ( const QModelIndex &  ) const
{
    return m_gameMasterList.count();
}

QVariant GameMasterModel::data ( const QModelIndex & index, int role ) const
{
    if(!index.isValid())
        return QVariant();

    if((Qt::DisplayRole == role)||(Qt::EditRole == role))
    {
        return m_gameMasterList[index.row()]->getNickName();
    }
    else if(Qt::BackgroundColorRole== role)
    {
        /// @todo puts image
        if(!m_gameMasterList[index.row()]->isPresent())
        {
            QVariant var;
            var.setValue(QColor(Qt::gray));
            return var;
        }
    }
    else if(Qt::DecorationRole == role)
    {
      return m_gameMasterList[index.row()]->getColor();
    }
    else if(Qt::CheckStateRole == role)
    {
        return m_gameMasterList[index.row()]->isPresent();
    }
    else if(GameMasterModel::NameRole == role)
    {
        return m_gameMasterList[index.row()]->getName();
    }
    else if(GameMasterModel::PhoneRole == role)
    {
        return m_gameMasterList[index.row()]->getPhoneNumber();
    }
    else if(GameMasterModel::FirstNameRole == role)
    {
        return m_gameMasterList[index.row()]->getFirstName();
    }
    else if(GameMasterModel::MailRole == role)
    {
        return m_gameMasterList[index.row()]->getMailAddress();
    }
    else if(GameMasterModel::ColorRole == role)
    {
      return m_gameMasterList[index.row()]->getColor();
    }

    return QVariant();
}
bool GameMasterModel::setData(const QModelIndex & index, const QVariant & value, int role)
{
    if(!index.isValid())
        return false;

    if(role==Qt::CheckStateRole)
    {
          m_gameMasterList[index.row()]->setPresent(!m_gameMasterList[index.row()]->isPresent());
          emit gameMasterStatusHasChanged(m_gameMasterList[index.row()],m_gameMasterList[index.row()]->isPresent());
          return true;
    }
    else if(role == GameMasterModel::BackTime)
    {

        QDateTime time = QDateTime::currentDateTime();
        time.addSecs(value.toInt()*60);
        m_gameMasterList[index.row()]->setBackTime(time);
        emit dataChanged(index,index);
        return true;
    }
    else if(GameMasterModel::ActivityRole==role)
    {
        m_gameMasterList[index.row()]->setCurrentActivity((GameMaster::Activity)value.toInt());
        emit dataChanged(index,index);
        return true;
    }
    return false;

}

void GameMasterModel::append(GameMaster* tmp)
{
    beginInsertRows(QModelIndex(),m_gameMasterList.size(),m_gameMasterList.size());

    m_gameMasterList.append(tmp);
    m_gameMasterMap.insert(tmp->getId(),tmp);

    endInsertRows();

}
void GameMasterModel::readFromData(QDataStream& from)
{
    int size;
    from >> size;
    for(int i = 0; i < size;++i)
    {
        GameMaster* tmp = new GameMaster();
        tmp->readFromData(from);
        append(tmp);
        emit gmHasBeenAdded(tmp);
    }

}

void GameMasterModel::writeToData(QDataStream& to) const
{
    to << m_gameMasterList.count();

    foreach(GameMaster* tmp,m_gameMasterList)
    {
        tmp->writeToData(to);
    }
}

void GameMasterModel::readDataFromJson(QJsonObject & json)
{
    QJsonArray fieldArray = json["items"].toArray();
    QJsonArray::Iterator it;
    for(it = fieldArray.begin(); it != fieldArray.end(); ++it)
    {
        QJsonObject obj = (*it).toObject();
        GameMaster* master = new GameMaster();
        master->readDataFromJson(obj);

        append(master);
        emit gmHasBeenAdded(master);
    }
}

void GameMasterModel::writeDataToJson(QJsonObject & obj)
{
    QJsonArray fieldArray;
    for(auto key : m_gameMasterMap.keys())
    {
        auto master = m_gameMasterMap.value(key);
        QJsonObject masterObj;
        master->writeDataToJson(masterObj);
        fieldArray.append(masterObj);
    }
    obj["items"]=fieldArray;

}
Qt::ItemFlags GameMasterModel::flags ( const QModelIndex & index ) const
{
    return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsUserCheckable;
}
QMap<QString,GameMaster*>& GameMasterModel::getMasterMap()
{
     return m_gameMasterMap;
}
QList<GameMaster*>& GameMasterModel::getMasterList()
{
    return m_gameMasterList;
}
void GameMasterModel::removeItem(QModelIndex& index)
{
    beginRemoveRows(QModelIndex(),index.row(),index.row());

    GameMaster* tmp = m_gameMasterList.at(index.row());
    m_gameMasterMap.remove(tmp->getId());
    m_gameMasterList.removeAll(tmp);
    emit gameMasterStatusHasChanged(tmp,false);
    endRemoveRows();
}
QDomElement GameMasterModel::writeDataToXml(QDomDocument& doc)
{
    QDomElement gmList = doc.createElement("GameMasterList");
    foreach(GameMaster* tmp,m_gameMasterList)
    {
        gmList.appendChild(tmp->writeDataToXml(doc));
    }
    return gmList;

}

void GameMasterModel::readDataFromXml(QDomNode& node)
{
    QDomElement gameList = node.firstChildElement("GameMasterList");
    QDomElement elt = gameList.firstChildElement("GameMaster");
     for (; !elt.isNull(); elt = elt.nextSiblingElement("GameMaster"))
     {
         GameMaster* tmp = new GameMaster();
         tmp->readDataFromXml(elt);
         append(tmp);
         emit gmHasBeenAdded(tmp);
     }
}
void GameMasterModel::resetData()
{
    beginResetModel();
    m_gameMasterList.clear();
    m_gameMasterMap.clear();
    endResetModel();
}
