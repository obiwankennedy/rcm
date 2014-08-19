#ifndef GAMEIMAGEPROVIDER_H
#define GAMEIMAGEPROVIDER_H

#include <QQuickImageProvider>
#include <QMap>
#include <QPixmap>

class GameImageProvider : public QObject, public QQuickImageProvider
{
    Q_OBJECT
public:
    GameImageProvider();
    QPixmap requestPixmap(const QString &id, QSize *size, const QSize &requestedSize);


public slots:
    void insertPixmap(QString,QPixmap*);

private:
    QMap<QString,QPixmap*>* m_map;

};

#endif // GAMEIMAGEPROVIDER_H
