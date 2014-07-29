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

    void data(const QModelIndex &index, int role) const;
    void setData(const QModelIndex &index, const QVariant &value, int role);
    void rowCount(const QModelIndex &parent) const;
    void columnCount(const QModelIndex &parent) const;

signals:

public slots:

private:
    QMap<QString,int>* m_roomMap;
};

#endif // ROOMMODEL_H
