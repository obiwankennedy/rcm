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
    explicit GameMasterDialog(QMap<QString,Game*>& l,QWidget *parent = 0);
    ~GameMasterDialog();

    QString getName();
    QString getNickName();
    QString getFirstName();
    QString getPhoneNumber();
    QString getMailAddress();

    QList<Scenario*>* getScenarioList();
    void setPerformer(QString m_id);
public slots:
    void addScenario();
    void updateGameListHeader();

private:
    Ui::GameMasterDialog *ui;
    ScenarioModel* m_model;


    QAction* m_addScenarioAct;
    QAction* m_delScenarioAct;
    GameEditorDelegate* m_gameDelegate;
};

#endif // GAMEMASTERDIALOG_H
