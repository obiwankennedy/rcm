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
#include "model/gamemastermodel.h"
#include "playerinformationformdialog.h"
#include "playersinformationdialog.h"
#include "scenarioeditordialog.h"
#include "ui_mainwindow.h"

#include <QContextMenuEvent>
#include <QDebug>
#include <QHeaderView>
#include <QInputDialog>

ScenarioManager::ScenarioManager(Ui::MainWindow* ui, QList<Game*>& sortedList, GameModel* gameModel,
    QMap<QString, Game*>& map, GameMasterModel* masters, GameImageProvider* gameImgProvider, QObject* parent)
    : QObject(parent)
    , m_gameModel(gameModel)
    , m_gameMasterModel(masters)
    , m_ui(ui)
    , m_list(map)
    , m_sortedList(sortedList)
    , m_registrerPlayerInfo(true)
{
    // model
    m_availableScenarioModel
        = new ScenarioModel(m_list, gameModel, m_gameMasterModel->getMasterMap(), Scenario::AVAILABLE);
    m_availableScenarioModel->disableEdition();

    m_proxyModel= new SortedScenario(this);
    m_proxyModel->setSourceModel(m_availableScenarioModel);
    connect(m_ui->m_filterEdit, &QLineEdit::textChanged, m_proxyModel, &SortedScenario::setFilter);

    m_customerView= new CustomerView(gameImgProvider, m_proxyModel);
    m_ui->m_customerViewDisplayAct->setEnabled(true);
    m_ui->m_customerViewDisplayAct->setVisible(true);

    // view
    m_ui->m_availableScenario->setList(&m_list);
    connect(m_ui->m_availableScenario, &ScenarioListView::updateSorting, m_proxyModel, &SortedScenario::invalidate);

    m_ui->m_availableScenario->setModel(m_proxyModel);

    connect(m_ui->m_availableScenario, &QTableView::clicked, m_customerView, &CustomerView::setSelectionIndex);

    auto header= m_ui->m_availableScenario->horizontalHeader();
    // header->hideSection(0);
    header->hideSection(0);
    header->hideSection(2);
    header->hideSection(3);
    header->hideSection(4);
    header->hideSection(5);
    header->hideSection(6);
    header->hideSection(7);
    header->hideSection(8);
    header->hideSection(9);
    header->hideSection(10);
    header->hideSection(10);

    header->moveSection(11, 1);
    header->moveSection(12, 2);
    header->setSectionResizeMode(1, QHeaderView::Stretch);

    // Actions
    m_increasePlayersCount= new QAction(tr("+1 player"), this);
    m_increasePlayersCount->setShortcut(Qt::Key_Plus);

    m_decreasePlayersCount= new QAction(tr("-1 player"), this);
    m_decreasePlayersCount->setShortcut(Qt::Key_Minus);

    m_startScenario= new QAction(tr("Start"), this);
    m_editScenario= new QAction(tr("Edit..."), this);

    m_scenarioIsFinished= new QAction(tr("Finish"), this);

    m_showPlayersInfo= new QAction(tr("Show Players Info"), this);

    // connect
    connect(m_increasePlayersCount, SIGNAL(triggered()), this, SLOT(increaseCurrentPlayerCount()));
    connect(m_decreasePlayersCount, SIGNAL(triggered()), this, SLOT(decreaseCurrentPlayerCount()));
    connect(m_startScenario, SIGNAL(triggered()), this, SLOT(startScenario()));
    connect(m_editScenario, SIGNAL(triggered()), this, SLOT(editScenario()));

    connect(m_showPlayersInfo, SIGNAL(triggered()), this, SLOT(showPlayerInfo()));

    m_avScenarioDelegate= new ScenarioItemDelegate(m_list, m_gameMasterModel->getMasterMap(), Scenario::AVAILABLE);
    // m_ui->m_availableScenario->setItemDelegate(m_avScenarioDelegate);
}
ScenarioManager::~ScenarioManager()
{
    /*m_customerView->close();
    if(nullptr!=m_customerView)
        delete m_customerView;*/
}
bool ScenarioManager::eventFilter(QObject* obj, QEvent* event)
{
    bool retValue= false;
    if(obj == m_ui->m_availableScenario)
    {
        retValue= eventFilterForListPlaning(event);
    }

    if(!retValue)
    {
        return QObject::eventFilter(obj, event);
    }
    else
    {
        return retValue;
    }
}
void ScenarioManager::setRegistrerPlayer(bool b)
{
    m_registrerPlayerInfo= b;
}
bool ScenarioManager::isPlayersAreRegistred() const
{
    return m_registrerPlayerInfo;
}

