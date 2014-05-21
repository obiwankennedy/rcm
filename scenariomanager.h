#ifndef SCENARIOMANAGER_H
#define SCENARIOMANAGER_H

#include <QObject>
#include <QList>



#include "scenario.h"


class ScenarioManager : public QObject
{
    Q_OBJECT
public:
    explicit ScenarioManager(QObject *parent = 0);
    

    void addAvailableScenarios(QList<Scenario*>* l);
    void addRunningScenarios(QList<Scenario*>* l);
    void addDoneScenarios(QList<Scenario*>* l);
    
    void addOneAvailableScenario(Scenario* l);
    void addOneRunningScenario(Scenario* l);
    void addOneDoneScenario(Scenario* l);

private:
    QList<Scenario*>* m_availableScenarioList;
    QList<Scenario*>* m_runningScenarioList;
    QList<Scenario*>* m_doneScenarioList;
};

#endif // SCENARIOMANAGER_H
