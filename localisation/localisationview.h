#ifndef LOCALISATIONVIEW_H
#define LOCALISATIONVIEW_H

#include <QWidget>
#include <QPushButton>
#include <QGraphicsView>
#include <QTimer>
#include <QGraphicsLineItem>
#include <QAction>

#include "tableswizard.h"
#include "serializable.h"
#include "tableitem.h"


class Scenario;
class ScenarioItem;
class Schedules : public QGraphicsScene, public Serialisable
{
    Q_OBJECT
public:
    Schedules(int, int,int,int);


    qreal getTableHeight() const;

    qreal minuteWidth() const;

    int getNumberOfTable() const;
    void setNumberOfTable(const qreal &numberOfTable);

    QPointF computeClosePoint(QPointF pos);

    int getDay() const;
    void setDay(int day);

    qreal getStartOnDay() const;
    void setStartOnDay(const qreal &startOnDay);


    virtual void readFromData(QDataStream&);
    virtual void writeToData(QDataStream&) const;

    virtual void readDataFromJson(QJsonObject&);
    virtual void writeDataToJson(QJsonObject&);

    virtual QDomElement writeDataToXml(QDomDocument&);
    virtual void readDataFromXml(QDomNode&);

    void appendTableItem(TableItem *item, QPointF pos);
public slots:
    void setTableHeight(qreal height);
    void setMinuteWidth(qreal minuteWidth);
    void replaceScenario(ScenarioItem*);
    void updatePositionOfTime();


protected:
    void dragEnterEvent ( QGraphicsSceneDragDropEvent * event );
    /**
     * @brief dropEvent
     * @param event
     */
    void dropEvent ( QGraphicsSceneDragDropEvent * event );
    /**
     * @brief dragMoveEvent
     * @param event
     */
    void dragMoveEvent( QGraphicsSceneDragDropEvent * event );

    void addScenarioItem(ScenarioItem *sceneItem, QPointF pos);
private:
    void addScenario(Scenario* item, QPointF pos);


private:
    Scenario* m_droppingItem;
    qreal m_tableHeight;
    qreal m_minuteWidth;
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
    explicit LocalisationView(QGraphicsView* view, QWidget *parent = 0);

    virtual void readFromData(QDataStream&);
    virtual void writeToData(QDataStream&) const;

    virtual void readDataFromJson(QJsonObject&);
    virtual void writeDataToJson(QJsonObject&);


    virtual QDomElement writeDataToXml(QDomDocument&);
    virtual void readDataFromXml(QDomNode&);

    void appendTableItem(TableItem *item, QPointF pos);
public slots:
    void setProperties();
    void displayNextDay();
    void displayPreviousDay();

    void contextMenuOnView(QPoint p);

protected:
    bool eventFilter(QObject *obj, QEvent *event);
    bool wheelEventForView(QWheelEvent *event);
signals:


private:
    int m_counterZoom;
    QPushButton* m_startWizzard;
    QGraphicsView* m_view;
    QList<QGraphicsScene*> m_scenes;
    TablesWizard* m_wizzard;
    QList<Table*>* m_data;
    int m_roomCount;


    QAction* m_addPlayer;
    QAction* m_delPlayer;
    QAction* m_showInfo;
    QAction* m_startGame;
    QAction* m_gameEnd;
    QAction* m_scheduleGame;
    QAction* m_removeGame;

};

#endif // LOCALISATIONVIEW_H
