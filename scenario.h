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
#ifndef GAMESESSION_H
#define GAMESESSION_H

#include <QString>
#include <QDateTime>
#include <QUuid>
#include "serializable.h"

class Scenario : public Serialisable
{
public:
    enum LEVEL {BEGINNER,AVERAGE,EXPERIMENTED};
    enum STATE {AVAILABLE,RUNNING,DONE};

    Scenario();

//set
    void setGameId(QString id);
    void setGameMasterId(QString id);
    void setDuration(quint64 id);
    void setTableNumber(quint32 number);
    void setDateTime(QDateTime time);
    void setLevel(Scenario::LEVEL);
    void setMaximumPlayer(quint32);
    void setMinimumPlayer(quint32);
    void setTitle(QString m);
    void setState(Scenario::STATE m);
    void setDescription(QString m);
    void setCurrentPlayers(quint32 m);


//gets
    Scenario::LEVEL getLevel() const;
    Scenario::STATE getState() const;
    quint64 getDuration() const;
    quint32 getMaximumPlayers() const;
    quint32 getMinimumPlayers() const;
    quint32 getCurrentPlayers() const;
    QString getGameId();
    QString getTitle();
    QString getDescription();
    QString getGameMasterId();
    quint64 getDuration();
    quint32 getTableNumber();
    QDateTime getDateTime();



//save & restore
    virtual void readFromData(QDataStream&);
    virtual void writeToData(QDataStream&) const;

    friend QDataStream &operator<<(QDataStream &out, const Scenario &myObj);
    friend QDataStream &operator>>(QDataStream &in, Scenario &myObj);

    void increaseCurrentPlayerCount(quint32 i =1 );
    void decreaseCurrentPlayerCount(quint32 i =1 );

private:
    QString m_gameId;
    QString m_gameMasterId;
    QString m_scenarioId;
    quint64 m_duration;//minutes
    quint32 m_tableNumber;
    QDateTime m_startTime;
    LEVEL m_level;
    quint32 m_maximumPlayers;
    quint32 m_minimumPlayers;
    quint32 m_currentPlayers;
    QString m_title;
    QString m_description;
    STATE m_state;

};



 Q_DECLARE_METATYPE(Scenario)
#endif // GAMESESSION_H
