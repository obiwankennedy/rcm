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

#include "leveldelegateitem.h"
#include <QColorDialog>

GameMasterDialog::GameMasterDialog(QMap<QString,Game*>& l,QList<Game*>& sortedList,QMap<QString,GameMaster*>& lst,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GameMasterDialog)
{

    m_addScenarioAct=new QAction(tr("Add"),this);
    m_delScenarioAct=new QAction(tr("Del"),this);
    m_addGameAct=new QAction(tr("Add Game"),this);

    ui->setupUi(this);
    m_model = new ScenarioModel(l,lst,Scenario::AVAILABLE);
    ui->m_scenarioTable->setModel(m_model);
    ui->m_deleteButton->setDefaultAction(m_delScenarioAct);
    ui->m_newButton->setDefaultAction(m_addScenarioAct);
    ui->m_addGame->setDefaultAction(m_addGameAct);


    m_gameDelegate = new GameEditorDelegate(sortedList);

    ui->m_scenarioTable->setItemDelegateForColumn(0,m_gameDelegate);
    ui->m_scenarioTable->setItemDelegateForColumn(3,new LevelDelegateItem());

    ui->m_scenarioTable->hideColumn(8);
    ui->m_scenarioTable->hideColumn(7);
    ui->m_scenarioTable->hideColumn(9);
    ui->m_scenarioTable->hideColumn(10);
    updateGameListHeader();
    ui->m_scenarioTable->verticalHeader()->setVisible(false);
    connect(m_addScenarioAct,SIGNAL(triggered()),this,SLOT(addScenario()));
    connect(m_model,SIGNAL(updateHeader()),this,SLOT(updateGameListHeader()));
    connect(ui->m_addGame,SIGNAL(pressed()),this,SIGNAL(addGame()));

    connect(ui->m_color,&QPushButton::clicked,this,[=]()
    {
      m_currentColor = QColorDialog::getColor(m_currentColor,this,tr("GM color"));
      ui->m_color->setStyleSheet(QStringLiteral("background: rgb(%1,%2,%3);").arg(m_currentColor.red()).arg(m_currentColor.green()).arg(m_currentColor.blue()));
    });
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
    //ui->m_scenarioTable->horizontalHeader()->resizeSections(QHeaderView::ResizeToContents);
    ui->m_scenarioTable->horizontalHeader()->resizeSection(0,150);//Game
    ui->m_scenarioTable->horizontalHeader()->resizeSection(1,150);//title
    ui->m_scenarioTable->horizontalHeader()->setSectionResizeMode(1,QHeaderView::Stretch);
    ui->m_scenarioTable->horizontalHeader()->resizeSection(2,80);//Duration
    ui->m_scenarioTable->horizontalHeader()->resizeSection(3,50);//level
    ui->m_scenarioTable->horizontalHeader()->resizeSection(4,50);//min
    ui->m_scenarioTable->horizontalHeader()->resizeSection(5,50);//max
    ui->m_scenarioTable->horizontalHeader()->setSectionResizeMode(6,QHeaderView::Stretch);
    //ui->m_scenarioTable->setColumnWidth(0,300);//Description
   // ui->m_scenarioTable->setColumnWidth(0,150);//current Player


}

QColor GameMasterDialog::getCurrentColor() const
{
  return m_currentColor;
}

void GameMasterDialog::setCurrentColor(const QColor &currentColor)
{
  m_currentColor = currentColor;
  ui->m_color->setStyleSheet(QStringLiteral("background: rgb(%1,%2,%3);").arg(m_currentColor.red()).arg(m_currentColor.green()).arg(m_currentColor.blue()));
}
void GameMasterDialog::setName(QString str)
{
  ui->m_nameEdit->setText(str);
}

void GameMasterDialog::setNickName(QString str)
{
  ui->m_nickNameEdit->setText(str);
}

void GameMasterDialog::setFirstName(QString str)
{
ui->m_firstNameEdit->setText(str);
}

void GameMasterDialog::setPhoneNumber(QString str)
{
ui->m_phoneEdit->setText(str);
}

void GameMasterDialog::setMailAddress(QString str)
{
    ui->m_mailAddress->setText(str);
}
void GameMasterDialog::setScenarioList(QList<Scenario*>* lst)
{

    m_model->addDataList(lst);
     updateGameListHeader();
}
