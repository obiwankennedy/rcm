#include "preferencesdialog.h"
#include "ui_preferencesdialog.h"

#include "preferencesmanager.h"
#include <QFileDialog>

PreferencesDialog::PreferencesDialog(QWidget* parent) : QDialog(parent), ui(new Ui::PreferencesDialog)
{
    ui->setupUi(this);
}

PreferencesDialog::~PreferencesDialog()
{
    delete ui;
}

void PreferencesDialog::on_m_openBtn_clicked()
{
    auto pref= PreferencesManager::getInstance();
    auto dir= QFileDialog::getExistingDirectory(
        this, tr("Place to store all images"), pref->value("imagesDirectory", QDir::homePath()).toString());

    if(dir.isEmpty())
        return;

    pref->registerValue("imagesDirectory", dir);
    ui->m_pathEdit->setText(dir);
}
