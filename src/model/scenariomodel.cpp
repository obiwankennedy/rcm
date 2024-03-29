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
#include <QColor>
#include <QDebug>
#include <QJsonArray>
#include <QJsonObject>

ScenarioModel::ScenarioModel(QMap<QString, Game*>& l, GameModel* gameModel, QMap<QString, GameMaster*>& lstGm,
    Scenario::STATE m, QObject* parent)
    : QAbstractTableModel(parent)
    , m_state(m)
    , m_list(l)
    , m_gameMasterMap(lstGm)
    , m_edition(true)
    , m_gameModel(gameModel)
{
    m_scenarioList= new QList<Scenario*>();

    // clang-format off
    m_columns << tr("Game")
              << tr("Title")
              << tr("Duration")
              << tr("Level")
              << tr("Min")
              << tr("Max")
              << tr("Register")
              << tr("Description")
              << tr("Available")
              << tr("State")
              << tr("Table Number")
              << tr("GM Name")
              << tr("Game")
              << tr("Count");
    // clang-format on

    qRegisterMetaType<Scenario>("Scenario");
    //qRegisterMetaTypeStreamOperators<Scenario>("Scenario");

    qRegisterMetaType<Scenario*>("Scenario*");
    // qRegisterMetaTypeStreamOperators<Scenario*>("Scenario*");

    m_timer= new QTimer();
    m_timer->setInterval(1000 * 15);
    if(m_state == Scenario::RUNNING)
    {
        connect(m_timer, SIGNAL(timeout()), this, SLOT(timeOut()));
        connect(this, SIGNAL(addedData()), this, SLOT(mayStartTimer()));
    }
}

int ScenarioModel::rowCount(const QModelIndex& parent) const
{
    if(!parent.isValid())
        return m_scenarioList->count();
    return 0;
}
int ScenarioModel::columnCount(const QModelIndex&) const
{
    return m_columns.count();
}
QVariant ScenarioModel::data(const QModelIndex& index, int role) const
{
    if(!index.isValid())
        return QVariant();

    if((Qt::DisplayRole == role) || (Qt::EditRole == role))
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
            return m_scenarioList->at(index.row())->getCurrentPlayers();
        case 7:
            return m_scenarioList->at(index.row())->getDescription();
        case 8:
            return m_scenarioList->at(index.row())->getAvailableTime();
        case 9:
            return m_scenarioList->at(index.row())->getState();
        case 10:
            return m_scenarioList->at(index.row())->getTableNumber();
        case 11:
        {
            auto id= m_scenarioList->at(index.row())->getGameMasterId();
            GameMaster* tmp= m_gameMasterMap[id];
            if(tmp != nullptr)
                return tmp->getNickName();
            else
                return QVariant();
        }
        case 12:
        {
            auto id= m_scenarioList->at(index.row())->getGameId();
            Game* tmp= m_list[id];
            if(tmp != nullptr)
                return tmp->getTitle();
            else
                return QVariant();
        }
        case 13:
        {
            auto id= m_scenarioList->at(index.row())->getGameMasterId();
            GameMaster* tmp= m_gameMasterMap[id];
            if(tmp != nullptr)
                return tmp->getGameCount();
            else
                return QVariant();
        }
        }
    }
    else if(ScenarioModel::TitleRole == role)
    {
        return m_scenarioList->at(index.row())->getTitle();
    }
    else if(ScenarioModel::GameIdRole == role)
    {
        QVariant var(m_scenarioList->at(index.row())->getGameId());

        return var;
    }
    else if(ScenarioModel::GameMasterIdRole == role)
    {
        return m_scenarioList->at(index.row())->getGameMasterId();
    }
    else if(ScenarioModel::DurationRole == role)
    {
        return m_scenarioList->at(index.row())->getDuration();
    }
    else if(ScenarioModel::DescriptionRole == role)
    {
        QString id= m_scenarioList->at(index.row())->getGameId();
        Game* tmp= m_list[id];
        if(tmp != nullptr)
            return tmp->getDescription();
        else
            return QVariant();
    }
    else if(ScenarioModel::CurrentPlayerRole == role)
    {
        return m_scenarioList->at(index.row())->getCurrentPlayers();
    }
    else if(ScenarioModel::MaximumRole == role)
    {
        return m_scenarioList->at(index.row())->getMaximumPlayers();
    }
    else if(ScenarioModel::MinimumRole == role)
    {
        return m_scenarioList->at(index.row())->getMinimumPlayers();
    }
    else if(ScenarioModel::CurrentPlayerRole == role)
    {
        return m_scenarioList->at(index.row())->getCurrentPlayers();
    }
    else if(ScenarioModel::GameTitleRole == role)
    {
        QString id= m_scenarioList->at(index.row())->getGameId();
        Game* tmp= m_list[id];
        if(tmp != nullptr)
            return tmp->getTitle();
        else
            return QVariant();
    }
    else if(ScenarioModel::GameMasterNameRole == role)
    {
        QString id= m_scenarioList->at(index.row())->getGameMasterId();
        GameMaster* tmp= m_gameMasterMap[id];
        if(tmp != nullptr)
            return tmp->getNickName();
        else
            return QVariant();
    }
    else if(ScenarioModel::ColorRole == role)
    {
        int current= static_cast<int>(m_scenarioList->at(index.row())->getCurrentPlayers());
        int max= static_cast<int>(m_scenarioList->at(index.row())->getMaximumPlayers());

        qreal a= static_cast<qreal>(current) / static_cast<qreal>(max);
        int endHue= 120;
        int startHue= 0;
        int hueResult= startHue + (static_cast<int>(a) * (endHue - startHue));

        QColor result;

        result.setHsv(hueResult, 255, 255, 200);
        return result;
    }
    else if(ScenarioModel::GameCount == role)
    {
        QString id= m_scenarioList->at(index.row())->getGameMasterId();
        GameMaster* tmp= m_gameMasterMap[id];
        if(tmp != nullptr)
        {
            return tmp->getGameCount();
        }
        else
            return QVariant();
    }
    else if(Qt::UserRole == role)
    {
        QVariant var;
        Scenario* tmp= m_scenarioList->at(index.row());
        var.setValue(tmp);
        return var;
    }
    else if(ScenarioModel::PixmapRole == role)
    {
        QString id= m_scenarioList->at(index.row())->getGameId();
        Game* tmp= m_list[id];
        return m_gameModel->indexOf(tmp);

        /*if(tmp->hasPicture())
            return tmp->getIdImage();
        else
            return QString();*/
    }
    else if(ScenarioModel::LevelRole == role)
    {
        return m_scenarioList->at(index.row())->getLevel();
    }
    return QVariant();
}
void ScenarioModel::disableEdition()
{
    m_edition= false;
}

