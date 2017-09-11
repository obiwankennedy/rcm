#ifndef TABLEITEM_H
#define TABLEITEM_H

#include <QGraphicsObject>
#include "table.h"
#include "scenario.h"
#include "tableswizard.h"
#include "serializable.h"

class TableItem : public QGraphicsObject, public Serialisable
{
    Q_OBJECT
public:
    explicit TableItem();
    virtual ~TableItem();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);



    EventDay* day() const;
    void setDay(EventDay* day);

    int idTable() const;
    void setIdTable(int idTable);

    int tableCount() const;
    void setTableCount(int tableCount);

    QString name() const;
    void setName(const QString &name);

    virtual void readFromData(QDataStream&);
    virtual void writeToData(QDataStream&) const;

    virtual QDomElement writeDataToXml(QDomDocument&);
    virtual void readDataFromXml(QDomNode&);

    virtual void readDataFromJson(QJsonObject&);
    virtual void writeDataToJson(QJsonObject&);

signals:
    void heightChanged(qreal );
    void minuteWidthChanged(qreal );

private:
    QList<Scenario*> m_scenarioList;
    EventDay* m_day;
    int m_idTable;
    int m_tableCount;
    QString m_name;
};

#endif // TABLEITEM_H
