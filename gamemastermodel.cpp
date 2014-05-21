#include "gamemastermodel.h"

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
    else if(Qt::CheckStateRole == role)
    {
        return m_gameMasterList[index.row()]->isPresent();

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
          return true;
    }
    return false;

}

void GameMasterModel::append(GameMaster* tmp)
{
    beginInsertRows(QModelIndex(),m_gameMasterList.size(),m_gameMasterList.size());

    m_gameMasterList.append(tmp);

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
    }

}

void GameMasterModel::writeToData(QDataStream& to)
{
    to << m_gameMasterList.count();

    foreach(GameMaster* tmp,m_gameMasterList)
    {
        tmp->writeToData(to);
    }
}
Qt::ItemFlags GameMasterModel::flags ( const QModelIndex & index ) const
{
    return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsUserCheckable;
}
