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
#include "scenariomodel.h"
#include <QDebug>

ScenarioModel::ScenarioModel(Scenario::STATE m,QObject *parent) :
    QAbstractListModel(parent),m_state(m)
{
    m_scenarioList = new QList<Scenario*>();
    m_columns << tr("Game")<< tr("Title")<< tr("Duration")<< tr("Level")<< tr("Min")<< tr("Max")<< tr("Description");

    qRegisterMetaType<Scenario>("Scenario");
    qRegisterMetaTypeStreamOperators<Scenario>("Scenario");


    m_timer = new QTimer();
    m_timer->setInterval(1000*15);
    if(m_state == Scenario::RUNNING)
    {
        connect(m_timer,SIGNAL(timeout()),this,SLOT(timeOut()));
        connect(this,SIGNAL(addedData()),this,SLOT(mayStartTimer()));
    }
}

int ScenarioModel::rowCount ( const QModelIndex &  ) const
{
    return m_scenarioList->count();
}
int ScenarioModel::columnCount ( const QModelIndex & parent  ) const
{
    return m_columns.count();
}
QVariant ScenarioModel::data ( const QModelIndex & index, int role ) const
{
    if(!index.isValid())
        return QVariant();

    if((Qt::DisplayRole == role)||(Qt::EditRole == role))
    {
        switch(index.column())
        {
            case 0:
                return m_scenarioList->at(index.row())->getGameId();
            case 1:
                return m_scenarioList->at(index.row())->getTitle();
            case 2:
                return m_scenarioList->at(index.row())->getDuration();
            case 3:
                return m_scenarioList->at(index.row())->getLevel();
            case 4:
                return m_scenarioList->at(index.row())->getMinimumPlayers();
            case 5:
                return m_scenarioList->at(index.row())->getMaximumPlayers();
            case 6:
                return m_scenarioList->at(index.row())->getDescription();
        }


    }

    else if(Qt::UserRole == role)
    {

        QVariant var;
        Scenario* tmp = m_scenarioList->at(index.row());
        var.setValue(*tmp);
        return var;
    }

    return QVariant();
}
bool ScenarioModel::setData(const QModelIndex & index, const QVariant & value, int role)
{
    if(!index.isValid())
        return false;

    Scenario* current=m_scenarioList->at(index.row());

    if(role==Qt::EditRole)
    {
        bool result=false;
        switch(index.column())
        {
            case 0:
                current->setGameId(value.toString());
                result = true;
                break;
            case 1:
                current->setTitle(value.toString());
                result = true;
                break;
            case 2:
                current->setDuration(value.toInt());
                result = true;
                break;
            case 3:
                current->setLevel((Scenario::LEVEL)value.toInt());
                result = true;
                break;
            case 4:
                current->setMinimumPlayer(value.toInt());
                result = true;
                break;
            case 5:
                 current->setMaximumPlayer(value.toInt());
                result = true;
                break;
            case 6:
               current->setDescription(value.toString());
                result = true;
                break;
        }
          emit updateHeader();
          emit dataChanged(index,index);
          return result;
    }
    else if(ScenarioModel::INCREASE_CURRENT == role)
    {

        if(current->getMaximumPlayers()>=current->getCurrentPlayers()+value.toInt())
        {
            current->increaseCurrentPlayerCount(value.toInt());
            emit dataChanged(index,index);
            return true;
        }
        else
        {
            return false;
        }
    }
    else if(ScenarioModel::DECREASE_CURRENT == role)
    {

        int valueInt = current->getCurrentPlayers()-value.toInt();
        if(valueInt>=0)
        {
            current->decreaseCurrentPlayerCount(value.toInt());
            emit dataChanged(index,index);
            return true;
        }
        else
        {
            return false;
        }
    }
    return false;

}

Qt::ItemFlags ScenarioModel::flags ( const QModelIndex & index ) const
{
    return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;
}

void ScenarioModel::setDataList(QList<Scenario*>* l )
{
    m_scenarioList = l;
}
void ScenarioModel::addDataList(QList<Scenario*>* l)
{
    beginInsertRows(QModelIndex(),m_scenarioList->size(),m_scenarioList->size()+l->size()-1);
    m_scenarioList->append(*l);
    emit addedData();
    emit updateHeader();
    endInsertRows();
}

void ScenarioModel::setGameList(QList<Game*>* l )
{
    m_gameList = l;
}
void ScenarioModel::appendScenario(Scenario* a)
{
    beginInsertRows(QModelIndex(),m_scenarioList->size(),m_scenarioList->size());
    m_scenarioList->append(a);
    emit addedData();
    emit updateHeader();
    endInsertRows();

}
void ScenarioModel::setPerformer(QString m_id)
{
    foreach(Scenario* tmp,*m_scenarioList)
    {
        tmp->setGameMasterId(m_id);
    }
}
QList<Scenario*>* ScenarioModel::getScenarioList()
{
    return m_scenarioList;
}

QVariant ScenarioModel::headerData ( int section, Qt::Orientation orientation, int role ) const
{
    if(orientation == Qt::Vertical)
        return QVariant();
    if(Qt::DisplayRole == role)
    {
        return m_columns[section];
    }

    return QVariant();
}
void ScenarioModel::removeScenario(Scenario* tmp)
{
    beginRemoveRows(QModelIndex(),m_scenarioList->indexOf(tmp),m_scenarioList->indexOf(tmp));
    m_scenarioList->removeOne(tmp);
    endRemoveRows();
}
Scenario* ScenarioModel::getScenarioById(QString id)
{
    foreach(Scenario* tmp,*m_scenarioList)
    {
        if(tmp->getScenarioId()==id)
        {

            return tmp;
        }

    }
    return NULL;
}
void ScenarioModel::mayStartTimer()
{
    if((!m_scenarioList->isEmpty())&&(!m_timer->isActive()))
    {
        m_timer->start();
    }
    else  if(m_scenarioList->isEmpty())
    {
        m_timer->stop();
    }
}
void ScenarioModel::timeOut()
{
    if(!m_scenarioList->isEmpty())
    {
       emit dataChanged(createIndex(0,0),createIndex(m_scenarioList->size(),0));
    }
}
