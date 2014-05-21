#ifndef GAME_H
#define GAME_H

#include <QString>

#include "serializable.h"

class Game : public Serialisable
{

public:
    enum LEVEL {BEGINNER,AVERAGE,EXPERIMENTED};

    Game();
    virtual void readFromData(QDataStream&);
    virtual void writeToData(QDataStream&);

    //
    void setTitle(QString title);
    void setPunchLine(QString title);
    void setDescription(QString title);
    void setUuid(QString id);




    QString getTitle() const;
    QString getPunchLine() const;
    QString getDescription() const;
    QString getUuid() const;


private:
    QString m_uuid;
    QString m_title;
    QString m_description;
    QString m_punchLine;
    /**/

};

#endif // GAME_H
