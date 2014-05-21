#ifndef SCENARIOMODEL_H
#define SCENARIOMODEL_H

#include <QAbstractListModel>
#include <QStringList>


#include "scenario.h"
#include "game.h"

class ScenarioModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit ScenarioModel(QObject *parent = 0);
    int rowCount ( const QModelIndex & parent = QModelIndex() ) const;
    int columnCount ( const QModelIndex & parent = QModelIndex() ) const;
    QVariant data ( const QModelIndex & index, int role = Qt::DisplayRole ) const;
    bool setData(const QModelIndex & index, const QVariant & value, int role = Qt::EditRole);
    Qt::ItemFlags flags ( const QModelIndex & index ) const;

    void setDataList(QList<Scenario*>* );
    void addDataList(QList<Scenario*>* );
    void setGameList(QList<Game*>* );
    void setPerformer(QString m_id);

    void appendScenario(Scenario*);

    virtual QVariant headerData ( int section, Qt::Orientation orientation, int role = Qt::DisplayRole ) const;
    QList<Scenario*>* getScenarioList();
signals:
    void updateHeader();
public slots:

private:
    QList<Scenario*>* m_scenarioList;
    QList<Game*>* m_gameList;
    QString m_uuid;//isolate
    bool m_isFiltered;
    QStringList m_columns;
    
};

#endif // SCENARIOMODEL_H
