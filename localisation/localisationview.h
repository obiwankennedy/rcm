#ifndef LOCALISATIONVIEW_H
#define LOCALISATIONVIEW_H

#include <QWidget>
#include <QPushButton>
#include <QGraphicsView>

#include "tableswizard.h"
class Scenario;
class Schedules : public QGraphicsScene
{
    Q_OBJECT
public:
    Schedules(int, int,int,int);


    qreal getTableHeight() const;

    qreal minuteWidth() const;

public slots:
    void setTableHeight(qreal height);
    void setMinuteWidth(qreal minuteWidth);


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

private:
    QPointF computeClosePoint(QPointF pos);
    void addScenario(Scenario* item, QPointF pos);

private:
    Scenario* m_droppingItem;
    qreal m_tableHeight;
    qreal m_minuteWidth;

};

class LocalisationView : public QObject
{
    Q_OBJECT
public:
    explicit LocalisationView(QGraphicsView* view, QWidget *parent = 0);

public slots:
    void setProperties();
    void displayNextDay();
    void displayPreviousDay();

protected:
    bool eventFilter(QObject *obj, QEvent *event);
signals:


private:
    QPushButton* m_startWizzard;
    QGraphicsView* m_view;
    QList<QGraphicsScene*> m_scenes;


    TablesWizard* m_wizzard;
    QList<Table*>* m_data;
    int m_roomCount;
};

#endif // LOCALISATIONVIEW_H