void ScenarioManager::addScenarios(QList<Scenario*>* l)
{
    for(Scenario* tmp : *l)
    {
        addScenario(tmp);
    }
}
#include "localisation/rcmmimedata.h"
#include <QDrag>
bool ScenarioManager::mouseMoveOnScenarioListOnPlanning(QMouseEvent* event)
{
    QModelIndex tmp= m_ui->m_availableScenario->indexAt(event->pos());

    if((event->buttons() == Qt::LeftButton) && (tmp.isValid()))
    {
        QVariant var= tmp.data(Qt::UserRole);
        Scenario sce= var.value<Scenario>();

        Scenario* trueScenario= new Scenario();
        trueScenario->setReferenceScenario(&sce);

        QDrag* drag= new QDrag(this);
        RcmMimeData* mimeData= new RcmMimeData();

        mimeData->setScenario(trueScenario);
        drag->setMimeData(mimeData);
        auto game= m_list.value(trueScenario->getGameId());
        if(nullptr != game)
        {
            // drag->setPixmap(game->getPixmap());
        }

        Qt::DropAction dropAction= drag->exec();
        Q_UNUSED(dropAction);
    }
    return true;
}
void ScenarioManager::addScenario(Scenario* l)
{
    l->setState(Scenario::AVAILABLE);
    m_availableScenarioModel->appendScenario(l);
}

void ScenarioManager::showCustomView(bool b)
{
    m_customerView->setVisible(b);
}
void ScenarioManager::setCustomViewVisible(bool b)
{
    m_customerView->setVisible(b);
}

bool ScenarioManager::isCustomViewDisplayed()
{
    return m_customerView->isVisible();
}

void ScenarioManager::setLabel(Ui::MainWindow* wid)
{
    m_customerView->setLabel(wid);
}

void ScenarioManager::removeScenarioFromList(QList<Scenario*>* l)
{
    foreach(Scenario* tmp, *l)
    {
        m_availableScenarioModel->removeScenario(tmp);
    }
}

void ScenarioManager::invertSelection()
{
    for(auto gm : m_gameMasterModel->getMasterList())
    {
        m_gameMasterModel->setPresence(gm, !gm->isPresent());
    }
} // slots to perform action
/*void ScenarioManager::showContextMenu(QContextMenuEvent* event, Scenario::STATE m)
{
    QModelIndex index= getFocusedListView()->indexAt(event->pos());

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
    menu.addSeparator();
    menu.addAction(m_showPlayersInfo);

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
}*/
void ScenarioManager::increaseCurrentPlayerCount()
{
    QModelIndex index= m_ui->m_availableScenario->currentIndex();

    if(index.isValid())
    {
        QVariant var= index.data(Qt::UserRole);
        Scenario sce= var.value<Scenario>();
        ScenarioModel* model= m_availableScenarioModel;
        PlayerInformationFormDialog dialog(m_ui->m_availableScenario);

        if(dialog.exec())
        {
            auto name= dialog.name();
            auto first= dialog.firstName();
            auto phone= dialog.phone();
            auto count= dialog.getPlayerCount();
            QStringList list({first, name, phone, QString::number(count)});
            model->setData(index, list.join(';'), ScenarioModel::AddPlayerInfo);
            model->setData(index, count, ScenarioModel::IncreaseRole);
        }
    }
}
void ScenarioManager::decreaseCurrentPlayerCount()
{
    QModelIndex index= m_ui->m_availableScenario->currentIndex();
    if(index.isValid())
    {
        QInputDialog dialog;

        QVariant var= index.data(Qt::UserRole);
        Scenario sce= var.value<Scenario>();
        QStringList list= sce.getPlayerInformation();
        list.prepend(tr("No body"));
        dialog.setComboBoxItems(list);
        // dialog.setInputMode(QInputDialog::TextInput);
        ScenarioModel* model= m_availableScenarioModel;
        if(dialog.exec())
        {
            list.removeAt(0);
            QString textVal= dialog.textValue();
            if(list.contains(textVal))
            {
                qDebug() << textVal << list;
                list.removeOne(textVal);
                qDebug() << "after remove" << textVal << list;

                QVariant var2= list;
                model->setData(index, var2, ScenarioModel::SetPlayerInfo);
            }
        }

        model->setData(index, 1, ScenarioModel::DecreaseRole);
    }
}

