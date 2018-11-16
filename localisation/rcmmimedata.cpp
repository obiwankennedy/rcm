#include "rcmmimedata.h"


RcmMimeData::RcmMimeData()
    : m_data(nullptr)
{
    m_format = "rcm/scenario-item";
}
bool RcmMimeData::hasFormat ( const QString & mimeType ) const
{
    if(mimeType==m_format)
    {
        return hasScenario();
    }
    return QMimeData::hasFormat(mimeType);
}

void RcmMimeData::setScenario(Scenario* data)
{
    m_data=data;
}
bool RcmMimeData::hasScenario() const
{
    if(m_data!=nullptr)
        return true;
    else
        return false;
}
Scenario* RcmMimeData::getData() const
{
    return m_data;
}
