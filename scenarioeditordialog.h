#ifndef SCENARIOEDITORDIALOG_H
#define SCENARIOEDITORDIALOG_H

#include <QDialog>


#include "scenariomodel.h"
#include "gameeditordelegate.h"
#include "leveldelegateitem.h"

namespace Ui {
class ScenarioEditorDialog;
}

class ScenarioEditorDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit ScenarioEditorDialog(QList<Game*>& l,QWidget *parent = 0);
    ~ScenarioEditorDialog();

    void setModel(ScenarioModel* model);
    
private:
    Ui::ScenarioEditorDialog *ui;
    GameEditorDelegate* m_gameDelegate;
    LevelDelegateItem* m_levelDelegate;
};

#endif // SCENARIOEDITORDIALOG_H
