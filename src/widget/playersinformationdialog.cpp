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
    result = tr("<table><tr><th>Name</th><th>FirstName</th><th>Phone</th><th>Nombre</th></tr>");
    for(auto user: data)
    {
        if(user.isEmpty())
            continue;

        QStringList fields = user.split(';');
        result += "<tr>";
        for(auto field : fields) //if(fields.size() == 4)
        {
            result += tr("<td>%1</td>").arg(field);
        }
        result += "</tr>";
    }
    result += tr("</table>");


    ui->m_textBrowser->setHtml(result);
}
