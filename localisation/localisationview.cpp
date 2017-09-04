#include <QVBoxLayout>
#include <QDebug>
#include <QEvent>
#include <QGraphicsSceneDragDropEvent>
#include <QWheelEvent>

#include "scenarioitem.h"
#include "localisationview.h"
#include "tableitem.h"
#include "roomitem.h"
#include "tableswizard.h"
#include "rcmmimedata.h"

#include <QTimer>
#include <QGraphicsTextItem>

#define REFRESH_TIME 60000//300000
#define PEN_W 5
#define ZVALUE 1000


Schedules::Schedules(int x, int y, int w, int h)
    : QGraphicsScene(x,y,w,h)
{
    m_timer = new QTimer();
    m_timer->setInterval(REFRESH_TIME);



    m_timeItem = new QGraphicsLineItem();
    m_timeItem->setLine(0,0,0,height());
    QPen pen(Qt::darkMagenta);
    pen.setStyle(Qt::DashLine);
    pen.setWidth(PEN_W);
    m_timeItem->setPen(pen);
    addItem(m_timeItem);
    m_timeItem->setZValue(ZVALUE);

    connect(m_timer,SIGNAL(timeout()),this,SLOT(updatePositionOfTime()));

    m_dayId = new QGraphicsTextItem();
    QFont font = m_dayId->font();
    font.setBold(true);
    font.setPointSize(25);
    m_dayId->setFont(font);
    m_dayId->setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable);
    addItem(m_dayId);
    m_dayId->setPos(width()/2, -20);


    updatePositionOfTime();
    m_timer->start();
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
    qreal totalHeight = height()/m_tableList.size();

    if(pos.y() <= totalHeight*0.2)
    {
        pos.setY(totalHeight*0.2);
    }
    if(pos.y() >= (((m_tableList.size()-1)*totalHeight)+totalHeight*0.2))
    {
        pos.setY((((m_tableList.size()-1)*totalHeight)+totalHeight*0.2));
    }
    else
    {
        qreal previousy = totalHeight*0.2;
        bool notFound = true;
        for(int i = 1; ((i < m_tableList.size()) && (notFound)); ++i)
        {
            qreal y = ((i*totalHeight)+totalHeight*0.2);
            if((pos.y() >= previousy)&&(pos.y() <= y))
            {
                qreal dist1 =  pos.y() - previousy;
                qreal dist2 = y - pos.y();

                if(dist1 < dist2)
                {
                    pos.setY(previousy);
                }
                else
                {
                    pos.setY(y);
                }
                notFound=false;

            }
            else
            {
                previousy = y;
            }

        }
    }
    //Compute y possible.
    return pos;
}

void Schedules::addScenario(Scenario* item, QPointF pos)
{
    ScenarioItem* sceneItem = new ScenarioItem();

    sceneItem->setMinutesInPixel(&m_minuteWidth);
    sceneItem->setTableInPixel(&m_tableHeight);
    sceneItem->setData(item);
    addItem(sceneItem);
    m_scenarioList.append(sceneItem);

    sceneItem->setPos(pos);

}

void Schedules::addTable(TableItem *table)
{
    m_tableList.append(table);
    addItem(table);
}

qreal Schedules::getStartOnDay() const
{
    return m_startOnDay;
}

void Schedules::setStartOnDay(const qreal &startOnDay)
{
    m_startOnDay = startOnDay;
    updatePositionOfTime();
}

void Schedules::readFromData(QDataStream &)
{

}

void Schedules::writeToData(QDataStream & in) const
{
    in << m_day;
    in << m_tableHeight;
    in << m_minuteWidth;
    in << m_startOnDay;
    in << m_tableList.size();

    for(auto tableItem : m_tableList)
    {
        tableItem->writeToData(in);
    }



    in << m_scenarioList.size();
    for(auto scenarioItem : m_scenarioList)
    {
        scenarioItem->writeToData(in);
    }
}

void Schedules::readDataToJson(QJsonObject &)
{

}

void Schedules::writeDataToJson(QJsonObject &)
{

}

QDomElement Schedules::writeDataToXml(QDomDocument &)
{

}