bool ScenarioModel::setData(const QModelIndex& index, const QVariant& value, int role)
{
    if(!index.isValid())
        return false;

    Scenario* current= m_scenarioList->at(index.row());

    if(role == Qt::EditRole)
    {
        bool result= false;
        switch(index.column())
        {
        case 0:
            current->setGameId(value.toString());
            result= true;
            break;
        case 1:
            current->setTitle(value.toString());
            result= true;
            break;
        case 2:
            current->setDuration(static_cast<quint64>(value.toInt()));
            result= true;
            break;
        case 3:
            current->setLevel(static_cast<Scenario::LEVEL>(value.toInt()));
            result= true;
            break;
        case 4:
            current->setMinimumPlayer(static_cast<quint32>(value.toInt()));
            result= true;
            break;
        case 5:
            current->setMaximumPlayer(static_cast<quint32>(value.toInt()));
            result= true;
            break;
        case 6:
            current->setDescription(value.toString());
            result= true;
            break;
        case 7:
            current->setCurrentPlayers(static_cast<quint32>(value.toInt()));
            result= true;
            break;
        case 8:
            current->setAvailableTime(value.toDateTime());
            result= true;
            break;
        case 9:
            current->setState(static_cast<Scenario::STATE>(value.toInt()));
            result= true;
            break;
        case 10:
            current->setTableNumber(static_cast<quint32>(value.toInt()));
            result= true;
            break;
        }
        emit updateHeader();
        emit dataChanged(index, index);
        return result;
    }
    else if(ScenarioModel::IncreaseRole == role)
    {
        current->increaseCurrentPlayerCount(static_cast<quint32>(value.toInt()));
        emit dataChanged(index, index);
        return true;
    }
    else if(ScenarioModel::DecreaseRole == role)
    {
        int valueInt= static_cast<int>(current->getCurrentPlayers()) - value.toInt();
        if(valueInt >= 0)
        {
            current->decreaseCurrentPlayerCount(static_cast<quint32>(value.toInt()));
            emit dataChanged(index, index);
            return true;
        }
        else
        {
            return false;
        }
    }
    else if(ScenarioModel::AddPlayerInfo == role)
    {
        current->addPlayerInfo(value.toString());

        return true;
    }
    else if(ScenarioModel::SetPlayerInfo == role)
    {
        current->setPlayerInformation(value.toStringList());
        return true;
    }
    return false;
}

Qt::ItemFlags ScenarioModel::flags(const QModelIndex&) const
{
    if(!m_edition)
    {
        return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
    }

    return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;
}

