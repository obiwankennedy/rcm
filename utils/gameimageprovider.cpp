#include "gameimageprovider.h"
#include "preferences/preferencesmanager.h"
#include <QDebug>
#include <QDir>

GameImageProvider::GameImageProvider(GameModel* gameModel)
    : QQuickImageProvider(QQmlImageProviderBase::Pixmap)
    , m_gameModel(gameModel)
    , m_default(":/resources/images/nologo.png")
{
}
QPixmap GameImageProvider::requestPixmap(const QString& id, QSize* /*size*/, const QSize& /*requestedSize*/)
{
    auto idx= id.toInt();
    auto pref= PreferencesManager::getInstance();
    m_rootPath= pref->value("imagesDirectory", QDir::homePath()).toString();
    auto index= m_gameModel->index(idx, 0);
    auto name= m_gameModel->data(index, GameModel::Name).toString();

    auto it= m_cache.find(name);
    if(it != m_cache.end())
        return it->second;

    auto path= QStringLiteral("%1/%2").arg(m_rootPath, name);
    if(QFile::exists(path))
    {
        auto pix= QPixmap(path, "png");
        if(!pix.isNull())
            m_cache.insert({name, pix});
        return pix;
    }

    return m_default;
}
