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

#include "scenariomanager.h"

#include "preferences/preferencesmanager.h"
#include "serializable.h"

#include "gameimageprovider.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    enum TAB {DATA,SCENARIO};
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


    void readSettings();
    void writeSettings();


    void addRecentFile();
    void refreshOpenedFile();
    

    void refreshView();
public slots:
    void addGameDialog();
    void addGameMasterDialog();
    void addGmScenarioListToGlobalList(GameMaster* l);
    void statusGmHasChanged(GameMaster* l,bool);
    void ensureTabVisible(TAB);
    void makeGameMasterUnavailable();
    void openData();

protected:
    void closeEvent ( QCloseEvent * event );
    bool eventFilter(QObject *obj, QEvent *event);


private slots:
    void saveData();
    void saveDataToXml();
    void importDataFromXml();
    void readFile();
    bool maybeSave();
    void saveAsData();
    void resetData();
    void exporCSV();



    //edition
    void editGame(const QModelIndex& index);
    void editGameMaster(const QModelIndex& index);

    //removal
    void removeGame();
    void removeGameMaster();

    void openRecentFile();
    void clearSelection(QModelIndex index);
private:
    void initActions();
    void contextMenuForGameMaster(QContextMenuEvent* event);

private:
    Ui::MainWindow *ui;
    //data model
    GameModel* m_gameModel;
    GameMasterModel* m_gameMasterModel;


    //GameMasterModel* m_gameMasterPresenceModel;

    //QActions
    QAction* m_addGameAct;
    QAction* m_removeGameAct;
    QAction* m_removeGMAct;
    QAction* m_addGMAct;
    QAction* m_makeGMGoneAct;
    QMenu* m_recentFile;
    QList<QAction*>* m_recentFileActions;


    QQuickWindow* m_window;


    QString m_currentDataPath;
    PreferencesManager* m_preferences;
    ScenarioManager* m_scenarioManager;

    QString m_title;
    GameImageProvider* m_gameImgProvider;
};

#endif // MAINWINDOW_H
