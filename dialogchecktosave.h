#ifndef DIALOGCHECKTOSAVE_H
#define DIALOGCHECKTOSAVE_H

#include <QDialog>

namespace Ui {
class DialogChecktoSave;
}

class DialogChecktoSave : public QDialog
{
    Q_OBJECT

public:
    explicit DialogChecktoSave(QWidget *parent = nullptr);
    ~DialogChecktoSave();

public:
    Ui::DialogChecktoSave *ui;

private slots:
    //按下Save
    void slotButtonSaveClicked();
    //按下Not to Save
    void slotButtonNottoSaveClicked();
    //按下Cancel
    void slotButtonCancelClicked();
signals:
    //按下Save
    void signalButtonSaveClicked();
    //按下Not to Save
    void signalButtonNottoSaveClicked();
    //按下Cancel
    void signalButtonCancelClicked();
};

#endif // DIALOGCHECKTOSAVE_H
