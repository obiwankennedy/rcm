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
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QAction>

#include "gamemodel.h"
#include "gamemastermodel.h"
#include "scenario.h"
#include "customerview.h"

#include "preferences/preferencesmanager.h"
#include "serializable.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


    void readSettings();
    void writeSettings();
    

public slots:
    void addGameDialog();
    void addGameMasterDialog();

protected:
    void closeEvent ( QCloseEvent * event );


private slots:
    void saveData();
    void readFile();
    bool maybeSave();
    void saveAsData();
    void openData();




private:
    void initActions();

private:
    Ui::MainWindow *ui;
    //data model
    GameModel* m_gameModel;
    GameMasterModel* m_gameMasterModel;

    QList<Scenario*>* m_scenarioList;
    //GameMasterModel* m_gameMasterPresenceModel;

    //QActions
    QAction* m_addGameAct;
    QAction* m_removeGameAct;
    QAction* m_removeGMAct;
    QAction* m_addGMAct;

    CustomerView* m_customerView;

    QString m_currentDataPath;
    PreferencesManager* m_preferences;
};

#endif // MAINWINDOW_H
