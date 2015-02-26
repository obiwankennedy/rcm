#include "exportcsv.h"
#include <QTextStream>
#include <QFile>

ExportCSV::ExportCSV()
{
}
void ExportCSV::write()
{
    QFile file(m_fileName);
    if (!file.open(QFile::WriteOnly | QFile::Text))
    {
        m_error.append(QObject::tr("Cannot write file %1:\n%2.")
                       .arg(m_fileName)
                       .arg(file.errorString()));
    }
    QTextStream cvs(&file);






    if(m_gameModel!=NULL)
    {
        cvs << QObject::tr("List of Games\n");
      for(int i = 0; i<m_gameModel->rowCount();i++)
      {
          QModelIndex index = m_gameModel->index(i,0);
          cvs << QString("%1;%2;%3;%4;%5\n").arg(m_gameModel->data(index).toString())
                                            .arg(m_gameModel->data(index,GameModel::Description).toString())
                                            .arg(m_gameModel->data(index,GameModel::PunchLine).toString())
                                            .arg(m_gameModel->data(index,GameModel::IMAGE_URL).toString())
                                            .arg(m_gameModel->data(index,GameModel::TYPE).toString());
      }

    }

    if(NULL!= m_gameMasterModel)
    {
        cvs << QObject::tr("List of Game Masters\n");
      for(int i = 0; i<m_gameMasterModel->rowCount();i++)
      {
          QModelIndex index = m_gameMasterModel->index(i,0);
          cvs << QString("%1;%2;%3;%4;%5\n").arg(m_gameMasterModel->data(index).toString())
                                            .arg(m_gameMasterModel->data(index,GameMasterModel::NameRole).toString())
                                            .arg(m_gameMasterModel->data(index,GameMasterModel::FirstNameRole).toString())
                                            .arg(m_gameMasterModel->data(index,GameMasterModel::PhoneRole).toString())
                                            .arg(m_gameMasterModel->data(index,GameMasterModel::MailRole).toString());
      }

    }

    if(NULL!= m_scenarioModel)
    {
        cvs << QObject::tr("List of Scenarios\n");
      for(int i = 0; i<m_scenarioModel->rowCount();i++)
      {
          QModelIndex index = m_scenarioModel->index(i,0);
          cvs << QString("%1;%2;%3;%4;%5;%6;%7\n").arg(m_scenarioModel->data(index,ScenarioModel::TitleRole).toString())
                                            .arg(m_scenarioModel->data(index,ScenarioModel::GameTitleRole).toString())
                                            .arg(m_scenarioModel->data(index,ScenarioModel::GameMasterNameRole).toString())
                                            .arg(m_scenarioModel->data(index,ScenarioModel::LevelRole).toString())
                                            .arg(m_scenarioModel->data(index,ScenarioModel::CurrentPlayerRole).toString())
                                            .arg(m_scenarioModel->data(index,ScenarioModel::MaximumRole).toString())
                                            .arg(m_scenarioModel->data(index,ScenarioModel::DurationRole).toString());
      }

    }
}
