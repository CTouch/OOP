#include "dialognoselected.h"
#include "ui_dialognoselected.h"

DialogNoSelected::DialogNoSelected(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogNoSelected)
{
    ui->setupUi(this);
}

DialogNoSelected::~DialogNoSelected()
{
    delete ui;
}
