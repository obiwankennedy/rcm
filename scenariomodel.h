/***************************************************************************
* Copyright (C) 2014 by Renaud Guezennec                                   *
* http://renaudguezennec.homelinux.org/accueil,3.html                      *
*                                                                          *
*  This file is part of rcm                                                *
*                                                                          *
* Rcm is free software; you can redistribute it and/or modify              *
* it under the terms of the GNU General Public License as published by     *
* the Free Software Foundation; either version 2 of the License, or        *
* (at your option) any later version.                                      *
*                                                                          *
* This program is distributed in the hope that it will be useful,          *
* but WITHOUT ANY WARRANTY; without even the implied warranty of           *
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the             *
* GNU General Public License for more details.                             *
*                                                                          *
* You should have received a copy of the GNU General Public License        *
* along with this program; if not, write to the                            *
* Free Software Foundation, Inc.,                                          *
* 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.                 *
***************************************************************************/
#ifndef SCENARIOMODEL_H
#define SCENARIOMODEL_H

#include <QAbstractListModel>
#include <QStringList>
#include <QTimer>


#include "scenario.h"
#include "game.h"

class ScenarioModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum CustomRole {IncreaseRole = Qt::UserRole+1,DecreaseRole,GameIdRole,GameMasterIdRole,DurationRole,MinimumRole,MaximumRole,DescriptionRole,CurrentPlayerRole,TitleRole,GameTitleRole};

    explicit ScenarioModel(QMap<QString,Game*>& l,Scenario::STATE m,QObject *parent = 0);
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
    void removeScenario(Scenario* tmp);
    Scenario* getScenarioById(QString tmp);

    virtual QVariant headerData ( int section, Qt::Orientation orientation, int role = Qt::DisplayRole ) const;
    QList<Scenario*>* getScenarioList();

     QHash<int, QByteArray>  roleNames() const;
signals:
    void updateHeader();
    void addedData();
public slots:
    void mayStartTimer();
    void timeOut();
private:
    QList<Scenario*>* m_scenarioList;
    QList<Game*>* m_gameList;/// @brief no longer needed i think
    QMap<QString,Game*>& m_list;
    QString m_uuid;//isolate
    bool m_isFiltered;
    QStringList m_columns;
    Scenario::STATE m_state;
    /// @todo there may be a way to place this in manager/controler
    QTimer* m_timer;
};

#endif // SCENARIOMODEL_H
