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
#include <QJsonDocument>
#include <QJsonObject>

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "gamedialog.h"
#include "gamemaster.h"

#include "gamemasterdialog.h"

#include "export/exportcsv.h"

#include "idtranslator.h"

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

    ui->m_availableScenario->setDragEnabled(true);

    //m_gameMasterPresenceModel = new GameMasterModel();

    m_preferences = PreferencesManager::getInstance();

    ui->m_gameView->setModel(m_gameModel);
    ui->m_masterView->setModel(m_gameMasterModel);


    IdTranslator* translator = IdTranslator::getInstance(m_gameModel->getGameMap(),m_gameMasterModel->getMasterMap());
    Q_UNUSED(translator);
    m_scenarioManager = new ScenarioManager(ui,m_gameModel->getGameList(),m_gameModel->getGameMap(),m_gameMasterModel->getMasterMap(),m_gameImgProvider);
    m_scenarioManager->setLabel(ui);

    initActions();

    ui->m_gameView->setSelectionMode(QAbstractItemView::ExtendedSelection);

    readSettings();

    m_recentFile=new QMenu(tr("Recent Files"));
    refreshOpenedFile();
    ui->m_fileMenu->insertMenu(ui->m_quitAct,m_recentFile);
    ui->m_fileMenu->insertSeparator(ui->m_quitAct);

    ui->m_masterView->installEventFilter(this);
    m_locview = new LocalisationView(ui->m_timeLine);


    connect(ui->m_properties,SIGNAL(clicked(bool)),m_locview,SLOT(setProperties()));
   // ui->m_tabWidget->addTab(,tr("Tables"));


    //setAttribute( Qt::WA_DeleteOnClose);
    //clear selection connect
    connect(ui->m_gameView,SIGNAL(clicked(QModelIndex)),this,SLOT(clearSelection(QModelIndex)));
    connect(ui->m_masterView,SIGNAL(clicked(QModelIndex)),this,SLOT(clearSelection(QModelIndex)));
    connect(ui->m_scenarioAvailabeView,SIGNAL(clicked(QModelIndex)),this,SLOT(clearSelection(QModelIndex)));
    connect(ui->m_scenarioDoneView,SIGNAL(clicked(QModelIndex)),this,SLOT(clearSelection(QModelIndex)));
    connect(ui->m_scenarioRunningView,SIGNAL(clicked(QModelIndex)),this,SLOT(clearSelection(QModelIndex)));
    connect(ui->m_exportCSVAct,SIGNAL(triggered()),this,SLOT(exporCSV()));

    connect(ui->m_nextDay,SIGNAL(clicked(bool)),m_locview,SLOT(displayNextDay()));
    connect(ui->m_previousDay,SIGNAL(clicked(bool)),m_locview,SLOT(displayPreviousDay()));


}

