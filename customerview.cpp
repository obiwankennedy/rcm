#include "customerview.h"
#include "ui_customerview.h"

CustomerView::CustomerView(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CustomerView)
{
    ui->setupUi(this);
}

CustomerView::~CustomerView()
{
    delete ui;
}
