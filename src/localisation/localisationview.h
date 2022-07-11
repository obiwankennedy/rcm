#ifndef LOCALISATIONVIEW_H
#define LOCALISATIONVIEW_H

#include <QAction>
#include <QGraphicsLineItem>
#include <QGraphicsView>
#include <QPushButton>
#include <QTimer>
#include <QWidget>

#include "serializable.h"
#include "tableitem.h"
#include "tableswizard.h"

class Scenario;
class ScenarioItem;
class Schedules : public QGraphicsScene, public Serialisable
{
    Q_OBJECT
public:
    Schedules(qreal, qreal, qreal, qreal);

    qreal getTableHeight() const;

    qreal minuteWidth() const;

    int getNumberOfTable() const;
    void setNumberOfTable(const qreal&);

    QPointF computeClosePoint(QPointF pos);

    int getDay() const;
    void setDay(int day);

    qreal getStartOnDay() const;
    void setStartOnDay(const qreal& startOnDay);

    virtual void readFromData(QDataStream&);
    virtual void writeToData(QDataStream&) const;

    virtual void readDataFromJson(QJsonObject&);
    virtual void writeDataToJson(QJsonObject&);

    virtual QDomElement writeDataToXml(QDomDocument&);
    virtual void readDataFromXml(QDomNode&);

    void appendTableItem(TableItem* item, QPointF pos);
public slots:
    void setTableHeight(qreal height);
    void setMinuteWidth(qreal minuteWidth);
    void replaceScenario(ScenarioItem*);
    void updatePositionOfTime();
    // void visibleWidthChanged();

protected:
    void dragEnterEvent(QGraphicsSceneDragDropEvent* event);
    /**
     * @brief dropEvent
     * @param event
     */
    void dropEvent(QGraphicsSceneDragDropEvent* event);
    /**
     * @brief dragMoveEvent
     * @param event
     */
    void dragMoveEvent(QGraphicsSceneDragDropEvent* event);

    void addScenarioItem(ScenarioItem* sceneItem, QPointF pos);

private:
    void addScenario(Scenario* item, QPointF pos);

private:
    Scenario* m_droppingItem;
    qreal m_tableHeight= 200;
    qreal m_minuteWidth= 10.;
    qreal m_startOnDay;

    // qreal m_numberOfTable;
    QTimer* m_timer;
    QGraphicsLineItem* m_timeItem;
    QGraphicsTextItem* m_dayId;
    int m_day;

    QList<ScenarioItem*> m_scenarioList;
    QList<TableItem*> m_tableList;
};

class LocalisationView : public QObject, public Serialisable
{
    Q_OBJECT
public:
    explicit LocalisationView(QGraphicsView* view, QWidget* parent= nullptr);

    virtual void readFromData(QDataStream&);
    virtual void writeToData(QDataStream&) const;

    virtual void readDataFromJson(QJsonObject&);
    virtual void writeDataToJson(QJsonObject&);

    virtual QDomElement writeDataToXml(QDomDocument&);
    virtual void readDataFromXml(QDomNode&);

    void appendTableItem(TableItem* item, QPointF pos);
public slots:
    void setProperties();
    void displayNextDay();
    void displayPreviousDay();

    void contextMenuOnView(QPoint p);

protected:
    bool eventFilter(QObject* obj, QEvent* event);
    bool wheelEventForView(QWheelEvent* event);

private:
    int m_counterZoom;
    QPushButton* m_startWizzard= nullptr;
    TablesWizard* m_wizzard= nullptr;
    QGraphicsView* m_view= nullptr;
    QList<QGraphicsScene*> m_scenes;
    QList<Table*>* m_data= nullptr;
    int m_roomCount;

    QAction* m_addPlayer= nullptr;
    QAction* m_delPlayer= nullptr;
    QAction* m_showInfo= nullptr;
    QAction* m_startGame= nullptr;
    QAction* m_gameEnd= nullptr;
    QAction* m_scheduleGame= nullptr;
    QAction* m_removeGame= nullptr;
};

#endif // LOCALISATIONVIEW_H
