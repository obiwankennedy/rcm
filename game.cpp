#include "game.h"
#include <QUuid>

Game::Game()
    : m_uuid(QUuid::createUuid().toString())
{


}
void Game::readFromData(QDataStream& from)
{
    from >> m_title;
    from >> m_punchLine;
    from >> m_description;
    from >> m_uuid;
}

void Game::writeToData(QDataStream& to)
{
    to << m_title;
    to << m_punchLine;
    to << m_description;
    to << m_uuid;

}


void Game::setTitle(QString title)
{
    m_title = title;
}


QString  Game::getTitle() const
{
    return m_title;
}

void Game::setPunchLine(QString line)
{
    m_punchLine = line;
}

void Game::setDescription(QString title)
{
    m_description = title;
}

void Game::setUuid(QString id)
{
    m_uuid = id;
}
QString Game::getPunchLine() const
{
    return m_punchLine;
}
QString Game::getDescription() const
{
    return m_description;
}
QString Game::getUuid() const
{
    return m_uuid;
}
