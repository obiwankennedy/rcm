#ifndef TABLESWIZARD_H
#define TABLESWIZARD_H

#include <QWizard>


#include "roommodel.h"

namespace Ui {
class TablesWizard;
}

class TablesWizard : public QWizard
{
    Q_OBJECT

public:
    explicit TablesWizard(QWidget *parent = 0);
    ~TablesWizard();

public slots:
    void currentPageChanged(int i);
    void manageRoomPage();
    void manageTableInRooms();
   // void managePersonPerTable();

    void currentRoomCount(int);
private:
    Ui::TablesWizard *ui;

    int m_roomCount;
};

#endif // TABLESWIZARD_H
