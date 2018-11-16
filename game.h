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
#include <QPixmap>
#include <QNetworkAccessManager>

#include "serializable.h"

/**
 * @brief The Game class
 */
class Game : public QObject,public Serialisable
{
    Q_OBJECT
public:
    enum LEVEL {BEGINNER,AVERAGE,EXPERIMENTED};
    /**
     * @brief Game
     */
    Game();
    /**
     * @brief readFromData
     */
    virtual void readFromData(QDataStream&);
    /**
     * @brief writeToData
     */
    virtual void writeToData(QDataStream&) const;
    /**
     * @brief writeDataToXml
     * @return
     */
    virtual QDomElement writeDataToXml(QDomDocument&)  ;
    /**
     * @brief readDataFromXml
     */
    virtual void readDataFromXml(QDomNode&) ;

    virtual void readDataFromJson(QJsonObject&);
    virtual void writeDataToJson(QJsonObject&);


    /**
     * @brief setTitle
     * @param title
     */
    void setTitle(QString title);
    /**
     * @brief setPunchLine
     * @param title
     */
    void setPunchLine(QString title);
    /**
     * @brief setDescription
     * @param title
     */
    void setDescription(QString title);
    /**
     * @brief setPixmap
     * @param title
     */
    void setPixmap(QPixmap* title);
    /**
     * @brief setType
     * @param type
     */
    void setType(QString type);
    /**
     * @brief setImageUrl
     * @param url
     */
    void setImageUrl(QString url);
    /**
     * @brief setUuid
     * @param id
     */
    void setUuid(QString id);
    /**
     * @brief hasPicture
     * @return
     */
    bool hasPicture() const;
    bool hasValidImage() const;




    QString getTitle() const;
    QString getPunchLine() const;
    QString getDescription() const;
    QString getUuid() const;
    QString getIdImage() const;
    QPixmap* getPixmap( )const;
    QString getType( )const;
    QString getImageUrl( )const;
signals:
    /**
     * @brief pixmapChanged
     */
    void pixmapChanged(QString,QPixmap*);

public slots:
    /**
     * @brief replyFinished
     * @param reply
     */
    void replyFinished(QNetworkReply* reply);


private:
    QString m_uuid;
    QString m_title;
    QString m_description;
    QString m_punchLine;
    QString m_type;
    QString m_imageUrl;
    QPixmap* m_image;
    /**/

    QNetworkAccessManager * m_manager;
};

#endif // GAME_H
