#include "dialogchecktosave.h"
#include "ui_dialogchecktosave.h"

DialogChecktoSave::DialogChecktoSave(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogChecktoSave)
{
    ui->setupUi(this);
    //连接信号槽
    connect(ui->buttonSave,&QPushButton::clicked,this,&DialogChecktoSave::slotButtonSaveClicked);
    connect(ui->buttonNottoSave,&QPushButton::clicked,this,&DialogChecktoSave::slotButtonNottoSaveClicked);
    connect(ui->buttonCancel,&QPushButton::clicked,this,&DialogChecktoSave::slotButtonCancelClicked);
}

DialogChecktoSave::~DialogChecktoSave()
{
    delete ui;
}


void DialogChecktoSave::slotButtonSaveClicked()
{
    signalButtonSaveClicked();
    disconnect();
    close();
}

void DialogChecktoSave::slotButtonNottoSaveClicked()
{
    signalButtonNottoSaveClicked();
    disconnect();
    close();
}

void DialogChecktoSave::slotButtonCancelClicked()
{
    signalButtonCancelClicked();
    disconnect();
    close();
}
