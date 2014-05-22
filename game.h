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
#ifndef GAME_H
#define GAME_H

#include <QString>

#include "serializable.h"

class Game : public Serialisable
{

public:
    enum LEVEL {BEGINNER,AVERAGE,EXPERIMENTED};

    Game();
    virtual void readFromData(QDataStream&);
    virtual void writeToData(QDataStream&) const;

    //
    void setTitle(QString title);
    void setPunchLine(QString title);
    void setDescription(QString title);
    void setUuid(QString id);




    QString getTitle() const;
    QString getPunchLine() const;
    QString getDescription() const;
    QString getUuid() const;


private:
    QString m_uuid;
    QString m_title;
    QString m_description;
    QString m_punchLine;
    /**/

};

#endif // GAME_H
