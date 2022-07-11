#include "roommodel.h"

RoomModel::RoomModel(int roomCount,QObject *parent) :
    QAbstractListModel(parent)
{
    m_roomMap = new QMap<QString,int>();
    for(int i = 0; i<roomCount; ++i)
    {
        m_roomMap->insert(tr("Room %1").arg(i+1),0);
    }
}
QVariant RoomModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid())
        return QVariant();

    if(m_roomMap->isEmpty())
        return QVariant();

    if(Qt::EditRole == role || Qt::DisplayRole == role)
    {
        QString key = m_roomMap->keys()[index.row()];
        if(index.column()==0)
        {
            return key;
        }
        else
        {
            return m_roomMap->value(key);
        }
    }

    return QVariant();

}
bool RoomModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    QString key = m_roomMap->keys()[index.row()];
    if(Qt::EditRole == role || Qt::DisplayRole == role)
    {
        if(index.column()==0)
        {
            int valueOld=m_roomMap->value(key);
            m_roomMap->remove(key);
            m_roomMap->insert(value.toString(),valueOld);
            return true;
        }
        else
        {
            m_roomMap->insert(key,value.toInt());
            return true;
        }
    }
    return false;
}

int RoomModel::rowCount(const QModelIndex &/*parent*/) const
{
    return m_roomMap->size();
}
int RoomModel::columnCount(const QModelIndex &/*parent*/) const
{
    return 2;
}
QMap<QString,int>* RoomModel::getDataMap()
{
    return m_roomMap;
}
Qt::ItemFlags  RoomModel::flags(const QModelIndex &index) const
{
    if(index.column()>0)
    {
        return Qt::ItemIsSelectable | Qt::ItemIsEditable | Qt::ItemIsEnabled;
    }
    else
    {
        return Qt::ItemIsSelectable | Qt::ItemIsEnabled;
    }
}