void Schedules::readDataFromXml(QDomNode &)
{

}

int Schedules::getDay() const
{
    return m_day;
}

void Schedules::setDay(int day)
{
    m_day = day;
    m_dayId->setPlainText(QStringLiteral("Jour n°%1").arg(m_day+1));
    updatePositionOfTime();
}

int Schedules::getNumberOfTable() const
{
    return m_tableList.size();
}

void Schedules::setNumberOfTable(const qreal &numberOfTable)
{
   // m_numberOfTable = numberOfTable;
}

qreal Schedules::minuteWidth() const
{
    return m_minuteWidth;
}

void Schedules::setMinuteWidth(qreal minuteWidth)
{
    m_minuteWidth = minuteWidth;
}

void Schedules::replaceScenario(ScenarioItem * item)
{
    QPointF point = computeClosePoint(item->pos());
    item->setPos(point);
}

void Schedules::updatePositionOfTime()
{
    QTime current = QTime::currentTime();
    qreal time=current.hour()*60+current.minute();

    qDebug() << current << time << m_startOnDay << m_timeItem->boundingRect();
    time-=m_startOnDay;
    time=time*m_minuteWidth;
    qDebug() << time;
    m_timeItem->setTransformOriginPoint(m_timeItem->boundingRect().center());
    m_timeItem->setPos(time-(m_timeItem->boundingRect().width()*m_minuteWidth*2),0);
}

qreal Schedules::getTableHeight() const
{
    return m_tableHeight;
}

void Schedules::setTableHeight(qreal height)
{
    m_tableHeight = height;
}





//////////////////////////



LocalisationView::LocalisationView(QGraphicsView* view,QWidget *parent) :
    QObject(parent),m_wizzard(nullptr),m_view(view)
{
    m_view->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
    m_view->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(m_view,SIGNAL(customContextMenuRequested(QPoint)),this,SLOT(contextMenuOnView(QPoint)));
    //m_view->setScene(m_scene);
    //m_view->ensureVisible(m_scene->sceneRect(),0,0);

    m_addPlayer= new QAction(tr("Add player"),this);
    m_delPlayer= new QAction(tr("Delete player"),this);
    m_startGame= new QAction(tr("Start"),this);
    m_gameEnd = new QAction(tr("End"),this);
    m_scheduleGame = new QAction(tr("Incoming"),this);
    m_showInfo = new QAction(tr("Show Players Info"),this);

    m_view->installEventFilter(this);
}

void LocalisationView::readFromData(QDataStream &)
{

}

void LocalisationView::writeToData(QDataStream & in) const
{
    in << m_scenes.size();
    for(auto scene : m_scenes)
    {
        auto schedule = dynamic_cast<Schedules*>(scene);
        schedule->writeToData(in);
    }
}

void LocalisationView::readDataToJson(QJsonObject &)
{

}

void LocalisationView::writeDataToJson(QJsonObject &)
{

}

QDomElement LocalisationView::writeDataToXml(QDomDocument &)
{

}

void LocalisationView::readDataFromXml(QDomNode &)
{

}

#include <QMouseEvent>
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
        else if(event->type() == QEvent::MouseButtonPress)
        {
            QMouseEvent* mEvent = dynamic_cast<QMouseEvent*>(event);

            if(mEvent->button() == Qt::LeftButton)
            {
                if(mEvent->modifiers() & Qt::ShiftModifier)
                {
                    m_view->setDragMode(QGraphicsView::ScrollHandDrag);
                }
            }
        }
        else if(event->type() == QEvent::MouseButtonRelease)
        {
            m_view->setDragMode(QGraphicsView::NoDrag);
        }
        else if(event->type() == QEvent::Wheel)
        {
            QWheelEvent* wEvent = dynamic_cast<QWheelEvent*>(event);

            wheelEventForView(wEvent);

        }
    }
    return QObject::eventFilter(obj,event);
}
#include <QMenu>
#include "playerinformationformdialog.h"
#include "playersinformationdialog.h"

