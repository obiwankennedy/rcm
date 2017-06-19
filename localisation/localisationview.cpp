#include <QVBoxLayout>
#include <QDebug>
#include <QEvent>


#include "localisationview.h"
#include "tableitem.h"
#include "roomitem.h"
#include "tableswizard.h"

LocalisationView::LocalisationView(QGraphicsView* view,QWidget *parent) :
    QObject(parent),m_wizzard(nullptr),m_view(view)
{
    m_scene = new QGraphicsScene(0,0,1500,900);
    m_view->setScene(m_scene);
    m_view->ensureVisible(m_scene->sceneRect(),0,0);



    m_view->installEventFilter(this);
}


bool LocalisationView::eventFilter(QObject *obj, QEvent *event)
{
    if(obj == m_view)
    {
        if(event->type() == QEvent::Resize)
        {
            m_view->fitInView(
                m_scene->itemsBoundingRect(),
                Qt::KeepAspectRatio);
        }
    }
    return QObject::eventFilter(obj,event);
}
void LocalisationView::setProperties()
{
    TablesWizard wizzard;
    if(QDialog::Accepted == wizzard.exec())
    {
        int tableCount = wizzard.getTableCount();
        int y = m_scene->height()/tableCount;
        for(int i = 0; i< tableCount; ++i)
        {
            TableItem* item = new TableItem();
            item->setIdTable(i);
            item->setTableCount(tableCount);
            m_scene->addItem(item);
            item->setPos(0,y*i);
        }

    }
}
