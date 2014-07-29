#include "table.h"

Table::Table()
{

}
void Table::setRoomName(QString str)
{
    m_id = str;
}

void Table::setDescription(QString str)
{
    m_description=str;
}

void Table::setId(int id)
{
    m_id=id;
}

void Table::setCapacity(int c)
{
    m_capacity=c;
}

void Table::setState( bool avail)
{
    if(avail)
        m_state=Table::AVAILABLE;
    else
        m_state=Table::BUSY;
}



bool Table::checkCapacity(int a)
{
    return (a <= m_capacity);
}

QString Table::getRoomName()
{
    return m_roomName;
}

QString Table::getDescription()
{
    return m_description;

}

int Table::getId()
{
    return m_id;
}

int Table::getCapacity()
{
    return m_capacity;
}

Table::State Table::getCurrentState()
{
    return m_state;
}