void LocalisationView::contextMenuOnView(QPoint f)
{
    QMenu menu;

    QList<QGraphicsItem*> items = m_view->items(f);

    if(items.isEmpty())
    {
        m_addPlayer->setEnabled(false);
        m_delPlayer->setEnabled(false);
        m_startGame->setEnabled(false);
        m_gameEnd->setEnabled(false);
        m_scheduleGame->setEnabled(false);
        m_showInfo->setEnabled(false);
    }
    menu.addAction(m_addPlayer);
    menu.addAction(m_delPlayer);
    menu.addSeparator();
    menu.addAction(m_showInfo);
    menu.addSeparator();
    menu.addAction(m_startGame);
    menu.addAction(m_gameEnd);
    menu.addAction(m_scheduleGame);


    auto selectedAction = menu.exec(f);

    ScenarioItem* selectedItem = nullptr;
    for(auto item : items)
    {
        ScenarioItem* tmp = dynamic_cast<ScenarioItem*>(item);
        if((nullptr != tmp)&&(nullptr == selectedItem))
        {
            selectedItem = tmp;
        }
    }

    if(nullptr != selectedItem)
    {
        Scenario* sce = selectedItem->data();
        if(selectedAction == m_addPlayer)
        {
            PlayerInformationFormDialog dialog(m_view);
            if(QDialog::Accepted == dialog.exec())
            {
                sce->addPlayerInfo(dialog.getInfo());
                sce->increaseCurrentPlayerCount();
            }
        }
        else if (selectedAction == m_delPlayer)
        {
            sce->decreaseCurrentPlayerCount();
        }
        else if(selectedAction == m_showInfo)
        {
                PlayersInformationDialog dialog(m_view);
                dialog.setData(sce->getPlayerInformation());
                dialog.exec();

        }
        else if(selectedAction == m_startGame)
        {
            selectedItem->startGame();
        }
        else if(selectedAction == m_gameEnd)
        {
            selectedItem->endGame();
        }
        else if(selectedAction == m_scheduleGame)
        {
            selectedItem->scheduleGame();
        }
        selectedItem->update();
    }
}

void LocalisationView::setProperties()
{
    TablesWizard wizzard;
    if(QDialog::Accepted == wizzard.exec())
    {
        auto schedules = wizzard.getSchedule();
        int tableCount = wizzard.getTableCount();
        QStringList name = wizzard.getNameTable();

        for(auto day : *schedules)
        {
            Schedules* scene = new Schedules(0,0,1500,900);
            scene->setNumberOfTable(tableCount);
            scene->setDay(m_scenes.size());
            scene->setStartOnDay(day->getStartTime());


            int y = scene->height()/tableCount;
            for(int i = 0; i< tableCount; ++i)
            {
                TableItem* item = new TableItem();
                item->setName(name.at(i));
                connect(item,SIGNAL(minuteWidthChanged(qreal)),scene,SLOT(setMinuteWidth(qreal)));
                connect(item,SIGNAL(heightChanged(qreal)),scene,SLOT(setTableHeight(qreal)));
                item->setDay(day);
                item->setIdTable(i);
                item->setTableCount(tableCount);
                scene->addTable(item);
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
bool LocalisationView::wheelEventForView(QWheelEvent *event)
{
    if(event->modifiers() & Qt::ShiftModifier)
    {
        m_view->setResizeAnchor(QGraphicsView::AnchorUnderMouse);
        m_view->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
        // Scale the view / do the zoom
        double scaleFactor = 1.1;

        if((event->delta() > 0)&&(m_counterZoom<20))
        {
            m_view->scale(scaleFactor, scaleFactor);
            ++m_counterZoom;
            //RuleItem::setZoomLevel(scaleFactor);
            //ChildPointItem::setZoomLevel(scaleFactor);
        }
        else if(m_counterZoom>-20)
        {
            --m_counterZoom;
            m_view->scale(1.0 / scaleFactor, 1.0 / scaleFactor);
            //RuleItem::setZoomLevel(1.0 / scaleFactor);
            //ChildPointItem::setZoomLevel(1.0 / scaleFactor);
        }

        m_view->setResizeAnchor(QGraphicsView::NoAnchor);
        m_view->setTransformationAnchor(QGraphicsView::NoAnchor);
        return true;
    }
    else
        return false;
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
