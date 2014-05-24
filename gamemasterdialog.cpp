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
#include "gamemasterdialog.h"
#include "ui_gamemasterdialog.h"
#include <QDebug>


GameMasterDialog::GameMasterDialog(QMap<QString,Game*>& l,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GameMasterDialog)
{

    m_addScenarioAct=new QAction(tr("Add"),this);
    m_delScenarioAct=new QAction(tr("Del"),this);

    ui->setupUi(this);
    m_model = new ScenarioModel(Scenario::AVAILABLE);
    ui->m_scenarioTable->setModel(m_model);
    ui->m_deleteButton->setDefaultAction(m_delScenarioAct);
    ui->m_newButton->setDefaultAction(m_addScenarioAct);

    m_gameDelegate = new GameEditorDelegate(l);

    ui->m_scenarioTable->setItemDelegateForColumn(0,m_gameDelegate);

#if QT_VERSION >= 0x050000
    ui->m_scenarioTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Interactive);
#else
    ui->m_scenarioTable->horizontalHeader()->setResizeMode(QHeaderView::Interactive);
#endif
    ui->m_scenarioTable->horizontalHeader()->setStretchLastSection(true);
//    ui->m_scenarioTable->horizontalHeader()->setCascadingSectionResizes(true);

    ui->m_scenarioTable->verticalHeader()->setVisible(false);



    connect(m_addScenarioAct,SIGNAL(triggered()),this,SLOT(addScenario()));
    connect(m_model,SIGNAL(updateHeader()),this,SLOT(updateGameListHeader()));
}

GameMasterDialog::~GameMasterDialog()
{
    delete ui;
}


QString GameMasterDialog::getName()
{
return ui->m_nameEdit->text();
}

QString GameMasterDialog::getNickName()
{
return ui->m_nickNameEdit->text();
}

QString GameMasterDialog::getFirstName()
{
return ui->m_firstNameEdit->text();
}

QString GameMasterDialog::getPhoneNumber()
{
return ui->m_phoneEdit->text();
}

QString GameMasterDialog::getMailAddress()
{
    return ui->m_mailAddress->text();
}
void GameMasterDialog::addScenario()
{
    m_model->appendScenario(new Scenario());
    updateGameListHeader();
}
QList<Scenario*>* GameMasterDialog::getScenarioList()
{
    return m_model->getScenarioList();
}
void GameMasterDialog::setPerformer(QString m_id)
{
     m_model->setPerformer(m_id);

}

void GameMasterDialog::updateGameListHeader()
{
    ui->m_scenarioTable->horizontalHeader()->resizeSections(QHeaderView::ResizeToContents);
}
