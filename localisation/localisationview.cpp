#include <QVBoxLayout>
#include <QDebug>
#include <QEvent>
#include <QGraphicsSceneDragDropEvent>

#include "scenarioitem.h"
#include "localisationview.h"
#include "tableitem.h"
#include "roomitem.h"
#include "tableswizard.h"
#include "rcmmimedata.h"


Schedules::Schedules(int x, int y, int w, int h)
    : QGraphicsScene(x,y,w,h)
{

}
void Schedules::dragMoveEvent(QGraphicsSceneDragDropEvent *event)
{
    event->acceptProposedAction();
}
void Schedules::dragEnterEvent ( QGraphicsSceneDragDropEvent * event )
{
    const RcmMimeData* data= qobject_cast<const RcmMimeData*>(event->mimeData());
    if(nullptr != data)
    {
        if (data->hasFormat("rcm/scenario-item"))
        {
            event->acceptProposedAction();
        }
    }
}

void Schedules::dropEvent ( QGraphicsSceneDragDropEvent * event )
{
    const RcmMimeData* data = qobject_cast<const RcmMimeData*>(event->mimeData());
    if(nullptr != data)
    {
        if (data->hasFormat("rcm/scenario-item"))
        {
            Scenario* item = data->getData();
            if(item)
            {
                addScenario(item,computeClosePoint(event->scenePos()));
                m_droppingItem = item;
            }
        }
    }

}

QPointF Schedules::computeClosePoint(QPointF pos)
{
    return pos;
}

void Schedules::addScenario(Scenario* item, QPointF pos)
{
    ScenarioItem* sceneItem = new ScenarioItem();
    sceneItem->setData(item);
    addItem(sceneItem);

    sceneItem->setPos(pos);

}





//////////////////////////



LocalisationView::LocalisationView(QGraphicsView* view,QWidget *parent) :
    QObject(parent),m_wizzard(nullptr),m_view(view)
{

    //m_view->setScene(m_scene);
    //m_view->ensureVisible(m_scene->sceneRect(),0,0);



    m_view->installEventFilter(this);
}


bool LocalisationView::eventFilter(QObject *obj, QEvent *event)
{
    if(obj == m_view)
    {
        if(event->type() == QEvent::Resize)
        {
            auto scene = m_view->scene();
            if(nullptr != scene)
            {
                m_view->fitInView(scene->itemsBoundingRect(),Qt::KeepAspectRatio);
            }
        }
    }
    return QObject::eventFilter(obj,event);
}
void LocalisationView::setProperties()
{
    TablesWizard wizzard;
    if(QDialog::Accepted == wizzard.exec())
    {
        auto schedules = wizzard.getSchedule();
        int tableCount = wizzard.getTableCount();

        for(auto day : *schedules)
        {
            Schedules* scene = new Schedules(0,0,1500,900);

            int y = scene->height()/tableCount;
            for(int i = 0; i< tableCount; ++i)
            {
                TableItem* item = new TableItem();
                item->setDay(day);
                item->setIdTable(i);
                item->setTableCount(tableCount);
                scene->addItem(item);
                item->setPos(0,y*i);
            }
            m_scenes.append(scene);
        }
    }

    if(!m_scenes.isEmpty())
    {
        m_view->setScene(m_scenes.at(0));
        m_view->ensureVisible(m_scenes.at(0)->sceneRect(),0,0);
    }
}
void LocalisationView::displayNextDay()
{
    auto scene = m_view->scene();
    int i = m_scenes.indexOf(scene);
    ++i;
    if(i<0)
    {
        i =0;
    }
    else if(i>=m_scenes.size())
    {
        i = m_scenes.size()-1;
    }
    m_view->setScene(m_scenes.at(i));
}

void LocalisationView::displayPreviousDay()
{
    auto scene = m_view->scene();
    int i = m_scenes.indexOf(scene);
    --i;
    if(i<0)
    {
        i =0;
    }
    else if(i>=m_scenes.size())
    {
        i = m_scenes.size()-1;
    }
    m_view->setScene(m_scenes.at(i));
}
