#include "tablemodel.h"

TableModel::TableModel(QMap<QString,int>* data,QObject *parent) :
    QAbstractListModel(parent)
{
}
