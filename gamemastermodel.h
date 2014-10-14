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
#ifndef GAMEMASTERMODEL_H
#define GAMEMASTERMODEL_H

#include <QAbstractListModel>
#include <QMap>

#include "gamemaster.h"
#include "serializable.h"
class GameMasterModel : public QAbstractListModel, public Serialisable
{
    Q_OBJECT
public:
    enum CustomRole {BackTime = Qt::UserRole+1,ActivityRole};

    explicit GameMasterModel(QObject *parent = 0);
    int rowCount ( const QModelIndex & parent = QModelIndex() ) const;
    QVariant data ( const QModelIndex & index, int role = Qt::DisplayRole ) const;
    bool setData(const QModelIndex & index, const QVariant & value, int role = Qt::EditRole);
    Qt::ItemFlags flags ( const QModelIndex & index ) const;
    
    void append(GameMaster*);

    virtual void readFromData(QDataStream&);
    virtual void writeToData(QDataStream&) const;

    virtual QDomElement writeDataToXml(QDomDocument&);
    virtual void readDataFromXml(QDomNode&);


    QMap<QString,GameMaster*>& getMasterMap();
    QList<GameMaster*>& getMasterList();

    virtual void removeItem(QModelIndex&);
    void resetData();
signals:
    void gameMasterStatusHasChanged(GameMaster*,bool);
    void gmHasBeenAdded(GameMaster*);
public slots:
    
private:
    QList<GameMaster*> m_gameMasterList;
    QMap<QString,GameMaster*> m_gameMasterMap;
};

#endif // GAMEMASTERMODEL_H
