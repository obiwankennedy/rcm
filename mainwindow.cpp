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
#include <QDebug>
#include <QFileInfo>
#include <QFileDialog>
#include <QCloseEvent>
#include <QInputDialog>
#include <QMessageBox>

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "gamedialog.h"
#include "gamemaster.h"

#include "gamemasterdialog.h"
#include "localisation/localisationview.h"

#include "export/exportcsv.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_gameImgProvider = new GameImageProvider();

    m_title=tr("%1[*] - Rolisteam Convention Manager");
    m_recentFileActions = new QList<QAction*>();

    setWindowTitle(m_title.arg("Unkown"));

    m_gameModel = new GameModel(m_gameImgProvider);

    m_gameMasterModel = new GameMasterModel();
    //m_gameMasterPresenceModel = new GameMasterModel();

    m_preferences = PreferencesManager::getInstance();

    ui->m_gameView->setModel(m_gameModel);
    ui->m_masterView->setModel(m_gameMasterModel);

    m_scenarioManager = new ScenarioManager(ui,m_gameModel->getGameList(),m_gameModel->getGameMap(),m_gameMasterModel->getMasterMap(),m_gameImgProvider);


    initActions();

    ui->m_gameView->setSelectionMode(QAbstractItemView::ExtendedSelection);

    readSettings();

    m_recentFile=new QMenu(tr("Recent Files"));
    refreshOpenedFile();
    ui->m_fileMenu->insertMenu(ui->m_quitAct,m_recentFile);
    ui->m_fileMenu->insertSeparator(ui->m_quitAct);

    ui->m_masterView->installEventFilter(this);
    LocalisationView* locview = new LocalisationView(ui->m_timeLine);


    connect(ui->m_properties,SIGNAL(clicked(bool)),locview,SLOT(setProperties()));
   // ui->m_tabWidget->addTab(,tr("Tables"));


    //setAttribute( Qt::WA_DeleteOnClose);
    //clear selection connect
    connect(ui->m_gameView,SIGNAL(clicked(QModelIndex)),this,SLOT(clearSelection(QModelIndex)));
    connect(ui->m_masterView,SIGNAL(clicked(QModelIndex)),this,SLOT(clearSelection(QModelIndex)));
    connect(ui->m_scenarioAvailabeView,SIGNAL(clicked(QModelIndex)),this,SLOT(clearSelection(QModelIndex)));
    connect(ui->m_scenarioDoneView,SIGNAL(clicked(QModelIndex)),this,SLOT(clearSelection(QModelIndex)));
    connect(ui->m_scenarioRunningView,SIGNAL(clicked(QModelIndex)),this,SLOT(clearSelection(QModelIndex)));
    connect(ui->m_exportCSVAct,SIGNAL(triggered()),this,SLOT(exporCSV()));


}

