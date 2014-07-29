#ifndef TABLEMODEL_H
#define TABLEMODEL_H

#include <QAbstractListModel>

class TableModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit TableModel(QObject *parent = 0);

signals:

public slots:

};

#endif // TABLEMODEL_H
