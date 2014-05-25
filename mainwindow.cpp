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
#include <QFile>
#include <QFileInfo>
#include <QFileDialog>
#include <QCloseEvent>



#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "gamedialog.h"
#include "gamemaster.h"

#include "gamemasterdialog.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_title=tr("%1[*] - Rolisteam Convention Manager");

    setWindowTitle(m_title.arg("Unkown"));

    m_gameModel = new GameModel();
    m_gameMasterModel = new GameMasterModel();
    //m_gameMasterPresenceModel = new GameMasterModel();

    m_preferences = PreferencesManager::getInstance();

    ui->m_gameView->setModel(m_gameModel);
    ui->m_masterView->setModel(m_gameMasterModel);
    m_scenarioManager = new ScenarioManager(ui,m_gameModel->getGameMap(),m_gameMasterModel->getMasterMap());
    initActions();

    ui->m_gameView->setSelectionMode(QAbstractItemView::ExtendedSelection);


}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::initActions()
{
    m_addGameAct = new QAction(tr("Add"),this);
    m_removeGameAct= new QAction(tr("Del"),this);
    m_removeGMAct= new QAction(tr("Del"),this);
    m_addGMAct= new QAction(tr("Add"),this);

    ui->m_addGameButton->setDefaultAction(m_addGameAct);
    ui->m_addGMButton->setDefaultAction(m_addGMAct);
    ui->m_deleteGameButton->setDefaultAction(m_removeGameAct);
    ui->m_deleteGMButton->setDefaultAction(m_removeGMAct);

    connect(m_addGameAct,SIGNAL(triggered()),this,SLOT(addGameDialog()));
    connect(m_addGMAct,SIGNAL(triggered()),this,SLOT(addGameMasterDialog()));
    connect(m_gameMasterModel,SIGNAL(gmHasBeenAdded(GameMaster*)),this,SLOT(addGmScenarioListToGlobalList(GameMaster*)));
    connect(m_gameMasterModel,SIGNAL(gameMasterStatusHasChanged(GameMaster*,bool)),this,SLOT(statusGmHasChanged(GameMaster*,bool)));






    // init menu
    connect(ui->m_openAct,SIGNAL(triggered()),this,SLOT(openData()));
    connect(ui->m_quitAct,SIGNAL(triggered()),this,SLOT(close()));
    connect(ui->m_saveAct,SIGNAL(triggered()),this,SLOT(saveData()));
    connect(ui->m_saveAsAct,SIGNAL(triggered()),this,SLOT(saveAsData()));

    connect(ui->m_customerViewDisplayAct,SIGNAL(triggered(bool)),m_scenarioManager,SLOT(showCustomView(bool)));

}
void  MainWindow::addGameDialog()
{
    GameDialog dialog;

    if(dialog.exec())
    {
        Game* tmp = new Game();
        tmp->setTitle(dialog.getTitle());
        tmp->setPunchLine(dialog.getPunchLine());
        tmp->setDescription(dialog.getDescription());

        m_gameModel->append(tmp);

    }

}
void MainWindow::closeEvent ( QCloseEvent * event )
{

    if (maybeSave()) {
             writeSettings();
             event->accept();
         } else {
             event->ignore();
         }
}
bool MainWindow::maybeSave()
{
    return true;
}
void MainWindow::readFile()
{
    QFile file(m_currentDataPath);
    setWindowTitle(m_title.arg(m_currentDataPath));
    if (file.open(QIODevice::ReadOnly))
    {
        QDataStream in(&file);
        m_gameModel->readFromData(in);
        m_gameMasterModel->readFromData(in);
        file.close();

    }
}
void MainWindow::saveData()
{
    if (m_currentDataPath.isNull())
    {
            saveAsData();
    }

    if(!m_currentDataPath.endsWith(".rcdb"))
    {
            m_currentDataPath += ".rcdb";
    }

    QFile file(m_currentDataPath);

    QFileInfo fileinfo(file);
    m_preferences->registerValue("dataDirectory",fileinfo.absoluteDir().canonicalPath());

    if (file.open(QIODevice::WriteOnly))
    {
        QDataStream in(&file);
// write data
        m_gameModel->writeToData(in);
        m_gameMasterModel->writeToData(in);

        file.close();
    }
}
void MainWindow::saveAsData()
{
    m_currentDataPath = QFileDialog::getSaveFileName(this, tr("Save Data"), m_preferences->value("dataDirectory",QDir::homePath()).toString(), tr("Rolisteam Conv Database (*.rcdb)"));
    if(!m_currentDataPath.isNull())
    {
        saveData();
    }
}
void MainWindow::openData()
{
    m_currentDataPath = QFileDialog::getOpenFileName(this, tr("Open Data"), m_preferences->value("dataDirectory",QDir::homePath()).toString(), tr("Rolisteam Conv Database (*.rcdb)"));
    if(!m_currentDataPath.isNull())
    {
        if(!m_currentDataPath.endsWith(".rcdb"))
        {
                m_currentDataPath += ".rcdb";
        }

        readFile();
    }
}
void MainWindow::readSettings()
{

}

void MainWindow::writeSettings()
{

}
void MainWindow::addGameMasterDialog()
{
    GameMasterDialog dialog(m_gameModel->getGameMap());
    dialog.setWindowFlags(Qt::Window );

    if(dialog.exec())
    {
        GameMaster* tmp = new GameMaster();

        tmp->setName(dialog.getName());
        tmp->setNickName(dialog.getNickName());
        tmp->setFirstName(dialog.getFirstName());
        tmp->setPhoneNumber(dialog.getPhoneNumber());
        tmp->setMailAddress(dialog.getMailAddress());


        //dialog.get

        m_gameMasterModel->append(tmp);
        dialog.setPerformer(tmp->getId());
        QList<Scenario*>* list = dialog.getScenarioList();

        //All scenario are Available
        tmp->setGMScenario(list);

        //m_scenarioManager->addScenarios(list);


    }
}

void MainWindow::addGmScenarioListToGlobalList(GameMaster* l)
{
    if(l->isPresent())
    {
        m_scenarioManager->addScenarios(l->getGMScenarios());
    }
}
void MainWindow::statusGmHasChanged(GameMaster* l,bool b)
{
    if(b)
    {
        addGmScenarioListToGlobalList(l);
    }
    else
    {
        m_scenarioManager->removeScenarioFromList(l->getGMScenarios());
    }
}
