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
#include "scenarioeditordialog.h"


#include <QDebug>
#include <QContextMenuEvent>


ScenarioManager::ScenarioManager(Ui::MainWindow* ui,QMap<QString,Game*>& map,QMap<QString,GameMaster*>& mastermap, QObject *parent ) :
    QObject(parent),m_ui(ui),m_list(map),m_masterList(mastermap)
{
    qDebug() << m_masterList.keys();
    //model
    m_availableScenarioModel = new ScenarioModel(Scenario::AVAILABLE);
    m_runningScenarioModel = new ScenarioModel(Scenario::RUNNING);
    m_doneScenarioModel = new ScenarioModel(Scenario::DONE);


    m_customerView = new CustomerView();

    //view
    m_ui->m_scenarioAvailabeView->setModel(m_availableScenarioModel);
    m_ui->m_scenarioAvailabeView->installEventFilter(this);
    m_ui->m_scenarioRunningView->setModel(m_runningScenarioModel);
    m_ui->m_scenarioRunningView->installEventFilter(this);
    m_ui->m_scenarioDoneView->setModel(m_doneScenarioModel);
    m_ui->m_scenarioDoneView->installEventFilter(this);

    //Actions
    m_increasePlayersCount = new QAction(tr("+1 player"),this);
    m_increasePlayersCount->setShortcut(Qt::Key_Plus);

    m_decreasePlayersCount = new QAction(tr("-1 player"),this);
    m_decreasePlayersCount->setShortcut(Qt::Key_Minus);

    m_startScenario = new QAction(tr("Start"),this);
    m_editScenario = new QAction(tr("Edit..."),this);

    m_scenarioIsFinished = new QAction(tr("Finish"),this);

    //connect
    connect(m_increasePlayersCount,SIGNAL(triggered()),this,SLOT(increaseCurrentPlayerCount()));
    connect(m_decreasePlayersCount,SIGNAL(triggered()),this,SLOT(decreaseCurrentPlayerCount()));
    connect(m_startScenario,SIGNAL(triggered()),this,SLOT(startScenario()));
    connect(m_editScenario,SIGNAL(triggered()),this,SLOT(editScenario()));
    connect(m_scenarioIsFinished,SIGNAL(triggered()),this,SLOT(scenarioIsDone()));



    m_avScenarioDelegate = new ScenarioItemDelegate(m_list,m_masterList,Scenario::AVAILABLE);
    m_ui->m_scenarioAvailabeView->setItemDelegate(m_avScenarioDelegate);


    m_runningScenarioDelegate = new ScenarioItemDelegate(m_list,m_masterList,Scenario::RUNNING);
    m_ui->m_scenarioRunningView->setItemDelegate(m_runningScenarioDelegate);


    m_doneScenarioDelegate = new ScenarioItemDelegate(m_list,m_masterList,Scenario::DONE);
    m_ui->m_scenarioDoneView->setItemDelegate(m_doneScenarioDelegate);
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


bool ScenarioManager::eventFilter(QObject *obj, QEvent *event)
{
    if (obj == m_ui->m_scenarioAvailabeView)
    {
       return eventFilterForAvailable(event);
    }
    else if(obj == m_ui->m_scenarioRunningView)
    {
        return eventFilterForRunning(event);
    }
    else if(obj == m_ui->m_scenarioDoneView)
    {
        return eventFilterForDone(event);
    }
    else
    {
        return QObject::eventFilter(obj, event);
    }
}
//slots to perform action
void ScenarioManager::showContextMenu(QContextMenuEvent* event,Scenario::STATE m)
{
    QMenu menu;

    menu.addAction(m_increasePlayersCount);
    menu.addAction(m_decreasePlayersCount);
    switch(m)
    {
    case Scenario::AVAILABLE:
        menu.addSeparator();
        menu.addAction(m_startScenario);
        break;
    case Scenario::RUNNING:
        menu.addSeparator();
        menu.addAction(m_scenarioIsFinished);
        break;
    case Scenario::DONE:
        break;

    }


    menu.addSeparator();
    menu.addAction(m_editScenario);

    menu.exec(event->globalPos());
}
void ScenarioManager::increaseCurrentPlayerCount()
{
    QModelIndex index = m_ui->m_scenarioAvailabeView->currentIndex();

    if(index.isValid())
    {
        QVariant var = index.data(Qt::UserRole);
        Scenario sce = var.value<Scenario>();
        //
        ScenarioModel* model = getRightModel(sce.getState());
        model->setData(index,1,ScenarioModel::INCREASE_CURRENT);
    }
}
void ScenarioManager::decreaseCurrentPlayerCount()
{
    QModelIndex index = m_ui->m_scenarioAvailabeView->currentIndex();

    if(index.isValid())
    {
        QVariant var = index.data(Qt::UserRole);
        Scenario sce = var.value<Scenario>();
        //
        ScenarioModel* model = getRightModel(sce.getState());
        model->setData(index,1,ScenarioModel::DECREASE_CURRENT);
    }
}
void ScenarioManager::startScenario()
{
    QModelIndex index = m_ui->m_scenarioAvailabeView->currentIndex();

    if(index.isValid())
    {
        QVariant var = index.data(Qt::UserRole);
        Scenario sce = var.value<Scenario>();
        //
        ScenarioModel* model = getRightModel(sce.getState());
        Scenario* mySce = model->getScenarioById(sce.getScenarioId());
        model->removeScenario(mySce);
        mySce->setState(Scenario::RUNNING);
        model = getRightModel(mySce->getState());
        model->appendScenario(mySce);

    }
}
void ScenarioManager::editScenario()
{
    QModelIndex index = m_ui->m_scenarioAvailabeView->currentIndex();

    if(index.isValid())
    {
        QVariant var = index.data(Qt::UserRole);
        Scenario sce = var.value<Scenario>();
        //
        ScenarioModel* model = getRightModel(sce.getState());
        Scenario* mySce = model->getScenarioById(sce.getScenarioId());
        ScenarioEditorDialog dialog(m_list);
        dialog.setModel(model);
        dialog.exec();
    }
}
bool ScenarioManager::eventFilterForAvailable( QEvent *event)
{
    if (event->type() == QEvent::KeyPress)
    {
        QKeyEvent* keyEvent = static_cast<QKeyEvent*>(event);
        qDebug() << "Ate key press" << keyEvent->key();
        switch(keyEvent->key())
        {
        case Qt::Key_Plus:
            increaseCurrentPlayerCount();
            break;
        case Qt::Key_Minus:
            decreaseCurrentPlayerCount();
            break;
        case Qt::Key_Enter:
            editScenario();
            break;
        }

        return true;
    }
    else if (event->type() == QEvent::MouseButtonDblClick)
    {
        editScenario();
        return true;
    }
    else if(event->type() == QEvent::ContextMenu)
    {
        QContextMenuEvent* menuEvent = static_cast<QContextMenuEvent*>(event);
        showContextMenu(menuEvent,Scenario::AVAILABLE);
        return true;
    }
    else
    {
        return false;
    }
}
bool ScenarioManager::eventFilterForDone(QEvent * ent)
{
    return false;
}
bool ScenarioManager::eventFilterForRunning(QEvent * event)
{
    if(event->type() == QEvent::ContextMenu)
    {
        QContextMenuEvent* menuEvent = static_cast<QContextMenuEvent*>(event);
        showContextMenu(menuEvent,Scenario::RUNNING);
        return true;
    }
}
void ScenarioManager::scenarioIsDone()
{
    QModelIndex index = m_ui->m_scenarioRunningView->currentIndex();

    if(index.isValid())
    {
        QVariant var = index.data(Qt::UserRole);
        Scenario sce = var.value<Scenario>();
        //
        ScenarioModel* model = getRightModel(sce.getState());
        ////////////////////////


        Scenario* mySce = model->getScenarioById(sce.getScenarioId());
        Scenario* myNewSce = new Scenario();

        myNewSce->setReferenceScenario(mySce);


        model->removeScenario(mySce);
        mySce->setState(Scenario::AVAILABLE);
        model = getRightModel(mySce->getState());
        model->appendScenario(mySce);

        myNewSce->setState(Scenario::DONE);
        model = getRightModel(myNewSce->getState());
        model->appendScenario(myNewSce);
    }
}