void ScenarioManager::showPlayerInfo()
{
    QModelIndex index= m_ui->m_availableScenario->currentIndex();

    if(index.isValid())
    {
        QVariant var= index.data(Qt::UserRole);
        Scenario sce= var.value<Scenario>();
        PlayersInformationDialog dialog(m_ui->m_availableScenario);
        dialog.setData(sce.getPlayerInformation());
        dialog.exec();
    }
}
void ScenarioManager::startScenario()
{
    QModelIndex index= m_ui->m_availableScenario->currentIndex();

    if(index.isValid())
    {
        QVariant var= index.data(Qt::UserRole);
        Scenario sce= var.value<Scenario>();

        ScenarioModel* model= m_availableScenarioModel;
        Scenario* mySce= model->getScenarioById(sce.getScenarioId());
        // model->removeScenario(mySce);
        Scenario* myNewSce= new Scenario();
        myNewSce->setReferenceScenario(mySce);
        mySce->reset();
        myNewSce->setState(Scenario::RUNNING);
        model->appendScenario(myNewSce);

        GameMaster* gamemaster= getGameMasterFromId(myNewSce->getGameMasterId());

        QDateTime time= QDateTime::currentDateTime();

        gamemaster->setBackTime(time.addSecs(myNewSce->getDuration() * 60));
        gamemaster->setCurrentActivity(GameMaster::INGAME);
    }
}
void ScenarioManager::closeView()
{
    m_customerView->setVisible(false);
}

