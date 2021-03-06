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
#include <QLabel>
#include <QListView>
#include <QScrollArea>

#include "scenario.h"
#include "scenariomodel.h"
#include "scenarioitemdelegate.h"
#ifdef __QT_QUICK_2_
#include "customerview.h"
#include "gameimageprovider.h"
#endif
#include "gamemaster.h"

#include "serializable.h"


namespace Ui {
class MainWindow;
}

class ScenarioManager : public QObject, public Serialisable
{
    Q_OBJECT
public:
    #ifdef __QT_QUICK_2_
    explicit ScenarioManager(Ui::MainWindow* ui,QList<Game*>& sortedList,QMap<QString,Game*>& map,QMap<QString,GameMaster*>& mastermap,GameImageProvider* gameImgProvider,QObject *parent = 0);
#else
    explicit ScenarioManager(Ui::MainWindow* ui,QList<Game*>& sortedList,QMap<QString,Game*>& map,QMap<QString,GameMaster*>& mastermap,QObject *parent = 0);
#endif
    virtual ~ScenarioManager();
    
    void addScenarios(QList<Scenario*>* l,Scenario::STATE s = Scenario::AVAILABLE);
    
    void addScenario(Scenario* l,Scenario::STATE s = Scenario::AVAILABLE);
    
    void removeScenarioFromList(QList<Scenario*>* l);
    
    ScenarioModel* getRightModel(Scenario::STATE m);
    QListView* getFocusedListView();


    virtual void readFromData(QDataStream&);
    virtual void writeToData(QDataStream&) const;

    virtual void readDataFromJson(QJsonObject&);
    virtual void writeDataToJson(QJsonObject&);

    virtual QDomElement writeDataToXml(QDomDocument&);
    virtual void readDataFromXml(QDomNode&);


    GameMaster* getGameMasterFromId(QString id);
    bool isPlayersAreRegistred() const;
    
    bool isCustomViewDisplayed();
    void setLabel(Ui::MainWindow* wid);
protected:
    bool eventFilter(QObject *obj, QEvent *event);
    void showContextMenu(QContextMenuEvent* event,Scenario::STATE m);
    bool eventFilterForAvailable(QEvent* );
    bool eventFilterForRunning(QEvent* );
    bool eventFilterForDone(QEvent* );
    bool eventFilterForListPlaning(QEvent *ent);
    bool mouseMoveOnScenarioListOnPlanning(QMouseEvent *event);
public slots:
    void showCustomView(bool);
    void setCustomViewVisible(bool);
    void increaseCurrentPlayerCount();
    void decreaseCurrentPlayerCount();
    void startScenario();
    void editScenario();
    void scenarioIsDone();
    void resetData();
    void showPlayerInfo();
    void toggleFullScreen();
    void setRegistrerPlayer(bool);
    void closeView();
    
    
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
    QList<Game*>& m_sortedList;
    #ifdef __QT_QUICK_2_
    CustomerView* m_customerView;
    #endif
    
    //Actions
    QAction* m_increasePlayersCount;
    QAction* m_decreasePlayersCount;
    QAction* m_startScenario;
    QAction* m_editScenario;
    QAction* m_scenarioIsFinished;
    QAction* m_showPlayersInfo;

    bool m_registrerPlayerInfo;
    
};

#endif // SCENARIOMANAGER_H
