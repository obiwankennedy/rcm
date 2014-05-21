#ifndef CUSTOMERVIEW_H
#define CUSTOMERVIEW_H

#include <QMainWindow>

namespace Ui {
class CustomerView;
}

class CustomerView : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit CustomerView(QWidget *parent = 0);
    ~CustomerView();
    
private:
    Ui::CustomerView *ui;
};

#endif // CUSTOMERVIEW_H
