#ifndef GAMEMASTERMODEL_H
#define GAMEMASTERMODEL_H

#include <QAbstractListModel>

#include "gamemaster.h"
#include "serializable.h"
class GameMasterModel : public QAbstractListModel, public Serialisable
{
    Q_OBJECT
public:
    explicit GameMasterModel(QObject *parent = 0);
    int rowCount ( const QModelIndex & parent = QModelIndex() ) const;
    QVariant data ( const QModelIndex & index, int role = Qt::DisplayRole ) const;
    bool setData(const QModelIndex & index, const QVariant & value, int role = Qt::EditRole);
    Qt::ItemFlags flags ( const QModelIndex & index ) const;
    
    void append(GameMaster*);

    virtual void readFromData(QDataStream&);
    virtual void writeToData(QDataStream&) ;
signals:
    
public slots:
    
private:
    QList<GameMaster*> m_gameMasterList;
};

#endif // GAMEMASTERMODEL_H
