#ifndef ROOMMODEL_H
#define ROOMMODEL_H

#include <QAbstractListModel>

class RoomModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit RoomModel(QObject *parent = 0);

signals:

public slots:

};

#endif // ROOMMODEL_H
