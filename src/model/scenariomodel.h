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

#include <QAbstractTableModel>
#include <QString>
#include <QStringList>
#include <QTimer>

#include "game.h"
#include "gamemaster.h"
#include "gamemodel.h"
#include "scenario.h"
#include "serializable.h"

class ScenarioModel : public QAbstractTableModel, public Serialisable
{
    Q_OBJECT
    // Q_PROPERTY(type Title READ getTitle WRITE setTitle NOTIFY titleChanged)
public:
    enum CustomRole
    {
        IncreaseRole= Qt::UserRole + 1,
        DecreaseRole,
        GameIdRole,
        GameMasterIdRole,
        DurationRole,
        MinimumRole,
        MaximumRole,
        DescriptionRole,
        CurrentPlayerRole,
        TitleRole,
        GameTitleRole,
        GameMasterNameRole,
        ColorRole,
        PixmapRole,
        LevelRole,
        AddPlayerInfo,
        RemovePlayerInfo,
        ClearPlayerInfo,
        SetPlayerInfo,
        GameCount
    };

    explicit ScenarioModel(QMap<QString, Game*>& l, GameModel* gameModel, QMap<QString, GameMaster*>& lstGm,
        Scenario::STATE m, QObject* parent= nullptr);
    int rowCount(const QModelIndex& parent= QModelIndex()) const;
    int columnCount(const QModelIndex& index= QModelIndex()) const;
    QVariant data(const QModelIndex& index, int role= Qt::DisplayRole) const;
    bool setData(const QModelIndex& index, const QVariant& value, int role= Qt::EditRole);
    Qt::ItemFlags flags(const QModelIndex& index) const;

    void setDataList(QList<Scenario*>*);
    void addDataList(QList<Scenario*>*);
    void setGameList(QList<Game*>*);
    void setPerformer(QString m_id);

    void appendScenario(Scenario*);
    void removeScenario(Scenario* tmp);
    void removeScenarioAtIndex(QModelIndex& index);
    Scenario* getScenarioById(QString tmp);

    virtual QVariant headerData(int section, Qt::Orientation orientation, int role= Qt::DisplayRole) const;
    QList<Scenario*>* getScenarioList();

    QHash<int, QByteArray> roleNames() const;

    virtual void readFromData(QDataStream&);
    virtual void writeToData(QDataStream&) const;
    virtual void readDataFromJson(QJsonObject&);
    virtual void writeDataToJson(QJsonObject&);

    virtual QDomElement writeDataToXml(QDomDocument&);
    virtual void readDataFromXml(QDomNode&);

    /**
     * @brief disableEdition allows the view to change the data.
     */
    void disableEdition();

    void resetData();

    QString getTitle(); // Q_INVOKABLE
    void setTitle(QString);
signals:
    void updateHeader();
    void addedData();
    void titleChanged();

public slots:
    void mayStartTimer();
    void timeOut();

private:
    Scenario::STATE m_state;
    QList<Scenario*>* m_scenarioList;
    QMap<QString, Game*>& m_list;
    QMap<QString, GameMaster*>& m_gameMasterMap;
    QString m_uuid; // isolate
    bool m_isFiltered;
    QStringList m_columns;
    GameModel* m_gameModel= nullptr;
    /// @todo there may be a way to place this in manager/controler
    QTimer* m_timer;
    bool m_edition;
};

#endif // SCENARIOMODEL_H
