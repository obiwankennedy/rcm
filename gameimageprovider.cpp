#include "gameimageprovider.h"
#include <QDebug>

GameImageProvider::GameImageProvider()
    : QQuickImageProvider(QQmlImageProviderBase::Pixmap)
{
    m_map = new QMap<QString,QPixmap*>();
    m_map->insert("default",new QPixmap(":/resources/nologo.png"));
}
QPixmap GameImageProvider::requestPixmap(const QString &id, QSize */*size*/, const QSize &/*requestedSize*/)
{
    //qDebug() << "id image:" << id << m_map;
    if(m_map->contains(id))
    {
        const QPixmap* pix = m_map->value(id);
        return *pix;
    }
    else
    {
        const QPixmap* pix = m_map->value("default");
        return *pix;
    }
}
void GameImageProvider::insertPixmap(QString str,QPixmap* map)
{
    if(!map->isNull())
    {
        m_map->insert(str,map);
    }
}
void GameImageProvider::resetData()
{
    m_map->clear();
    m_map->insert("default",new QPixmap(":/resources/nologo.png"));
}
