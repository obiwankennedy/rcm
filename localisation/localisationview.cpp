#include <QVBoxLayout>

#include "localisationview.h"

LocalisationView::LocalisationView(QWidget *parent) :
    QWidget(parent),m_wizzard(NULL)
{
    QVBoxLayout* myBoxLayout = new QVBoxLayout();

    m_startWizzard = new QPushButton(tr("Wizzard"));
    m_view = new QGraphicsView();
    m_scene = new QGraphicsScene();
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

}
