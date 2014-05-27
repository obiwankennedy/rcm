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
#ifndef SCENARIOMANAGER_H
#define SCENARIOMANAGER_H

#include <QObject>
#include <QList>
#include <QListView>


#include "scenario.h"
#include "scenariomodel.h"
#include "scenarioitemdelegate.h"
#include "customerview.h"
#include "gamemaster.h"

namespace Ui {
class MainWindow;
}

class ScenarioManager : public QObject
{
    Q_OBJECT
public:
    explicit ScenarioManager(Ui::MainWindow* ui,QMap<QString,Game*>& map,QMap<QString,GameMaster*>& mastermap,QObject *parent = 0);
    
    
    void addScenarios(QList<Scenario*>* l,Scenario::STATE s = Scenario::AVAILABLE);
    
    void addScenario(Scenario* l,Scenario::STATE s = Scenario::AVAILABLE);
    
    void removeScenarioFromList(QList<Scenario*>* l);
    
    ScenarioModel* getRightModel(Scenario::STATE m);
    QListView* getFocusedListView();
    
protected:
    bool eventFilter(QObject *obj, QEvent *event);
    void showContextMenu(QContextMenuEvent* event,Scenario::STATE m);
    bool eventFilterForAvailable(QEvent* );
    bool eventFilterForRunning(QEvent* );
    bool eventFilterForDone(QEvent* );
    
public slots:
    void showCustomView(bool);
    void increaseCurrentPlayerCount();
    void decreaseCurrentPlayerCount();
    void startScenario();
    void editScenario();
    void scenarioIsDone();
    
    
    
private:
    ScenarioModel* m_availableScenarioModel;
    ScenarioModel* m_runningScenarioModel;
    ScenarioModel* m_doneScenarioModel;
    
    
    ScenarioItemDelegate* m_avScenarioDelegate;
    ScenarioItemDelegate* m_runningScenarioDelegate;
    ScenarioItemDelegate* m_doneScenarioDelegate;
    
    //QList<Scenario*>* m_availableScenarioList;
    //QList<Scenario*>* m_runningScenarioList;
    //QList<Scenario*>* m_doneScenarioList;
    
    Ui::MainWindow* m_ui;
    
    QMap<QString,Game*>& m_list;
    QMap<QString,GameMaster*>& m_masterList;
    
    CustomerView* m_customerView;
    
    
    //Actions
    QAction* m_increasePlayersCount;
    QAction* m_decreasePlayersCount;
    QAction* m_startScenario;
    QAction* m_editScenario;
    QAction* m_scenarioIsFinished;
    
};

#endif // SCENARIOMANAGER_H