MainWindow::~MainWindow()
{
    qDebug() << "Destructor MainWindow";
    delete ui;
    delete m_scenarioManager;
}
void MainWindow::initActions()
{
    m_addGameAct = new QAction(tr("Add"),this);
    m_removeGameAct= new QAction(tr("Del"),this);
    m_removeGMAct= new QAction(tr("Del"),this);
    m_addGMAct= new QAction(tr("Add"),this);
    m_makeGMGoneAct = new QAction(tr("GM is leaving"),this);
    connect(m_makeGMGoneAct,SIGNAL(triggered()),this,SLOT(makeGameMasterUnavailable()));

    ui->m_addGameButton->setDefaultAction(m_addGameAct);
    ui->m_addGMButton->setDefaultAction(m_addGMAct);
    ui->m_deleteGameButton->setDefaultAction(m_removeGameAct);
    ui->m_deleteGMButton->setDefaultAction(m_removeGMAct);

    connect(m_addGameAct,SIGNAL(triggered()),this,SLOT(addGameDialog()));
    connect(m_addGMAct,SIGNAL(triggered()),this,SLOT(addGameMasterDialog()));

    connect(m_gameMasterModel,SIGNAL(gmHasBeenAdded(GameMaster*)),this,SLOT(addGmScenarioListToGlobalList(GameMaster*)));
    connect(m_gameMasterModel,SIGNAL(gameMasterStatusHasChanged(GameMaster*,bool)),this,SLOT(statusGmHasChanged(GameMaster*,bool)));

    //removal connection
    connect(m_removeGameAct,SIGNAL(triggered()),this,SLOT(removeGame()));
    connect(m_removeGMAct,SIGNAL(triggered()),this,SLOT(removeGameMaster()));









    // init menu
    connect(ui->m_newAct,SIGNAL(triggered()),this,SLOT(resetData()));
    connect(ui->m_openAct,SIGNAL(triggered()),this,SLOT(openData()));
    connect(ui->m_quitAct,SIGNAL(triggered()),this,SLOT(close()));
    connect(ui->m_saveAct,SIGNAL(triggered()),this,SLOT(saveData()));
    connect(ui->m_saveAsAct,SIGNAL(triggered()),this,SLOT(saveAsData()));


    connect(ui->m_newGameAct,SIGNAL(triggered()),this,SLOT(addGameDialog()));
    connect(ui->m_newGmAct,SIGNAL(triggered()),this,SLOT(addGameMasterDialog()));

    connect(ui->m_exportXMLAct,SIGNAL(triggered()),this,SLOT(saveDataToXml()));
    connect(ui->m_importXMLAct,SIGNAL(triggered()),this,SLOT(importDataFromXml()));


    connect(ui->m_customerViewDisplayAct,SIGNAL(triggered(bool)),m_scenarioManager,SLOT(showCustomView(bool)));
    connect(ui->m_showFullScreenAct,SIGNAL(triggered()),m_scenarioManager,SLOT(toggleFullScreen()));


    //edit game and game master
    connect(ui->m_gameView,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(editGame(QModelIndex)));
    connect(ui->m_masterView,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(editGameMaster(QModelIndex)));


}
bool MainWindow::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::ContextMenu)
    {
        QContextMenuEvent *keyEvent = static_cast<QContextMenuEvent *>(event);
        contextMenuForGameMaster(keyEvent);
        return true;
    }
    else
    {
        // standard event processing
        return QObject::eventFilter(obj, event);
    }
}
void MainWindow::contextMenuForGameMaster(QContextMenuEvent* event)
{
    QMenu menu;

    QModelIndex index = ui->m_masterView->indexAt(event->pos());
    menu.addAction(m_addGMAct);
    if(index.isValid())
    {
        menu.addAction(m_removeGMAct);
        menu.addAction(m_makeGMGoneAct);
    }

    menu.exec(event->globalPos());
}

