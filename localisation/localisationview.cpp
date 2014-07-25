#include <QVBoxLayout>

#include "localisationview.h"

LocalisationView::LocalisationView(QWidget *parent) :
    QWidget(parent)
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

}
