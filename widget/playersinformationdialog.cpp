#include "playersinformationdialog.h"
#include "ui_playersinformationdialog.h"

PlayersInformationDialog::PlayersInformationDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PlayersInformationDialog)
{
    ui->setupUi(this);
}

PlayersInformationDialog::~PlayersInformationDialog()
{
    delete ui;
}
void PlayersInformationDialog::setData(QStringList data)
{
    QString result;
    result = tr("<table><tr><th>Name</th><th>FirstName</th><th>Phone</th></tr>");
    foreach(QString user, data)
    {
        QStringList fields = user.split(';');
        if(fields.size() == 3)
        {
            result += tr("<tr><td>%1</td><td>%2</td><td>%3</td></tr>").arg(fields[0]).arg(fields[1]).arg(fields[2]);
        }
    }
    result += tr("</table>");


    ui->m_textBrowser->setHtml(result);
}
