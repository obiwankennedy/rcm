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
#include "scenario.h"

class GameMaster : public Serialisable
{
public:
    enum Activity {FREE,INGAME,GONE};
    GameMaster();

    void insertScenario(Scenario*);
    void removeScenario(Scenario*);

    void setName(QString name);
    void setFirstName(QString fn);
    void setNickName(QString fn);
    void setPhoneNumber(QString pn);
    void setMailAddress(QString pn);
    void setCurrentActivity(GameMaster::Activity t);
    void setBackTime(QDateTime );

    QString getName() const ;
    QString getFirstName()const ;
    QString getNickName()const ;
    QString getPhoneNumber()const ;
    QString getMailAddress()const ;
    QString getId() const;
    GameMaster::Activity getCurrentActivity();
    QDateTime getBackTime();


    QList<Scenario*>* getGMScenarios() const;
    void setGMScenario(QList<Scenario*>* l);




    int getScenarioCount() const;


    bool isPresent();
    void setPresent(bool);


    virtual void readFromData(QDataStream&);
    virtual void writeToData(QDataStream&) const;
    virtual QDomElement writeDataToXml(QDomDocument&)  ;
    virtual void readDataFromXml(QDomNode&) ;
    virtual void readDataFromJson(QJsonObject&);
    virtual void writeDataToJson(QJsonObject&);


    QColor getColor() const;
    void setColor(const QColor &color);

private:
    QString m_id;
    QString m_name;
    QString m_phoneNumber;
    QColor m_color;
    QString m_firstName;
    QString m_nickname;
    QString m_mailAddress;
    QList<Scenario*>* m_scenarioList;

    bool m_isPresent;
    Activity m_currentActivity;
    QDateTime m_backTime;
};

#endif // GAMEMASTER_H
