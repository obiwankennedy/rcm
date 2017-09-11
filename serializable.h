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
#ifndef SERIALIZABLE_H
#define SERIALIZABLE_H

#include <QSettings>
#include <QTextStream>
#include <QDomDocument>

class SettingsUser
{
public:
    virtual void readSettings(QSettings&) = 0;
    virtual void writeSettings(QSettings&) = 0;
};

class Serialisable
{
public:
    virtual void readFromData(QDataStream&) = 0;
    virtual void writeToData(QDataStream&) const = 0;

    virtual void writeDataToJson(QJsonObject&) =0;
    virtual void readDataFromJson(QJsonObject&)=0;

    virtual QDomElement writeDataToXml(QDomDocument&) = 0 ;
    virtual void readDataFromXml(QDomNode&) = 0 ;
};

#endif // SERIALIZABLE_H
