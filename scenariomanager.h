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


class ScenarioManager : public QObject
{
    Q_OBJECT
public:
    explicit ScenarioManager(QObject *parent = 0);
    

    void addAvailableScenarios(QList<Scenario*>* l);
    void addRunningScenarios(QList<Scenario*>* l);
    void addDoneScenarios(QList<Scenario*>* l);
    
    void addOneAvailableScenario(Scenario* l);
    void addOneRunningScenario(Scenario* l);
    void addOneDoneScenario(Scenario* l);

private:
    QList<Scenario*>* m_availableScenarioList;
    QList<Scenario*>* m_runningScenarioList;
    QList<Scenario*>* m_doneScenarioList;
};

#endif // SCENARIOMANAGER_H
