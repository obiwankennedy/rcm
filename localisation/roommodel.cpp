#include "roommodel.h"

RoomModel::RoomModel(int roomCount,QObject *parent) :
    QAbstractListModel(parent)
{
    m_roomMap = new QMap<Qstring,int>();
    for(int i = 0; i<roomCount; ++i)
    {
        m_roomMap->insert(tr("Room %1").arg(i),0);
    }
}
void RoomModel::data(const QModelIndex &index, int role) const
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
void RoomModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    QString key = m_roomMap->keys()[index.row()];
    if(Qt::EditRole == role || Qt::DisplayRole == role)
    {
        if(index.column()==0)
        {
            int valueOld=m_roomMap->value(key);
            m_roomMap->remove(key);
            m_roomMap->insert(value.toString(),valueOld);

        }
        else
        {
            m_roomMap->insert(key,value.toInt());
        }
    }
}

void RoomModel::rowCount(const QModelIndex &parent) const
{
    return m_roomMap->size();
}
void RoomModel::columnCount(const QModelIndex &parent) const
{
    return 2;
}
