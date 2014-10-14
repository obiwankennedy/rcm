#include <QVBoxLayout>
#include <QDebug>

#include "localisationview.h"
#include "tableitem.h"
#include "roomitem.h"

LocalisationView::LocalisationView(QWidget *parent) :
    QWidget(parent),m_wizzard(NULL)
{
    QVBoxLayout* myBoxLayout = new QVBoxLayout();

    m_startWizzard = new QPushButton(tr("Wizzard"));
    m_view = new QGraphicsView();
    /// @todo get screen size
    m_scene = new QGraphicsScene(0,0,800,600);
    m_view->setScene(m_scene);
    myBoxLayout->addWidget(m_view);
    myBoxLayout->addWidget(m_startWizzard);

    connect(m_startWizzard,SIGNAL(pressed()),this,SLOT(startWizzard()));


    setLayout(myBoxLayout);
}


void LocalisationView::startWizzard()
{
    if(NULL!=m_wizzard)
    {
        delete m_wizzard;
        m_wizzard = NULL;
    }
    m_wizzard = new TablesWizard();
    m_wizzard->setModal(true);
    if(m_wizzard->exec())
    {

        m_data = m_wizzard->getData();
        m_roomCount = m_wizzard->getRoomCount();

        addItemToScene();
    }
}
void LocalisationView::addItemToScene()
{
//    QList<Table*>* m_data;
//    int m_roomCount;

    QMap<QString, QList<Table*>* >* m_buildData = new QMap<QString, QList<Table*>* >();

    for(int i = 0; i<m_roomCount;++i)
    {
        QList<Table*>* tmp = new QList<Table*>();

        bool finished=false;
        QString previousRoomName;

        do
        {
            if(!m_data->isEmpty())
            {
                Table* tmpTable= m_data->at(0);
                if((previousRoomName.isNull())||(previousRoomName==tmpTable->getRoomName()))
                {
                    m_data->removeAt(0);
                    tmp->append(tmpTable);

                }
                else
                {
                    m_buildData->insert(previousRoomName,tmp);
                    finished=true;
                }
                previousRoomName=tmpTable->getRoomName();
            }
            else
            {
                if(!previousRoomName.isEmpty())
                {
                    m_buildData->insert(previousRoomName,tmp);
                }
                finished=true;
            }
        }while(!finished);
    }

    ///////////////////////////////////////////////

    int i = 0;
        foreach(QString room, m_buildData->keys())
        {
            QList<Table*>* tmp = m_buildData->value(room);
            qDebug() << "table count" << tmp->size();
            RoomItem* roomItem = new RoomItem();
            roomItem->setName(room);
            int w = m_scene->width()/m_roomCount;
            roomItem->setPos(w*i,0);
            //qDebug() << "roomItem pos:" <<w*i << "scene"<< m_scene->sceneRect();
            roomItem->setSize(w,m_scene->height());
            m_scene->addItem(roomItem);
            int j=0;
            int tableCount = tmp->size();
            int sizeTable=m_scene->height()/tableCount;
            foreach(Table* table, *tmp)
            {
              TableItem* tableitem = new TableItem();
              tableitem->setTable(table);
              tableitem->setSize(w*0.8,sizeTable/2);
              tableitem->setPos(w*0.1,j*sizeTable+sizeTable*0.2);
              //qDebug() << "tableItem pose:" <<w/2 << j*sizeTable;
              tableitem->setParentItem(roomItem);
              ++j;
            }
            ++i;
        }





}
