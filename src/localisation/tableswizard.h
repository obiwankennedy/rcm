#ifndef TABLESWIZARD_H
#define TABLESWIZARD_H

#include <QDialog>
#include <QTimeEdit>
#include <QTableWidgetItem>

#include "roommodel.h"
#include "tablemodel.h"
#include "serializable.h"

namespace Ui {
    class EventProperties;
}
class EventDay : public Serialisable
{

public:
    EventDay();
    EventDay(EventDay*);
    virtual ~EventDay();
    int getStartTime() const;
    void setStartTime(int startTime);

    int getEndTime() const;
    void setEndTime(int endTime);

    int getDuration();//in minutes
    int getId() const;
    void setId(int id);



    virtual void readFromData(QDataStream&);
    virtual void writeToData(QDataStream&) const;

    virtual void writeDataToJson(QJsonObject&);
    virtual void readDataFromJson(QJsonObject&);

    virtual QDomElement writeDataToXml(QDomDocument&);
    virtual void readDataFromXml(QDomNode&);

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
    QStringList getNameTable();
public slots:
    void numberOfDayChanged();
    void tableCountChanged();

private:
    Ui::EventProperties *ui;
    int m_roomCount;
    QHash<QTimeEdit*, QTableWidgetItem*> m_editors;
};

#endif // TABLESWIZARD_H
