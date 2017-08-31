#ifndef RCMMIMEDATA_H
#define RCMMIMEDATA_H

#include <QMimeData>


#include "scenario.h"
/**
 * @brief allows drag and drop inside the application scope.
 */
class RcmMimeData : public QMimeData
{
    Q_OBJECT
public:
    /**
      *  @brief default constructor
      */
    RcmMimeData();
    /**
      *  @brief return true when given parameter describe a format is stored into the class
      */
    bool hasFormat ( const QString & mimeType ) const;
    //QStringList QMimeData::formats () const;
    
    /**
      *  @brief to define the draged and droped person.
      */
    void setScenario(Scenario*);
    /**
      *  @brief same utility of hasformat except is dedicated to person instance.
      */
    bool hasScenario() const;
    /**
      *  @brief return the person instance.
      */
    Scenario* getData() const;

private:
    QString m_format; /// const string representing the minetype of person
    Scenario* m_data; /// pointer to stored data
};
#endif // RCMMIMEDATA_H
