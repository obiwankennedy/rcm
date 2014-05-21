#include "scenariomodel.h"

ScenarioModel::ScenarioModel(QObject *parent) :
    QAbstractListModel(parent)
{
    m_scenarioList = new QList<Scenario*>();
    m_columns << tr("Game")<< tr("Title")<< tr("Duration")<< tr("Level")<< tr("Min")<< tr("Max")<< tr("Description");
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

    return QVariant();
}
bool ScenarioModel::setData(const QModelIndex & index, const QVariant & value, int role)
{
    if(!index.isValid())
        return false;

    if(role==Qt::EditRole)
    {
        bool result=false;
        switch(index.column())
        {
            case 0:
                m_scenarioList->at(index.row())->setGameId(value.toString());
                result = true;
                break;
            case 1:
                m_scenarioList->at(index.row())->setTitle(value.toString());
                result = true;
                break;
            case 2:
                m_scenarioList->at(index.row())->setDuration(value.toInt());
                result = true;
                break;
            case 3:
                m_scenarioList->at(index.row())->setLevel((Scenario::LEVEL)value.toInt());
                result = true;
                break;
            case 4:
                m_scenarioList->at(index.row())->setMinimumPlayer(value.toInt());
                result = true;
                break;
            case 5:
                 m_scenarioList->at(index.row())->setMaximumPlayer(value.toInt());
                result = true;
                break;
            case 6:
                m_scenarioList->at(index.row())->setDescription(value.toString());
                result = true;
                break;
        }
            emit updateHeader();
          return result;
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
    beginInsertRows(QModelIndex(),m_scenarioList->size(),m_scenarioList->size()+l->size());
    m_scenarioList->append(*l);
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
