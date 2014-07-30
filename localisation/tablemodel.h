#ifndef TABLEMODEL_H
#define TABLEMODEL_H

#include <QAbstractListModel>
#include <QString>
#include <QMap>

#include "table.h"

class TableModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit TableModel(QMap<QString,int>* data,QObject *parent = 0);

    QVariant data(const QModelIndex &index, int role) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;


private:
    QList<Table*>* m_tableList;
};

#endif // TABLEMODEL_H