MainWindow::~MainWindow()
{
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

    addAction(ui->m_customerViewDisplayAct);

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







    connect(ui->m_csvAct,SIGNAL(triggered(bool)),this,SLOT(readCSV()));

    // init menu
    connect(ui->m_newAct,SIGNAL(triggered()),this,SLOT(resetData()));
    connect(ui->m_openAct,SIGNAL(triggered()),this,SLOT(openJsonData()));
    connect(ui->m_quitAct,SIGNAL(triggered()),this,SLOT(close()));
    connect(ui->m_saveAct,SIGNAL(triggered()),this,SLOT(saveDataToJson()));
    connect(ui->m_saveAsAct,SIGNAL(triggered()),this,SLOT(saveAs()));

    connect(ui->m_importBinary,SIGNAL(triggered()),this,SLOT(openData()));
    connect(ui->m_exportBinary,SIGNAL(triggered(bool)),this,SLOT(saveAsData()));


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
#include <QFileDialog>
void MainWindow::saveAs()
{
    m_currentDataPath = QFileDialog::getSaveFileName(this,tr("Save Convention Data"),QDir::homePath(),tr("Rolisteam Convention Data(*.rcd)"));
    if(!m_currentDataPath.isEmpty())
    {
        if(!m_currentDataPath.endsWith(".rcd"))
        {
            m_currentDataPath.append(QStringLiteral(".rcd"));
        }
        saveDataToJson();
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
        m_locview->writeToData(in);
        file.close();
    }
}
void MainWindow::saveDataToJson()
{
    if(m_currentDataPath.isEmpty())
        saveAs();
    else if(!m_currentDataPath.isEmpty())
    {
        if(!m_currentDataPath.endsWith(".rcd"))
        {
            m_currentDataPath.append(".rcd");
            ///@Warning
        }
        QFile file(m_currentDataPath);
        if(file.open(QIODevice::WriteOnly))
        {
            //init Json
            QJsonDocument json;
            QJsonObject obj;



            //Get datamodel
            QJsonObject games;
            m_gameModel->writeDataToJson(games);
            obj["games"]=games;

            QJsonObject masters;
            m_gameMasterModel->writeDataToJson(masters);
            obj["masters"]=masters;

            QJsonObject scenarios;
            m_scenarioManager->writeDataToJson(scenarios);
            obj["scenarios"]=scenarios;

            QJsonObject schedules;
            m_locview->writeDataToJson(schedules);
            obj["schedules"]=schedules;

            json.setObject(obj);
            file.write(json.toJson());

            setWindowTitle(m_title.arg(QFileInfo(m_currentDataPath).fileName()).arg("RCM"));
            setWindowModified(false);
        }
    }
}
void MainWindow::openJsonData()
{
    m_currentDataPath = QFileDialog::getOpenFileName(this,tr("Open Convention Data"),QDir::homePath(),tr("Rolisteam Convention Data(*.rcd)"));
    if(!m_currentDataPath.isEmpty())
    {
        resetData();
        readJSonFile();
        addRecentFile();
    }
}
void MainWindow::readJSonFile()
{
    QFile file(m_currentDataPath);
    QFileInfo info(m_currentDataPath);


    setWindowTitle(m_title.arg(info.fileName()));
    if (file.open(QIODevice::ReadOnly))
    {
        QJsonDocument json = QJsonDocument::fromJson(file.readAll());
        QJsonObject jsonObj = json.object();

        QJsonObject games = jsonObj["games"].toObject();
        QJsonObject masters = jsonObj["masters"].toObject();
        QJsonObject scenarios = jsonObj["scenarios"].toObject();
        QJsonObject schedules = jsonObj["schedules"].toObject();


        m_gameModel->readDataFromJson(games);
        m_gameMasterModel->readDataFromJson(masters);
        m_scenarioManager->readDataFromJson(scenarios);
        m_locview->readDataFromJson(schedules);
        file.close();
        ensureTabVisible(DATA);
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
     //m_currentDataPath = "/home/renaud/documents/rcm/data_test_several_game.rcdb";
    m_currentDataPath = QFileDialog::getOpenFileName(this, tr("Open Data"), m_preferences->value("dataDirectory",QDir::homePath()).toString(), tr("Rolisteam Conv Database (*.rcdb)"));
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

/*void MainWindow::refreshView()
{
    if(m_scenarioManager->isCustomViewDisplayed())
    {
        QImage img = m_window->grabWindow();

        if(img.isNull())
            return;

        static int count = 0;

        //img.save(tr("/home/renaud/application/mine/pasSageEnSeine/screen/%1_screen.png").arg(++count,3,10,QChar('0')),"png");
        qDebug() << "id page shot save" << i;

        m_ratioImage = (double)img.size().width()/img.size().height();
        m_ratioImageBis = (double)img.size().height()/img.size().width();

        m_label->setPixmap(QPixmap::fromImage(img));

        if((i+1>=0)&&(i+1<m_commentData.size()))
        {
            ui->textEdit->setHtml(m_commentData.at(i));
        }
        resizeLabel();
    }
}*/
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
    m_gameModel->readSettings(settings);
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
    m_gameModel->writeSettings(settings);
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
void MainWindow::readCSV()
{
    QString fileImport = QFileDialog::getOpenFileName(this, tr("Open CSV Data"), m_preferences->value("dataDirectory",QDir::homePath()).toString(), tr("Csv Conv DataBase (*.csv)"));
    if(!fileImport.isNull())
    {

        QFile file(fileImport);
        if (file.open(QIODevice::ReadOnly))
        {
            QTextStream text(&file);
            QString line;
            text.readLineInto(&line);//remove first line
          while (text.readLineInto(&line))
          {//	Nom du jdr	Nombre de joueurs (mini-max)	Durée de la partie prévu
              //Description du jdr et/ou du scénario	Lien vers une image représentant le jeu (exemple la couverture du jeu)	Notes
              //Autre jeux ?	Nom du jdr	Nombre de joueurs (mini-max)	Durée de la partie prévu	Description du jdr et/ou du scénario
              //Lien vers une image représentant le jeu (exemple la couverture du jeu)	Notes	Autre jeux ?
              //Nom du jdr	Nombre de joueurs (mini-max)	Durée de la partie prévu	Description du jdr et/ou du scénario
              //Lien vers une image représentant le jeu (exemple la couverture du jeu)	Notes	Alors, heureux ?
//32
              QStringList array = line.split(";");

              while(array.size()!=35)
              {
                  array.append(QString());
              }
              QString hour = array.at(0);
              QString mail = array.at(1);
              QString name = array.at(2);
              QString pseudo = array.at(3);
              QString assos= array.at(4);
              QString dispo = array.at(5);
              QString info = array.at(6);
              QString rpg1 = array.at(7);
              QString rpg1PlayerCount = array.at(8);
              QString rpg1Time = array.at(9);
              QString rpg1Description = array.at(10);
              QString rpg1ImgLink = array.at(11);
              QString rpg1note = array.at(12);
              QString rpgOther = array.at(13);
              QString rpg2 = array.at(14);
              QString rpg2PlayerCount = array.at(15);
              QString rpg2Time = array.at(16);
              QString rpg2Description = array.at(17);
              QString rpg2ImgLink = array.at(18);
              QString rpg2note = array.at(19);
              QString rpgOther2 = array.at(20);
              QString rpg3 = array.at(21);
              QString rpg3PlayerCount = array.at(22);
              QString rpg3Time = array.at(23);
              QString rpg3Description = array.at(24);
              QString rpg3ImgLink = array.at(25);
              QString rpg3note = array.at(26);
              QString rpgOther3 = array.at(27);

              QString rpg4 = array.at(28);
              QString rpg4PlayerCount = array.at(29);
              QString rpg4Time = array.at(30);
              QString rpg4Description = array.at(31);
              QString rpg4ImgLink = array.at(32);
              QString rpg4note = array.at(33);
              QString rpgOther4 = array.at(34);


              qDebug() << "note:"<<rpg4note << rpg1 << rpg2 << array.size();

              GameMaster* gm = new GameMaster();
              gm->setName(name);
              gm->setNickName(pseudo);
              gm->setMailAddress(mail);

              QList<Scenario*>* listOfGame = new QList<Scenario*>();


              if(!rpg1.isEmpty())
              {
                Game* game1 = new Game();
                game1->setTitle(rpg1);
                game1->setImageUrl(rpg1ImgLink);

                m_gameModel->append(game1);


                QStringList minmax = rpg1PlayerCount.split('-');

                Scenario* scen1 = new Scenario();
                scen1->setDescription(rpg1Description);
                scen1->setDuration(rpg1Time.toInt());
                scen1->setMaximumPlayer(minmax[1].toInt());
                scen1->setMinimumPlayer(minmax[0].toInt());
                scen1->setGameId(game1->getUuid());
                scen1->setGameMasterId(gm->getId());

                listOfGame->append(scen1);

              }
              if(!rpg2.isEmpty())
              {
                Game* game2 = new Game();
                game2->setTitle(rpg2);
                game2->setImageUrl(rpg2ImgLink);

                m_gameModel->append(game2);


                QStringList minmax = rpg2PlayerCount.split('-');

                Scenario* scen2 = new Scenario();
                scen2->setDescription(rpg2Description);
                scen2->setDuration(rpg2Time.toInt());
                scen2->setMaximumPlayer(minmax[1].toInt());
                scen2->setMinimumPlayer(minmax[0].toInt());
                scen2->setGameId(game2->getUuid());
                scen2->setGameMasterId(gm->getId());

                listOfGame->append(scen2);

              }
              if(!rpg3.isEmpty())
              {
                Game* game3 = new Game();
                game3->setTitle(rpg1);
                game3->setImageUrl(rpg1ImgLink);

                m_gameModel->append(game3);


                QStringList minmax = rpg3PlayerCount.split('-');

                Scenario* scen3 = new Scenario();
                scen3->setDescription(rpg3Description);
                scen3->setDuration(rpg3Time.toInt());
                scen3->setMaximumPlayer(minmax[1].toInt());
                scen3->setMinimumPlayer(minmax[0].toInt());
                scen3->setGameId(game3->getUuid());
                scen3->setGameMasterId(gm->getId());

                listOfGame->append(scen3);

              }

              if(!rpg4.isEmpty())
              {
                Game* game4 = new Game();
                game4->setTitle(rpg4);
                game4->setImageUrl(rpg4ImgLink);

                m_gameModel->append(game4);


                QStringList minmax = rpg4PlayerCount.split('-');

                Scenario* scen4 = new Scenario();
                scen4->setDescription(rpg4Description);
                scen4->setDuration(rpg4Time.toInt());
                scen4->setMaximumPlayer(minmax[1].toInt());
                scen4->setMinimumPlayer(minmax[0].toInt());
                scen4->setGameId(game4->getUuid());
                scen4->setGameMasterId(gm->getId());

                listOfGame->append(scen4);

              }

              gm->setGMScenario(listOfGame);

              m_gameMasterModel->append(gm);

          }

        }

    }
}
