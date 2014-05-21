#ifndef GAMESESSION_H
#define GAMESESSION_H

#include <QString>
#include <QDateTime>
#include <QUuid>
#include "serializable.h"

class Scenario : public Serialisable
{
public:
    enum LEVEL {BEGINNER,AVERAGE,EXPERIMENTED};
    enum STATE {AVAILABLE,RUNNING,DONE};

    Scenario();

//set
    void setGameId(QString id);
    void setGameMasterId(QString id);
    void setDuration(quint64 id);
    void setTableNumber(quint32 number);
    void setDateTime(QDateTime time);
    void setLevel(Scenario::LEVEL);
    void setMaximumPlayer(quint32);
    void setMinimumPlayer(quint32);
    void setTitle(QString m);
    void setDescription(QString m);


//gets
    Scenario::LEVEL getLevel() const;
    quint64 getDuration() const;
    quint32 getMaximumPlayers() const;
    quint32 getMinimumPlayers() const;
    QString getGameId();
    QString getTitle();
    QString getDescription();
    QString getGameMasterId();
    quint64 getDuration();
    quint32 getTableNumber();
    QDateTime getDateTime();



//save & restore
    virtual void readFromData(QDataStream&);
    virtual void writeToData(QDataStream&);

private:
    QString m_gameId;
    QString m_gameMasterId;
    QString m_scenarioId;
    quint64 m_duration;//minutes
    quint32 m_tableNumber;
    QDateTime m_startTime;
    LEVEL m_level;
    quint32 m_maximumPlayers;
    quint32 m_minimumPlayers;
    quint32 m_currentPlayers;
    QString m_title;
    QString m_description;
    STATE m_state;

};

#endif // GAMESESSION_H
