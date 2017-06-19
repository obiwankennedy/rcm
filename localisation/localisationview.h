#ifndef LOCALISATIONVIEW_H
#define LOCALISATIONVIEW_H

#include <QWidget>
#include <QPushButton>
#include <QGraphicsView>

#include "tableswizard.h"

class LocalisationView : public QObject
{
    Q_OBJECT
public:
    explicit LocalisationView(QGraphicsView* view, QWidget *parent = 0);

public slots:
    void setProperties();

protected:
    bool eventFilter(QObject *obj, QEvent *event);
signals:


private:
    QPushButton* m_startWizzard;
    QGraphicsView* m_view;
    QGraphicsScene* m_scene;


    TablesWizard* m_wizzard;
    QList<Table*>* m_data;
    int m_roomCount;

};

#endif // LOCALISATIONVIEW_H
