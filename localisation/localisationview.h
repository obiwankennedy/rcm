#ifndef LOCALISATIONVIEW_H
#define LOCALISATIONVIEW_H

#include <QWidget>
#include <QPushButton>
#include <QGraphicsView>

#include "tableswizard.h"

class LocalisationView : public QWidget
{
    Q_OBJECT
public:
    explicit LocalisationView(QWidget *parent = 0);

signals:

public slots:
    void startWizzard();

private:
    QPushButton* m_startWizzard;
    QGraphicsView* m_view;
    QGraphicsScene* m_scene;


    TablesWizard* m_wizzard;
};

#endif // LOCALISATIONVIEW_H
