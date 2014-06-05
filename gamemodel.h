/***************************************************************************
* Copyright (C) 2014 by Renaud Guezennec                                   *
* http://renaudguezennec.homelinux.org/accueil,3.html                      *
*                                                                          *
*  This file is part of rcm                                                *
*                                                                          *
* Rcm is free software; you can redistribute it and/or modify              *
* it under the terms of the GNU General Public License as published by     *
* the Free Software Foundation; either version 2 of the License, or        *
* (at your option) any later version.                                      *
*                                                                          *
* This program is distributed in the hope that it will be useful,          *
* but WITHOUT ANY WARRANTY; without even the implied warranty of           *
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the             *
* GNU General Public License for more details.                             *
*                                                                          *
* You should have received a copy of the GNU General Public License        *
* along with this program; if not, write to the                            *
* Free Software Foundation, Inc.,                                          *
* 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.                 *
***************************************************************************/
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
    virtual void writeToData(QDataStream&) const;

    virtual QDomElement& writeDataToXml(QDomDocument&);
    virtual void readDataFromXml(QDomDocument&);


    QMap<QString,Game*>& getGameMap();
    QList<Game*>& getGameList();

    virtual void removeItem(QModelIndex&);
    



private:
    QList<Game*> m_gameList;
    QMap<QString,Game*> m_gameMap;
    
};

#endif // GAMEMODEL_H
