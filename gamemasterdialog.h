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
#ifndef GAMEMASTERDIALOG_H
#define GAMEMASTERDIALOG_H

#include <QDialog>


#include "scenariomodel.h"
#include "gameeditordelegate.h"

namespace Ui {
class GameMasterDialog;
}

class GameMasterDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit GameMasterDialog(QMap<QString,Game*>& l,QList<Game*>& sortedList,QMap<QString,GameMaster*>& lst,QWidget *parent = 0);
    ~GameMasterDialog();

    QString getName();
    QString getNickName();
    QString getFirstName();
    QString getPhoneNumber();
    QString getMailAddress();

    void setName(QString str);
    void setNickName(QString str);
    void setFirstName(QString str);
    void setPhoneNumber(QString str);
    void setMailAddress(QString str);

    void setScenarioList(QList<Scenario*>* lst);

    QList<Scenario*>* getScenarioList();
    void setPerformer(QString m_id);
signals:
    void addGame();

public slots:
    void addScenario();
    void updateGameListHeader();


private:
    Ui::GameMasterDialog *ui;
    ScenarioModel* m_model;


    QAction* m_addScenarioAct;
    QAction* m_delScenarioAct;
    QAction* m_addGameAct;
    GameEditorDelegate* m_gameDelegate;
};

#endif // GAMEMASTERDIALOG_H
