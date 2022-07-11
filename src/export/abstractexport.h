#ifndef ABSTRACTEXPORT_H
#define ABSTRACTEXPORT_H

#include "gamemodel.h"
#include "gamemastermodel.h"
#include "scenariomodel.h"

class AbstractExport
{
public:
    AbstractExport();
    virtual ~AbstractExport();
    virtual void write()=0;

    virtual void setData(GameModel*,GameMasterModel*,ScenarioModel*);
    virtual void setFilename(QString p);

    virtual bool hasError();
    virtual QString getLatestErrorString();



protected:
    GameModel* m_gameModel;
    GameMasterModel* m_gameMasterModel;
    ScenarioModel* m_scenarioModel;

    QString m_fileName;
    QStringList m_error;
};

#endif // ABSTRACTEXPORT_H
