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
#include "mainwindow.h"
#include <QApplication>
#include <QTranslator>
#include <QSqlDatabase>
#include <QSqlError>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QString locale = QLocale::system().name();


    QTranslator rcmTranslator;
    rcmTranslator.load(":/rcm_" + locale);
    a.installTranslator(&rcmTranslator);


    QSqlDatabase db = QSqlDatabase::addDatabase("QPSQL");
    db.setHostName("localhost");
    db.setDatabaseName("rcm");
    db.setUserName("renaud");
    db.setPassword("hulan8ye");
    bool ok = db.open();

    if(ok)
    {
        qDebug() << "Connection succeed";
    }
    else
    {
        qDebug() << "error" << db.lastError().text();
    }


    MainWindow w;
    w.show();

   // w.openData();
    
    return a.exec();
}