void  MainWindow::addGameDialog()
{
    GameDialog dialog;

    if(dialog.exec())
    {
        Game* tmp = new Game();
        connect(tmp,SIGNAL(pixmapChanged(QString,QPixmap*)),m_gameImgProvider,SLOT(insertPixmap(QString,QPixmap*)));
        tmp->setTitle(dialog.getTitle());
        tmp->setPunchLine(dialog.getPunchLine());
        tmp->setDescription(dialog.getDescription());
        tmp->setType(dialog.getGameType());
        tmp->setImageUrl(dialog.getPixmapUrl());

        m_gameModel->append(tmp);

    }

}
void MainWindow::closeEvent ( QCloseEvent * event )
{

    if (maybeSave())
    {
        writeSettings();
        event->accept();
       // close();
        m_scenarioManager->closeView();
    }
    else
    {
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
    QFileInfo info(m_currentDataPath);


    setWindowTitle(m_title.arg(info.fileName()));
    if (file.open(QIODevice::ReadOnly))
    {
        QDataStream in(&file);
        m_gameModel->readFromData(in);
        m_gameMasterModel->readFromData(in);
        m_scenarioManager->readFromData(in);
        file.close();
        ensureTabVisible(DATA);
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
        m_scenarioManager->writeToData(in);
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
    m_currentDataPath = "/home/renaud/applications/mine/rcm/data.rcdb";
    //m_currentDataPath = QFileDialog::getOpenFileName(this, tr("Open Data"), m_preferences->value("dataDirectory",QDir::homePath()).toString(), tr("Rolisteam Conv Database (*.rcdb)"));
    if(!m_currentDataPath.isNull())
    {
        if(!m_currentDataPath.endsWith(".rcdb"))
        {
            m_currentDataPath += ".rcdb";
        }
        resetData();
        readFile();
        addRecentFile();
    }
}
void MainWindow::readSettings()
{
    QSettings settings("rolisteam","rcm/preferences");
    move(settings.value("pos", QPoint(200, 200)).toPoint());
    resize(settings.value("size", QSize(600, 400)).toSize());
    restoreGeometry(settings.value("geometry").toByteArray());
    restoreState(settings.value("windowState").toByteArray());



    int size = settings.beginReadArray("recentFiles");
    for (int i = size-1; i > -1; --i)
    {
        settings.setArrayIndex(i);
        QFile info(settings.value("path").toString());
        if(info.exists())
        {
            QAction* tmp=new QAction(settings.value("name").toString(),this);
            tmp->setData(settings.value("path"));
            m_recentFileActions->append(tmp);
        }
    }
    settings.endArray();


    m_preferences->readSettings(settings);
}

void MainWindow::writeSettings()
{

    QSettings settings("rolisteam","rcm/preferences");
    settings.setValue("pos", pos());
    settings.setValue("size", size());
    settings.setValue("geometry", saveGeometry());
    settings.setValue("windowState", saveState());


    settings.beginWriteArray("recentFiles");
    qDebug() << "write settings" << m_recentFileActions->size();
    for (int i = 0; i < m_recentFileActions->size(); ++i)
    {
        settings.setArrayIndex(i);
        settings.setValue("name", m_recentFileActions->at(i)->text());
        settings.setValue("path", m_recentFileActions->at(i)->data());
    }
    settings.endArray();



    m_preferences->writeSettings(settings);

}
void MainWindow::openRecentFile()
{
    QAction* tmp = dynamic_cast<QAction*>(sender());
    m_currentDataPath=tmp->data().toString();

    readFile();
    // updateTitle();

}
void MainWindow::addRecentFile()
{
    QFileInfo fileinfo(m_currentDataPath);
    m_preferences->registerValue("MindMapDirectory",fileinfo.absoluteDir().canonicalPath());
    QAction* tmp=new QAction(fileinfo.fileName(),this);
    tmp->setData(fileinfo.absoluteFilePath());
    connect(tmp,SIGNAL(triggered()),this,SLOT(openRecentFile()));

    int size=m_preferences->value("MaxSizeRecentFile",5).toInt();
    if((size<=m_recentFileActions->size())&&(size>0))
    {
        delete m_recentFileActions->at(0);
        m_recentFileActions->removeAt(0);
    }
    m_recentFileActions->append(tmp);
    refreshOpenedFile();
}
void MainWindow::addGameMasterDialog()
{
    GameMasterDialog dialog(m_gameModel->getGameMap(),m_gameModel->getGameList(),m_gameMasterModel->getMasterMap());
    connect(&dialog,SIGNAL(addGame()),this,SLOT(addGameDialog()));
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
void MainWindow::editGame(const QModelIndex& index)
{
    if(index.isValid())
    {
        Game* tmp = m_gameModel->getGameList().at(index.row());
        GameDialog dialog;
        dialog.setTitle(tmp->getTitle());
        dialog.setDescription(tmp->getDescription());
        dialog.setPunchLine(tmp->getPunchLine());
        dialog.setGameType(tmp->getType());
        dialog.setPixmapUrl(tmp->getImageUrl());

        if(dialog.exec())
        {

            tmp->setTitle(dialog.getTitle());
            tmp->setPunchLine(dialog.getPunchLine());
            tmp->setDescription(dialog.getDescription());
            tmp->setImageUrl(dialog.getPixmapUrl());
            tmp->setType(dialog.getGameType());

            //m_gameModel->append(tmp);

        }

    }

}

void MainWindow::editGameMaster(const QModelIndex& index)
{
    if(index.isValid())
    {
        GameMaster* tmp = m_gameMasterModel->getMasterList().at(index.row());
        GameMasterDialog dialog(m_gameModel->getGameMap(),m_gameModel->getGameList(),m_gameMasterModel->getMasterMap());
        connect(&dialog,SIGNAL(addGame()),this,SLOT(addGameDialog()));

        dialog.setName(tmp->getName());
        dialog.setNickName(tmp->getNickName());
        dialog.setMailAddress(tmp->getMailAddress());
        dialog.setFirstName(tmp->getFirstName());
        dialog.setPhoneNumber(tmp->getPhoneNumber());
        dialog.setScenarioList(tmp->getGMScenarios());



        if(dialog.exec())
        {

            tmp->setName(dialog.getName());
            tmp->setNickName(dialog.getNickName());
            tmp->setFirstName(dialog.getFirstName());
            tmp->setPhoneNumber(dialog.getPhoneNumber());
            tmp->setMailAddress(dialog.getMailAddress());




            dialog.setPerformer(tmp->getId());
            QList<Scenario*>* list = dialog.getScenarioList();

            //All scenario are Available
            tmp->setGMScenario(list);

        }

    }
}
void MainWindow::removeGame()
{
    QModelIndex index = ui->m_gameView->currentIndex();
    m_gameModel->removeItem(index);
}

void MainWindow::removeGameMaster()
{
    QModelIndex index = ui->m_masterView->currentIndex();
    m_gameMasterModel->removeItem(index);
}
void MainWindow::refreshOpenedFile()
{
    m_recentFile->clear();
    for (int i = 0; i < m_recentFileActions->size(); ++i)
    {

        m_recentFile->addAction(m_recentFileActions->at(i));
        connect(m_recentFileActions->at(i),SIGNAL(triggered()),this,SLOT(openRecentFile()));
    }

}
void MainWindow::ensureTabVisible(TAB a)
{
    ui->m_tabWidget->setCurrentIndex(a);
}
void MainWindow::saveDataToXml()
{

    QString fileExport = QFileDialog::getSaveFileName(this, tr("Export Data as XML"), m_preferences->value("dataDirectory",QDir::homePath()).toString(), tr("XML Rolisteam Conv Database (*.xml)"));
    if(!fileExport.isNull())
    {


        QFileInfo fileinfo(fileExport);
        if(fileinfo.suffix()!="xml")
        {
            fileExport+=".xml";
        }

         QFile file(fileExport);
        //m_preferences->registerValue("dataDirectory",fileinfo.absoluteDir().canonicalPath());

        if (file.open(QIODevice::WriteOnly))
        {
            QDomDocument doc;
            QDomElement data = doc.createElement("data");

            data.appendChild(m_gameModel->writeDataToXml(doc));
            data.appendChild(m_gameMasterModel->writeDataToXml(doc));
            data.appendChild(m_scenarioManager->writeDataToXml(doc));

            doc.appendChild(data);

            QTextStream in(&file);
            // write data

            doc.save(in,4);
            file.close();

        }

    }

}
void MainWindow::importDataFromXml()
{
    QString fileImport = QFileDialog::getOpenFileName(this, tr("Open XML Data"), m_preferences->value("dataDirectory",QDir::homePath()).toString(), tr("XML Rolisteam Conv Database (*.xml)"));
    if(!fileImport.isNull())
    {

        QFile file(fileImport);
        if (file.open(QIODevice::ReadOnly))
        {
            QDomDocument doc;
            if(doc.setContent(&file))
            {
                QDomElement data = doc.firstChildElement("data");
                m_gameModel->readDataFromXml(data);
                m_gameMasterModel->readDataFromXml(data);
                m_scenarioManager->readDataFromXml(data);
            }
        }

    }
}
void MainWindow::makeGameMasterUnavailable()
{
    int i = QInputDialog::getInt(this,tr("How long this GM will be gone ?"),tr("busy time (in mins):"),0,0,500);
    QModelIndex tmp = ui->m_masterView->currentIndex();
    if(tmp.isValid())
    {
        m_gameMasterModel->setData(tmp,i,GameMasterModel::BackTime);
        //model->setData(index,1,ScenarioModel::DecreaseRole);
    }
}

void MainWindow::resetData()
{
    int ret;
    if(m_gameModel->rowCount()>0)
    {
        QMessageBox box(QMessageBox::Warning,tr("Do you confirm?"),tr("You are about to clear all the data.\nAll unsaved changes will be lost.\nDo you want to continue?"),QMessageBox::Cancel | QMessageBox::Yes,this);

        ret = box.exec();
    }
    else
    {
        ret= (int) QMessageBox::Yes;
    }

    switch (ret)
    {
    case QMessageBox::Yes:
        m_scenarioManager->resetData();
        m_gameModel->resetData();
        m_gameMasterModel->resetData();
        break;
    case QMessageBox::Cancel:
        break;
    default:
        break;
    }

}

void MainWindow::clearSelection( QModelIndex index)
{
    QAbstractItemView* view = qobject_cast<QAbstractItemView*>(sender());
   // qDebug() << "view" << view << index.isValid();

    if((NULL!=view)&&(!index.isValid()))
    {
        view->clearSelection();
    }
}
void MainWindow::exporCSV()
{
    QString fileExport = QFileDialog::getSaveFileName(this, tr("Export Data as CSV"), m_preferences->value("dataDirectory",QDir::homePath()).toString(), tr("Csv Rolisteam Conv Database (*.csv)"));
    if(!fileExport.isNull())
    {
        ExportCSV csvWriter;

        csvWriter.setData(m_gameModel,m_gameMasterModel,m_scenarioManager->getRightModel(Scenario::DONE));
        csvWriter.setFilename(fileExport);

        csvWriter.write();
    }
}
