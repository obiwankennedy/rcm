#ifndef TABLESWIZARD_H
#define TABLESWIZARD_H

#include <QWizard>

namespace Ui {
class TablesWizard;
}

class TablesWizard : public QWizard
{
    Q_OBJECT

public:
    explicit TablesWizard(QWidget *parent = 0);
    ~TablesWizard();

private:
    Ui::TablesWizard *ui;
};

#endif // TABLESWIZARD_H
