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

#ifdef __QT_QUICK_2_
ScenarioManager::ScenarioManager(Ui::MainWindow* ui,QMap<QString,Game*>& map,QMap<QString,GameMaster*>& mastermap, GameImageProvider* gameImgProvider,QObject *parent ) :
    #else
ScenarioManager::ScenarioManager(Ui::MainWindow* ui,QMap<QString,Game*>& map,QMap<QString,GameMaster*>& mastermap,QObject *parent ) :
#endif
    QObject(parent),m_ui(ui),m_list(map),m_masterList(mastermap)
{

    //model
    m_availableScenarioModel = new ScenarioModel(m_list,m_masterList,Scenario::AVAILABLE);
    m_availableScenarioModel->disableEdition();
    m_runningScenarioModel = new ScenarioModel(m_list,m_masterList,Scenario::RUNNING);
    m_runningScenarioModel->disableEdition();
    m_doneScenarioModel = new ScenarioModel(m_list,m_masterList,Scenario::DONE);
    m_doneScenarioModel->disableEdition();

#ifdef __QT_QUICK_2_
    m_customerView = new CustomerView(gameImgProvider,m_availableScenarioModel);
    m_ui->m_customerViewDisplayAct->setEnabled(true);
    m_ui->m_customerViewDisplayAct->setVisible(true);
    connect(m_ui->m_scenarioAvailabeView,SIGNAL(clicked(QModelIndex)),m_customerView,SLOT(setSelectionIndex(QModelIndex)));
#else
    m_ui->m_customerViewDisplayAct->setEnabled(false);
    m_ui->m_customerViewDisplayAct->setVisible(false);
#endif

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
#ifdef __QT_QUICK_2_
    m_customerView->setVisible(b);
#endif
}
void ScenarioManager::setCustomViewFullScreen(bool b)
{
#ifdef __QT_QUICK_2_
    m_customerView->setVisible(b);
#endif
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
    bool retValue=false;
    if (obj == m_ui->m_scenarioAvailabeView)
    {
        retValue = eventFilterForAvailable(event);
    }
    else if(obj == m_ui->m_scenarioRunningView)
    {
        retValue =  eventFilterForRunning(event);
    }
    else if(obj == m_ui->m_scenarioDoneView)
    {
        retValue =  eventFilterForDone(event);
    }

    if(!retValue)
    {
        return QObject::eventFilter(obj, event);
    }
}
//slots to perform action
void ScenarioManager::showContextMenu(QContextMenuEvent* event,Scenario::STATE m)
{
    QModelIndex index = getFocusedListView()->indexAt(event->pos());

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

    if(!index.isValid())
    {
       m_increasePlayersCount->setEnabled(false);
       m_decreasePlayersCount->setEnabled(false);
       m_startScenario->setEnabled(false);
       m_scenarioIsFinished->setEnabled(false);
       m_editScenario->setEnabled(false);
       getFocusedListView()->clearSelection();
    }
    else
    {
        m_increasePlayersCount->setEnabled(true);
        m_decreasePlayersCount->setEnabled(true);
        m_startScenario->setEnabled(true);
        m_scenarioIsFinished->setEnabled(true);
        m_editScenario->setEnabled(true);
    }

    menu.exec(event->globalPos());
}
void ScenarioManager::increaseCurrentPlayerCount()
{
    QModelIndex index = getFocusedListView()->currentIndex();

    if(index.isValid())
    {
        QVariant var = index.data(Qt::UserRole);
        Scenario sce = var.value<Scenario>();
        //
        ScenarioModel* model = getRightModel(sce.getState());
        model->setData(index,1,ScenarioModel::IncreaseRole);
    }
}
void ScenarioManager::decreaseCurrentPlayerCount()
{
    QModelIndex index = getFocusedListView()->currentIndex();

    if(index.isValid())
    {
        QVariant var = index.data(Qt::UserRole);
        Scenario sce = var.value<Scenario>();
        //
        ScenarioModel* model = getRightModel(sce.getState());
        model->setData(index,1,ScenarioModel::DecreaseRole);
    }
}
void ScenarioManager::startScenario()
{
    QModelIndex index = getFocusedListView()->currentIndex();


    if(index.isValid())
    {
        QVariant var = index.data(Qt::UserRole);
        Scenario sce = var.value<Scenario>();

        ScenarioModel* model = getRightModel(sce.getState());
        Scenario* mySce = model->getScenarioById(sce.getScenarioId());
        //model->removeScenario(mySce);
        Scenario* myNewSce = new Scenario();
        myNewSce->setReferenceScenario(mySce);
        mySce->reset();
        myNewSce->setState(Scenario::RUNNING);
        model = getRightModel(myNewSce->getState());
        model->appendScenario(myNewSce);


        GameMaster* gamemaster = getGameMasterFromId(myNewSce->getGameMasterId());

        QDateTime time = QDateTime::currentDateTime();


        gamemaster->setBackTime(time.addSecs(myNewSce->getDuration()*60));
        gamemaster->setCurrentActivity(GameMaster::INGAME);


    }
}
void ScenarioManager::scenarioIsDone()
{
    QModelIndex index = getFocusedListView()->currentIndex();

    if(index.isValid())
    {
        QVariant var = index.data(Qt::UserRole);
        Scenario sce = var.value<Scenario>();
        //
        ScenarioModel* model = getRightModel(sce.getState());
        ////////////////////////


        Scenario* mySce = model->getScenarioById(sce.getScenarioId());
        model->removeScenario(mySce);
        mySce->setState(Scenario::DONE);
        model = getRightModel(mySce->getState());
        model->appendScenario(mySce);

        GameMaster* gamemaster = getGameMasterFromId(mySce->getGameMasterId());

        QDateTime time;
        gamemaster->setBackTime(time);
        gamemaster->setCurrentActivity(GameMaster::FREE);

    }
}
void ScenarioManager::editScenario()
{
    QModelIndex index = getFocusedListView()->currentIndex();

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
        default:
            return false;
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
bool ScenarioManager::eventFilterForDone(QEvent * /*ent*/)
{
    return false;
}
bool ScenarioManager::eventFilterForRunning(QEvent * event)
{
    if (event->type() == QEvent::KeyPress)
    {
        QKeyEvent* keyEvent = static_cast<QKeyEvent*>(event);
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
        default:
            return false;
        }

        return true;
    }
    if(event->type() == QEvent::ContextMenu)
    {
        QContextMenuEvent* menuEvent = static_cast<QContextMenuEvent*>(event);
        showContextMenu(menuEvent,Scenario::RUNNING);
        return true;
    }
    return false;
}

