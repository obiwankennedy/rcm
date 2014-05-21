#include "gamemodel.h"


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
