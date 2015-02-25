#include "abstractexport.h"

AbstractExport::AbstractExport()
{

}

AbstractExport::~AbstractExport()
{

}


void AbstractExport::setData(GameModel* gm,GameMasterModel* gmm,ScenarioModel* sm)
{
    m_gameModel=gm;
    m_gameMasterModel=gmm;
    m_scenarioModel=sm;
}

void AbstractExport::setFilename(QString p)
{
    m_fileName=p;
}
bool AbstractExport::hasError()
{
    return !m_error.isEmpty();
}

QString AbstractExport::getLatestErrorString()
{
    if(hasError())
       return m_error.last();
    else
        return QString();
}
