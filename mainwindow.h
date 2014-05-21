#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QAction>

#include "gamemodel.h"
#include "gamemastermodel.h"
#include "scenario.h"
#include "customerview.h"

#include "preferences/preferencesmanager.h"
#include "serializable.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


    void readSettings();
    void writeSettings();
    

public slots:
    void addGameDialog();
    void addGameMasterDialog();

protected:
    void closeEvent ( QCloseEvent * event );


private slots:
    void saveData();
    void readFile();
    bool maybeSave();
    void saveAsData();
    void openData();




private:
    void initActions();

private:
    Ui::MainWindow *ui;
    //data model
    GameModel* m_gameModel;
    GameMasterModel* m_gameMasterModel;

    QList<Scenario*>* m_scenarioList;
    //GameMasterModel* m_gameMasterPresenceModel;

    //QActions
    QAction* m_addGameAct;
    QAction* m_removeGameAct;
    QAction* m_removeGMAct;
    QAction* m_addGMAct;

    CustomerView* m_customerView;

    QString m_currentDataPath;
    PreferencesManager* m_preferences;
};

#endif // MAINWINDOW_H