void ScenarioModel::setDataList(QList<Scenario*>* l)
{
    m_scenarioList= l;
}
void ScenarioModel::addDataList(QList<Scenario*>* l)
{
    beginInsertRows(QModelIndex(), m_scenarioList->size(), m_scenarioList->size() + l->size() - 1);
    m_scenarioList->append(*l);
    emit addedData();
    emit updateHeader();
    endInsertRows();
}

void ScenarioModel::appendScenario(Scenario* a)
{
    beginInsertRows(QModelIndex(), m_scenarioList->size(), m_scenarioList->size());
    m_scenarioList->append(a);
    emit addedData();
    emit updateHeader();

    endInsertRows();
}
void ScenarioModel::setPerformer(QString m_id)
{
    foreach(Scenario* tmp, *m_scenarioList)
    {
        tmp->setGameMasterId(m_id);
    }
}
QList<Scenario*>* ScenarioModel::getScenarioList()
{
    return m_scenarioList;
}

QVariant ScenarioModel::headerData(int section, Qt::Orientation orientation, int role) const
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
    if(nullptr == tmp)
        return;

    beginRemoveRows(QModelIndex(), m_scenarioList->indexOf(tmp), m_scenarioList->indexOf(tmp));
    m_scenarioList->removeOne(tmp);
    endRemoveRows();
}

void ScenarioModel::removeScenarioAtIndex(QModelIndex& index)
{
    if(!index.isValid() || m_scenarioList->isEmpty())
        return;

    auto i= index.row();
    if(i < m_scenarioList->size())
    {
        removeScenario(m_scenarioList->at(i));
    }
}
Scenario* ScenarioModel::getScenarioById(QString id)
{
    foreach(Scenario* tmp, *m_scenarioList)
    {
        if(tmp->getScenarioId() == id)
        {
            return tmp;
        }
    }
    return nullptr;
}
void ScenarioModel::mayStartTimer()
{
    if((!m_scenarioList->isEmpty()) && (!m_timer->isActive()))
    {
        m_timer->start();
    }
    else if(m_scenarioList->isEmpty())
    {
        m_timer->stop();
    }
}
void ScenarioModel::timeOut()
{
    if(!m_scenarioList->isEmpty())
    {
        // emit dataChanged(createIndex(0, 0), createIndex(m_scenarioList->size(), 0));
    }
}
QHash<int, QByteArray> ScenarioModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[GameIdRole]= "GameId";
    roles[GameMasterIdRole]= "GameMasterId";
    roles[DurationRole]= "Duration";
    roles[MinimumRole]= "MinimumPlayer";
    roles[MaximumRole]= "MaximumPlayer";
    roles[DescriptionRole]= "Description";
    roles[CurrentPlayerRole]= "CurrentPlayer";
    roles[TitleRole]= "Title";
    roles[GameTitleRole]= "GameTitle";
    roles[GameMasterNameRole]= "GMName";
    roles[ColorRole]= "ColorRole";
    roles[PixmapRole]= "PixmapRole";
    roles[LevelRole]= "Level";
    return roles;
}
void ScenarioModel::readFromData(QDataStream& from)
{
    int size;
    from >> size;
    for(int i= 0; i < size; ++i)
    {
        Scenario* tmp= new Scenario();
        tmp->readFromData(from);
        appendScenario(tmp);
        // emit gmHasBeenAdded(tmp);
    }
}
void ScenarioModel::writeToData(QDataStream& to) const
{
    to << m_scenarioList->count();

    foreach(Scenario* tmp, *m_scenarioList)
    {
        tmp->writeToData(to);
    }
}

void ScenarioModel::readDataFromJson(QJsonObject& obj)
{
    QJsonArray fieldArray= obj["items"].toArray();
    QJsonArray::Iterator it;
    for(it= fieldArray.begin(); it != fieldArray.end(); ++it)
    {
        QJsonObject obj= (*it).toObject();
        Scenario* tmp= new Scenario();
        tmp->readDataFromJson(obj);
        appendScenario(tmp);
    }
}

void ScenarioModel::writeDataToJson(QJsonObject& obj)
{
    QJsonArray fieldArray;
    for(auto tmp : *m_scenarioList)
    {
        QJsonObject scenario;
        tmp->writeDataToJson(scenario);
        fieldArray.append(scenario);
    }
    obj["items"]= fieldArray;
}
QDomElement ScenarioModel::writeDataToXml(QDomDocument& to)
{
    // to << m_scenarioList->count();
    QDomElement scenarioModel= to.createElement("scenarioModel");
    foreach(Scenario* tmp, *m_scenarioList)
    {
        scenarioModel.appendChild(tmp->writeDataToXml(to));
    }
    return scenarioModel;
}

void ScenarioModel::readDataFromXml(QDomNode&) {}
void ScenarioModel::resetData()
{
    beginResetModel();
    m_scenarioList->clear();
    endResetModel();
}