QListView* ScenarioManager::getFocusedListView()
{

    if(m_ui->m_scenarioAvailabeView->hasFocus())
    {
        return m_ui->m_scenarioAvailabeView;
    }
    else if(m_ui->m_scenarioDoneView->hasFocus())
    {
        return m_ui->m_scenarioDoneView;
    }
    else if(m_ui->m_scenarioRunningView->hasFocus())
    {
        return m_ui->m_scenarioRunningView;
    }
    return NULL;
}
void ScenarioManager::readFromData(QDataStream& from)
{
    m_doneScenarioModel->readFromData(from);
}
void ScenarioManager::writeToData(QDataStream& to) const
{
    m_doneScenarioModel->writeToData(to);
}

QDomElement ScenarioManager::writeDataToXml(QDomDocument& t)
{
    QDomElement scenarioList =  t.createElement("scenarioManager");
    scenarioList.appendChild(m_doneScenarioModel->writeDataToXml(t));
    return scenarioList;
}

void ScenarioManager::readDataFromXml(QDomNode& t)
{
    m_doneScenarioModel->readDataFromXml(t);
}
GameMaster* ScenarioManager::getGameMasterFromId(QString id)
{
    return m_masterList[id];
}
void ScenarioManager::resetData()
{
    m_availableScenarioModel->resetData();
    m_doneScenarioModel->resetData();
    m_runningScenarioModel->resetData();

    m_list.clear();
    m_masterList.clear();


}
