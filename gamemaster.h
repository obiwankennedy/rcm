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
#ifndef GAMEMASTER_H
#define GAMEMASTER_H

#include <QString>
#include <QList>

#include "game.h"
#include "serializable.h"

class GameMaster : public Serialisable
{
public:
    GameMaster();

    void insertGame(Game*,bool b = false);
    void removeGame(Game*);

    void setName(QString name);
    void setFirstName(QString fn);
    void setNickName(QString fn);
    void setPhoneNumber(QString pn);
    void setMailAddress(QString pn);

    QString getName() const ;
    QString getFirstName()const ;
    QString getNickName()const ;
    QString getPhoneNumber()const ;
    QString getMailAddress()const ;
    QString getId() const;


    int getGameCount();


    bool isPresent();
    void setPresent(bool);


    virtual void readFromData(QDataStream&);
    virtual void writeToData(QDataStream&);
protected:
    int getListGameCount();
    int getListGameAuthorCount();

private:
    QString m_id;
    QString m_name;
    QString m_phoneNumber;
    QString m_firstName;
    QString m_nickname;
    QString m_mailAddress;
    QList<Game*> m_gameList;
    QList<Game*> m_gameAuthorList;

    bool m_isPresent;
};

#endif // GAMEMASTER_H
