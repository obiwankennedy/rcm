#ifndef TABLEMODEL_H
#define TABLEMODEL_H

#include <QAbstractListModel>
#include <QString>
#include <QMap>

class TableModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit TableModel(QMap<QString,int>* data,QObject *parent = 0);

signals:

public slots:

};

#endif // TABLEMODEL_H
