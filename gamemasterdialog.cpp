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
    m_model = new ScenarioModel();
    ui->m_scenarioTable->setModel(m_model);
    ui->m_deleteButton->setDefaultAction(m_delScenarioAct);
    ui->m_newButton->setDefaultAction(m_addScenarioAct);

    m_gameDelegate = new GameEditorDelegate(l);

    ui->m_scenarioTable->setItemDelegateForColumn(0,m_gameDelegate);
    ui->m_scenarioTable->horizontalHeader()->setResizeMode(QHeaderView::Interactive);
    ui->m_scenarioTable->horizontalHeader()->setStretchLastSection(true);
//    ui->m_scenarioTable->horizontalHeader()->setCascadingSectionResizes(true);



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
