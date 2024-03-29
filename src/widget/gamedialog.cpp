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
#include <QNetworkReply>

#include "gamedialog.h"
#include "ui_gamedialog.h"



GameDialog::GameDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddGameDialog)
{
    ui->setupUi(this);
    connect(ui->m_urlEdit,SIGNAL(editingFinished()),this,SLOT(uriChanged()));
    m_manager = new QNetworkAccessManager(this);
    connect(m_manager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(replyFinished(QNetworkReply*)));
}

GameDialog::~GameDialog()
{
    delete ui;
}

QString GameDialog::getTitle()
{
    return ui->m_titleEdit->text();
}

QString GameDialog::getPunchLine()
{
    return ui->m_punchLineEdit->text();
}

QString GameDialog::getDescription()
{
    return ui->m_descriptionEdit->toPlainText();
}
void GameDialog::setTitle(QString str)
{
    ui->m_titleEdit->setText(str);
}

void GameDialog::setPunchLine(QString styr)
{
    ui->m_punchLineEdit->setText(styr);
}

void GameDialog::setDescription(QString str)
{
    ui->m_descriptionEdit->setText(str);
}

void GameDialog::uriChanged()
{
   m_manager->get(QNetworkRequest(QUrl(ui->m_urlEdit->text())));
}
void GameDialog::replyFinished(QNetworkReply* reply)
{
    QByteArray data = reply->readAll();

    m_pix.loadFromData(data);

    ui->m_picture->setPixmap(m_pix);
}
QString GameDialog::getGameType()
{
    return ui->m_typeEdit->text();
}

const QPixmap GameDialog::getPixmap()
{
    return ui->m_picture->pixmap();
}
void GameDialog::setGameType(QString str)
{
    ui->m_typeEdit->setText(str);
}

void GameDialog::setImage(QPixmap pix)
{
    ui->m_picture->setPixmap(pix);
}
 QString GameDialog::getPixmapUrl()
 {
     return ui->m_urlEdit->text();
 }
void GameDialog::setPixmapUrl(QString str)
{
    return ui->m_urlEdit->setText(str);
}
