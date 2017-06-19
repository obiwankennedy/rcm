#ifndef TABLESWIZARD_H
#define TABLESWIZARD_H

#include <QDialog>


#include "roommodel.h"
#include "tablemodel.h"

namespace Ui {
    class EventProperties;
}
class EventDay
{

public:
    EventDay();
    int getStartTime() const;
    void setStartTime(int startTime);

    int getEndTime() const;
    void setEndTime(int endTime);

    int getDuration();//in minutes
    int getId() const;
    void setId(int id);

private:
    int m_startTime;
    int m_endTime;
    int m_id;
};

class TablesWizard : public QDialog
{
    Q_OBJECT

public:
    explicit TablesWizard(QWidget *parent = 0);
    ~TablesWizard();

    QList<EventDay*>* getSchedule();
    int getTableCount() const;
public slots:
    void numberOfDayChanged();

private:
    Ui::EventProperties *ui;
    int m_roomCount;
};

#endif // TABLESWIZARD_H
