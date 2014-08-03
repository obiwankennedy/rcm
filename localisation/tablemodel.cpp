#include "tablemodel.h"

#include <QDebug>
TableModel::TableModel(QMap<QString,int>* data,QObject *parent) :
    QAbstractListModel(parent)
{
    m_tableList = new QList<Table*>();
    QStringList list = data->keys();
    int j=0;
    foreach(QString key, list)
    {
        for(int i = 0; i < data->value(key); ++i)
        {

            Table* tmp = new Table();
            tmp->setCapacity(0);
            tmp->setRoomName(key);
            tmp->setId(j);
            tmp->setState(true);
            ++j;
            m_tableList->append(tmp);
        }
    }
    m_header << tr("Number")<< tr("Description")<< tr("Capacity")<< tr("CurrentState")<< tr("RoomName");
}
QVariant TableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(Qt::EditRole == role || Qt::DisplayRole == role)
    {
        if(orientation==Qt::Horizontal)
        {
            return m_header[section];
        }
    }
    return QVariant();
}
QVariant TableModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid())
        return QVariant();

    if(m_tableList->isEmpty())
        return QVariant();

    if(Qt::EditRole == role || Qt::DisplayRole == role)
    {
        Table* key = m_tableList->at(index.row());
        switch(index.column())
        {
        case 0:
            return key->getId();
        case 1:
            return key->getDescription();
        case 2:
            return key->getCapacity();
        case 3:
            return key->getCurrentState();
        case 4:
            return key->getRoomName();
        }
    }

    return QVariant();

}
bool TableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if(!index.isValid())
        return false;

    if(m_tableList->isEmpty())
        return false;

    if(Qt::EditRole == role || Qt::DisplayRole == role)
    {
        Table* key = m_tableList->at(index.row());
        switch(index.column())
        {
        case 0:
            key->setId(value.toInt());
            break;
        case 1:
            key->setDescription(value.toString());
            break;
        case 2:
            key->setCapacity(value.toInt());
            break;
        case 3:
            key->setState(value.toBool());
            break;
        case 4:
            key->setRoomName(value.toString());
            break;
        }
        return true;
    }
    return false;
}
QList<Table*>* TableModel::getDataList()
{
    return m_tableList;
}

int TableModel::rowCount(const QModelIndex &parent) const
{
    return m_tableList->size();
}
int TableModel::columnCount(const QModelIndex &parent) const
{
    return m_header.size();
}
