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
#include <QSqlTableModel>

#include "game.h"
#include "serializable.h"
#include "gameimageprovider.h"


class GameModel : public QSqlTableModel, public Serialisable
{
    Q_OBJECT
public:
    enum CustomRole {PunchLine = Qt::UserRole+1,Description,IMAGE_URL,TYPE};

    explicit GameModel(GameImageProvider* gameImageProvider,QObject *parent = 0);

   /* int rowCount ( const QModelIndex & parent = QModelIndex() ) const;
    QVariant data ( const QModelIndex & index, int role = Qt::DisplayRole ) const;*/

    void append(Game*);


    virtual void readFromData(QDataStream&);
    virtual void writeToData(QDataStream&) const;
    virtual void readDataFromJson(QJsonObject&);
    virtual void writeDataToJson(QJsonObject&);


    virtual QDomElement writeDataToXml(QDomDocument&);
    virtual void readDataFromXml(QDomNode&);


    QMap<QString,Game*>& getGameMap();
    QList<Game*>& getGameList();

    virtual void removeItem(QModelIndex&);
    void resetData();


    void writeSettings(QSettings& settings);
    void readSettings(QSettings& settings);

private:
    GameImageProvider* m_gameImgProvider;
};

#endif // GAMEMODEL_H
