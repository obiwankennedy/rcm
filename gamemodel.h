#ifndef GAMEMODEL_H
#define GAMEMODEL_H

#include <QAbstractListModel>

#include "game.h"
#include "serializable.h"

class GameModel : public QAbstractListModel, public Serialisable
{
    Q_OBJECT
public:
    explicit GameModel(QObject *parent = 0);
    
    int rowCount ( const QModelIndex & parent = QModelIndex() ) const;
    QVariant data ( const QModelIndex & index, int role = Qt::DisplayRole ) const;

    void append(Game*);


    virtual void readFromData(QDataStream&);
    virtual void writeToData(QDataStream&) ;


    QMap<QString,Game*>& getGameMap();
    QList<Game*>& getGameList();

    



private:
    QList<Game*> m_gameList;
    QMap<QString,Game*> m_gameMap;
    
};

#endif // GAMEMODEL_H
