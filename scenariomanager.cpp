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
#include "scenariomanager.h"
#include "ui_mainwindow.h"

#include <QDebug>

ScenarioManager::ScenarioManager(Ui::MainWindow* ui,QObject *parent) :
    QObject(parent),m_ui(ui)
{
    m_availableScenarioModel = new ScenarioModel();
    m_runningScenarioModel = new ScenarioModel();
    m_doneScenarioModel = new ScenarioModel();


    m_customerView = new CustomerView();


    ui->m_scenarioAvailabeView->setModel(m_availableScenarioModel);
    ui->m_scenarioRunningView->setModel(m_runningScenarioModel);
    ui->m_scenarioDoneView->setModel(m_doneScenarioModel);


    m_scenarioDelegate = new ScenarioItemDelegate(m_list);
    ui->m_scenarioAvailabeView->setItemDelegate(m_scenarioDelegate);
}


void ScenarioManager::addScenarios(QList<Scenario*>* l,Scenario::STATE m )
{
    foreach(Scenario* tmp,*l)
    {
        addScenario(tmp,m);
    }

}

void ScenarioManager::addScenario(Scenario* l,Scenario::STATE s)
{
    l->setState(s);
    ScenarioModel* model = getRightModel(s);
    model->appendScenario(l);
}
ScenarioModel* ScenarioManager::getRightModel(Scenario::STATE m)
{
    switch(m)
    {
    case Scenario::AVAILABLE:
        return m_availableScenarioModel;
    case Scenario::RUNNING:
        return m_runningScenarioModel;
    case Scenario::DONE:
        return m_doneScenarioModel;
    }
    return NULL;
}
void ScenarioManager::showCustomView(bool b)
{
    m_customerView->setVisible(b);
}
void ScenarioManager::removeScenarioFromList(QList<Scenario*>* l)
{
    foreach(Scenario* tmp,*l)
    {
        ScenarioModel* model = getRightModel(tmp->getState());
        model->removeScenario(tmp);
    }
}
