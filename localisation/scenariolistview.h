#ifndef SCENARIOLISTVIEW_H
#define SCENARIOLISTVIEW_H

#include <QMap>
#include <QMouseEvent>
#include <QTableView>

#include "game.h"

class ScenarioListView : public QTableView
{
    Q_OBJECT
public:
    ScenarioListView(QWidget* parent= nullptr);

    QMap<QString, Game*>* list() const;
    void setList(QMap<QString, Game*>* list);
signals:
    void updateSorting();

protected:
    void mouseMoveEvent(QMouseEvent* event);

private:
    QMap<QString, Game*>* m_list;
};

#endif // SCENARIOLISTVIEW_H
