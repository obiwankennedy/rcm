#ifndef IDTRANSLATOR_H
#define IDTRANSLATOR_H

#include "game.h"
#include "gamemaster.h"
#include "scenario.h"
#include <QMap>

class IdTranslator
{
public:
    static IdTranslator* getInstance(QMap<QString,Game*>& l,QMap<QString,GameMaster*>& masterlist);
    static IdTranslator* getInstance();

    Game* getGameById(QString key);
    GameMaster* getGameMasterById(QString key);

private:
    IdTranslator(QMap<QString,Game*>& l,QMap<QString,GameMaster*>& masterlist);


private:
    QMap<QString,Game*>& m_list;
    QMap<QString,GameMaster*>& m_masterlist;
    static IdTranslator* m_singleton;
};

#endif // IDTRANSLATOR_H
