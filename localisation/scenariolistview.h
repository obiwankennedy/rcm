#ifndef SCENARIOLISTVIEW_H
#define SCENARIOLISTVIEW_H

#include <QListView>
#include <QMouseEvent>
#include <QMap>

#include "game.h"

class ScenarioListView : public QListView
{
    Q_OBJECT
public:
    ScenarioListView(QWidget* parent = nullptr);

    QMap<QString, Game *>* list() const;
    void setList(QMap<QString, Game *>* list);

protected:
    void mouseMoveEvent(QMouseEvent* event);

private:
    QMap<QString, Game *>* m_list;
};

#endif // SCENARIOLISTVIEW_H
