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



#include "scenario.h"
#include "scenariomodel.h"
#include "scenarioitemdelegate.h"
#include "customerview.h"
namespace Ui {
class MainWindow;
}

class ScenarioManager : public QObject
{
    Q_OBJECT
public:
    explicit ScenarioManager(Ui::MainWindow* ui,QObject *parent = 0);
    

    void addScenarios(QList<Scenario*>* l,Scenario::STATE s = Scenario::AVAILABLE);
    
    void addScenario(Scenario* l,Scenario::STATE s = Scenario::AVAILABLE);

    void removeScenarioFromList(QList<Scenario*>* l);

    ScenarioModel* getRightModel(Scenario::STATE m);

public slots:
    void showCustomView(bool);

private:
    ScenarioModel* m_availableScenarioModel;
    ScenarioModel* m_runningScenarioModel;
    ScenarioModel* m_doneScenarioModel;
    //QList<Scenario*>* m_availableScenarioList;
    //QList<Scenario*>* m_runningScenarioList;
    //QList<Scenario*>* m_doneScenarioList;

    Ui::MainWindow* m_ui;
    ScenarioItemDelegate* m_scenarioDelegate;
    QMap<QString,Game*> m_list;

    CustomerView* m_customerView;
};

#endif // SCENARIOMANAGER_H
