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
#ifndef ADDGAMEDIALOG_H
#define ADDGAMEDIALOG_H

#include <QDialog>
#include <QNetworkAccessManager>

//QNetworkAccessManager *manager = new QNetworkAccessManager(this);
//connect(manager, SIGNAL(finished(QNetworkReply*)),
//        this, SLOT(replyFinished(QNetworkReply*)));

//manager->get(QNetworkRequest(QUrl("http://qt-project.org")));
namespace Ui {
class AddGameDialog;
}

class GameDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit GameDialog(QWidget *parent = nullptr);
    ~GameDialog();

    QString getTitle();
    QString getPunchLine();
    QString getDescription();
    QString getGameType();
    QString getPixmapUrl();
    const QPixmap getPixmap();

    void setTitle(QString);
    void setPunchLine(QString);
    void setDescription(QString);
    void setGameType(QString);
    void setPixmapUrl(QString);
    void setImage(QPixmap);

public slots:
    void uriChanged();
    void replyFinished(QNetworkReply*);
    
private:
    Ui::AddGameDialog *ui;
    QNetworkAccessManager * m_manager;
    QPixmap m_pix;
};

#endif // ADDGAMEDIALOG_H
