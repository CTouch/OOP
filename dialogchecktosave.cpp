#include "dialogchecktosave.h"
#include "ui_dialogchecktosave.h"

DialogChecktoSave::DialogChecktoSave(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogChecktoSave)
{
    ui->setupUi(this);
    //连接信号槽
    connect(ui->buttonSave, &QPushButton::clicked, this, [&](){
        // 按下save之后执行的lambda表达式
        emit signalButtonSaveClicked(); // 发射按下save按钮的信号
        disconnect();
        close();
    });
    connect(ui->buttonNottoSave,&QPushButton::clicked, this, [&](){
        // 按下not to save之后执行的lambda表达式
        emit signalButtonNottoSaveClicked(); // 发射按下not to save按钮的信号
        disconnect();
        close();
    });
    connect(ui->buttonCancel,&QPushButton::clicked, this, [&](){
        // 按下cancel之后执行的lambda表达式
        emit signalButtonCancelClicked(); // 发射按下cancel按钮的信号
        disconnect();
        close();
    });
}

DialogChecktoSave::~DialogChecktoSave()
{
    delete ui;
}
