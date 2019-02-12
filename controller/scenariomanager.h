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

#include <QLabel>
#include <QList>
#include <QListView>
#include <QObject>
#include <QScrollArea>
#include <QSortFilterProxyModel>

#include "customerview.h"
#include "gameimageprovider.h"
#include "gamemaster.h"
#include "scenario.h"
#include "scenarioitemdelegate.h"
#include "scenariomodel.h"

#include "serializable.h"

namespace Ui
{
    class MainWindow;
}
class GameMasterModel;
class SortedScenario : public QSortFilterProxyModel
{
    Q_OBJECT
public:
    SortedScenario(QObject* parent= nullptr);

    QString filter() const;
public slots:
    void setFilter(const QString& filter);

protected:
    // bool lessThan(const QModelIndex& left, const QModelIndex& right) const override;
    bool filterAcceptsRow(int sourceRow, const QModelIndex& sourceParent) const override;

private:
    QString m_filter;
};

class ScenarioManager : public QObject, public Serialisable
{
    Q_OBJECT
public:
    explicit ScenarioManager(Ui::MainWindow* ui, QList<Game*>& sortedList, GameModel* gameModel,
        QMap<QString, Game*>& map, GameMasterModel* masters, GameImageProvider* gameImgProvider,
        QObject* parent= nullptr);
    virtual ~ScenarioManager();

    void addScenarios(QList<Scenario*>* l);

    void addScenario(Scenario* l);

    void removeScenarioFromList(QList<Scenario*>* l);

    virtual void readDataFromJson(QJsonObject&);
    virtual void writeDataToJson(QJsonObject&);

    GameMaster* getGameMasterFromId(QString id);
    bool isPlayersAreRegistred() const;

    bool isCustomViewDisplayed();
    void setLabel(Ui::MainWindow* wid);

protected:
    bool eventFilter(QObject* obj, QEvent* event);
    bool eventFilterForAvailable(QEvent*);
    bool eventFilterForListPlaning(QEvent* ent);
    bool mouseMoveOnScenarioListOnPlanning(QMouseEvent* event);
public slots:
    void showCustomView(bool);
    void setCustomViewVisible(bool);
    void increaseCurrentPlayerCount();
    void decreaseCurrentPlayerCount();
    void startScenario();
    void editScenario();
    // void scenarioIsDone();
    void resetData();
    void showPlayerInfo();
    void toggleFullScreen();
    void setRegistrerPlayer(bool);
    void closeView();

    void checkAllGM();

    void invertSelection();

private:
    ScenarioModel* m_availableScenarioModel= nullptr;
    SortedScenario* m_proxyModel= nullptr;
    GameModel* m_gameModel= nullptr;
    GameMasterModel* m_gameMasterModel= nullptr;

    ScenarioItemDelegate* m_avScenarioDelegate= nullptr;

    Ui::MainWindow* m_ui= nullptr;
    QMap<QString, Game*>& m_list;
    // QMap<QString, GameMaster*>& m_masterList;
    QList<Game*>& m_sortedList;
    CustomerView* m_customerView;

    // Actions
    QAction* m_increasePlayersCount= nullptr;
    QAction* m_decreasePlayersCount= nullptr;
    QAction* m_startScenario= nullptr;
    QAction* m_editScenario= nullptr;
    QAction* m_scenarioIsFinished= nullptr;
    QAction* m_showPlayersInfo= nullptr;

    bool m_registrerPlayerInfo;
};

#endif // SCENARIOMANAGER_H
