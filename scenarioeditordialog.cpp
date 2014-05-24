#include "scenarioeditordialog.h"
#include "ui_scenarioeditordialog.h"


ScenarioEditorDialog::ScenarioEditorDialog(QMap<QString,Game*>& l,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ScenarioEditorDialog)
{
    ui->setupUi(this);

    m_gameDelegate = new GameEditorDelegate(l);

    ui->m_tableView->setItemDelegateForColumn(0,m_gameDelegate);

#if QT_VERSION >= 0x050000
    ui->m_tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Interactive);
#else
    ui->m_tableView->horizontalHeader()->setResizeMode(QHeaderView::Interactive);
#endif
    ui->m_tableView->horizontalHeader()->setStretchLastSection(true);
    ui->m_tableView->verticalHeader()->setVisible(false);
}

ScenarioEditorDialog::~ScenarioEditorDialog()
{
    delete ui;
}
void ScenarioEditorDialog::setModel(ScenarioModel* model)
{
    ui->m_tableView->setModel(model);
}
