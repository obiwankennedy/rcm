#include "scenariolistview.h"
#include <QDebug>
#include "localisation/rcmmimedata.h"
#include <QDrag>
ScenarioListView::ScenarioListView(QWidget* parent)
    : QListView(parent)
{

}

void ScenarioListView::mouseMoveEvent(QMouseEvent *event)
{
    qDebug() << "mouse move";

    QModelIndex tmp = indexAt(event->pos());

    QListView::mouseMoveEvent(event);

    qDebug() << "mouseMoveOnScenarioListOnPlanning" << tmp;
    if ((event->buttons() == Qt::LeftButton) && (tmp.isValid()))
    {
        QVariant var = tmp.data(Qt::UserRole);
        Scenario sce = var.value<Scenario>();

        Scenario* trueScenario = new Scenario();
        trueScenario->setReferenceScenario(&sce);



        QDrag *drag = new QDrag(this);
        RcmMimeData* mimeData = new RcmMimeData();

        mimeData->setScenario(trueScenario);
        drag->setMimeData(mimeData);
        auto game = m_list->value(trueScenario->getGameId());
        if(nullptr != game)
        {
            drag->setPixmap(*game->getPixmap());
        }

        Qt::DropAction dropAction = drag->exec();

    }
}

QMap<QString, Game *>* ScenarioListView::list() const
{
    return m_list;
}

void ScenarioListView::setList(QMap<QString, Game *>* list)
{
    m_list = list;
}
