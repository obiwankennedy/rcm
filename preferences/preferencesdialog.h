#ifndef PREFERENCESDIALOG_H
#define PREFERENCESDIALOG_H

#include <QDialog>

namespace Ui
{
    class PreferencesDialog;
}

class PreferencesDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PreferencesDialog(QWidget* parent= nullptr);
    ~PreferencesDialog();

private slots:
    void on_m_openBtn_clicked();

private:
    Ui::PreferencesDialog* ui;
};

#endif // PREFERENCESDIALOG_H
