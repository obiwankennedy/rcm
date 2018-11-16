#ifndef SCENARIOITEM_H
#define SCENARIOITEM_H

#include <QGraphicsObject>
#include <QGraphicsSceneMouseEvent>

#include "scenario.h"
#include "idtranslator.h"
#include "serializable.h"
/**
 * @brief The ScenarioItem class
 */
class ScenarioItem : public QGraphicsObject, public Serialisable
{
    Q_OBJECT
public:
    enum State {Scheduled, Running, Done};
    explicit ScenarioItem();

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *);

    qreal* minutesInPixel() const;
    void setMinutesInPixel(qreal* minutesInPixel);

    Scenario* data() const;
    void setData(Scenario* data);

    qreal *tableInPixel() const;
    void setTableInPixel(qreal *tableInPixel);

    QVariant itemChange(GraphicsItemChange change, const QVariant &value);

    virtual void readFromData(QDataStream&);
    virtual void writeToData(QDataStream&) const;

    virtual void readDataFromJson(QJsonObject&);
    virtual void writeDataToJson(QJsonObject&);

    virtual QDomElement writeDataToXml(QDomDocument&);
    virtual void readDataFromXml(QDomNode&);

public slots:
    void startGame();
    void endGame();
    void scheduleGame();

signals:
    void positionChanged(Scenario*);
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *);

    QString stateToString();
private:
    Scenario* m_data;
    qreal* m_minutesInPixel;
    qreal* m_tableInPixel;
    IdTranslator* m_idTranslator;
    QColor m_color;
    bool m_lockUp;
    QGraphicsPixmapItem* m_locker;
    State m_state;
};

#endif // SCENARIOITEM_H
