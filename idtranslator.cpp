#include "idtranslator.h"

IdTranslator* IdTranslator::m_singleton=nullptr;

IdTranslator::IdTranslator(QMap<QString, Game *> &l, QMap<QString, GameMaster *> &masterlist)
: m_list(l),m_masterlist(masterlist)
{

}

IdTranslator *IdTranslator::getInstance(QMap<QString, Game *> &l, QMap<QString, GameMaster *> &masterlist)
{
    if(nullptr == m_singleton)
    {
        m_singleton = new IdTranslator(l,masterlist);
    }
    return m_singleton;
}

IdTranslator *IdTranslator::getInstance()
{
    return m_singleton;
}

Game *IdTranslator::getGameById(QString key)
{
    if(!m_list.contains(key))
        return nullptr;
    return m_list.value(key);
}

GameMaster* IdTranslator::getGameMasterById(QString key)
{
    if(!m_masterlist.contains(key))
        return nullptr;
    return m_masterlist.value(key);
}