/*void ScenarioManager::scenarioIsDone()
{
    QModelIndex index= getFocusedListView()->currentIndex();

    if(index.isValid())
    {
        QVariant var= index.data(Qt::UserRole);
        Scenario sce= var.value<Scenario>();
        //
        ScenarioModel* model= m_availableScenarioModel;
        ////////////////////////

        Scenario* mySce= model->getScenarioById(sce.getScenarioId());
        model->removeScenario(mySce);
        mySce->setState(Scenario::DONE);
        model= getRightModel(mySce->getState());
        model->appendScenario(mySce);

        GameMaster* gamemaster= getGameMasterFromId(mySce->getGameMasterId());

        QDateTime time;
        gamemaster->setBackTime(time);
        gamemaster->setCurrentActivity(GameMaster::FREE);
    }
}*/
void ScenarioManager::editScenario()
{
    QModelIndex index= m_ui->m_availableScenario->currentIndex();

    if(index.isValid())
    {
        QVariant var= index.data(Qt::UserRole);
        Scenario sce= var.value<Scenario>();
        //
        ScenarioModel* model= m_availableScenarioModel;
        model->getScenarioById(sce.getScenarioId());
        ScenarioEditorDialog dialog(m_sortedList);
        dialog.setModel(model);
        dialog.exec();
    }
}
bool ScenarioManager::eventFilterForAvailable(QEvent* event)
{
    if(event->type() == QEvent::KeyPress)
    {
        QKeyEvent* keyEvent= static_cast<QKeyEvent*>(event);
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
    else if(event->type() == QEvent::MouseButtonDblClick)
    {
        editScenario();
        return true;
    }
    else if(event->type() == QEvent::ContextMenu)
    {
        QContextMenuEvent* menuEvent= static_cast<QContextMenuEvent*>(event);
        // showContextMenu(menuEvent, Scenario::AVAILABLE);
        return true;
    }
    else
    {
        return false;
    }
}

bool ScenarioManager::eventFilterForListPlaning(QEvent* ent)
{
    if(ent->type() == QEvent::MouseMove)
    {
        QMouseEvent* mouse= dynamic_cast<QMouseEvent*>(ent);
        return mouseMoveOnScenarioListOnPlanning(mouse);
    }

    return false;
}

void ScenarioManager::readDataFromJson(QJsonObject& obj)
{
    // m_doneScenarioModel->readDataFromJson(obj);
}

void ScenarioManager::writeDataToJson(QJsonObject& obj)
{
    // m_doneScenarioModel->writeDataToJson(obj);
}
GameMaster* ScenarioManager::getGameMasterFromId(QString id)
{
    auto list= m_gameMasterModel->getMasterMap();
    return list[id];
}
void ScenarioManager::toggleFullScreen()
{
    if(!(m_customerView->windowState() & Qt::WindowFullScreen))
    {
        m_customerView->showFullScreen();
    }
    else
    {
        m_customerView->showNormal();
    }
}

void ScenarioManager::resetData()
{
    m_availableScenarioModel->resetData();
    m_gameModel->resetData();
    m_gameMasterModel->resetData();
}
void ScenarioManager::checkAllGM()
{
    int gmPresentCount= 0;
    int gmAwayCount= 0;
    auto list= m_gameMasterModel->getMasterList();
    for(auto& gm : list)
    {
        if(gm->isPresent())
            ++gmPresentCount;
        else
            ++gmAwayCount;
    }

    auto check= true;
    if(list.size() == gmAwayCount)
        check= true;
    else if(list.size() == gmPresentCount)
        check= false;

    for(auto& gm : list)
    {
        m_gameMasterModel->setPresence(gm, check);
        if(check)
            addScenarios(gm->getGMScenarios());
        else
        {
            removeScenarioFromList(gm->getGMScenarios());
        }
    }
    m_ui->m_masterView->update();
}
/********************
 *
 * sorted scenario
 *
 * *////////////////

SortedScenario::SortedScenario(QObject* parent) : QSortFilterProxyModel(parent)
{
    setDynamicSortFilter(true);
}
/*bool SortedScenario::lessThan(const QModelIndex& left, const QModelIndex& right) const
{
    auto leftCount= sourceModel()->data(left, ScenarioModel::GameCount).toInt();
    auto rightCount= sourceModel()->data(right, ScenarioModel::GameCount).toInt();

    if(leftCount < rightCount)
    {
        return leftCount < rightCount;
    }
    else
    {
        auto leftGameName= sourceModel()->data(left, ScenarioModel::GameMasterNameRole).toString();
        auto rightGameName= sourceModel()->data(right, ScenarioModel::GameMasterNameRole).toString();
        return leftGameName < rightGameName;
    }
}*/

bool SortedScenario::filterAcceptsRow(int sourceRow, const QModelIndex& sourceParent) const
{
    if(m_filter.isEmpty())
        return true;
    QModelIndex index0= sourceModel()->index(sourceRow, 0, sourceParent);

    auto gameTitle= index0.data(ScenarioModel::GameTitleRole).toString();
    auto gmName= index0.data(ScenarioModel::GameMasterNameRole).toString();
    auto scenario= index0.data(ScenarioModel::TitleRole).toString();

    return gameTitle.contains(m_filter, Qt::CaseInsensitive) || gmName.contains(m_filter, Qt::CaseInsensitive)
           || scenario.contains(m_filter, Qt::CaseInsensitive);
}

QString SortedScenario::filter() const
{
    return m_filter;
}

void SortedScenario::setFilter(const QString& filter)
{
    if(filter == m_filter)
        return;
    m_filter= filter;
    invalidateFilter();
}
