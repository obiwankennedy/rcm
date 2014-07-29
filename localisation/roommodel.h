#ifndef ROOMMODEL_H
#define ROOMMODEL_H

#include <QAbstractListModel>
#include <QString>
#include <QMap>

class RoomModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit RoomModel(int roomCount, QObject *parent = 0);

    QVariant data(const QModelIndex &index, int role) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;

    QMap<QString,int>* getDataMap();

signals:

public slots:

private:
    QMap<QString,int>* m_roomMap;
};

#endif // ROOMMODEL_H
