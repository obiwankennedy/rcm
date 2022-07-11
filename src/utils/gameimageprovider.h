#ifndef GAMEIMAGEPROVIDER_H
#define GAMEIMAGEPROVIDER_H

#include <QMap>
#include <QNetworkAccessManager>
#include <QPixmap>
#include <QQuickImageProvider>

#include "gamemodel.h"

class GameImageProvider : public QQuickImageProvider
{
public:
    GameImageProvider(GameModel* m_gameModel);
    QPixmap requestPixmap(const QString& id, QSize* size, const QSize& requestedSize);

private:
    GameModel* m_gameModel;
    QString m_rootPath;
    QPixmap m_default;
    std::map<QString, QPixmap> m_cache;
};

#endif // GAMEIMAGEPROVIDER_H
