#ifndef DIALOGNOSELECTED_H
#define DIALOGNOSELECTED_H

#include <QDialog>

namespace Ui {
class DialogNoSelected;
}

class DialogNoSelected : public QDialog
{
    Q_OBJECT

public:
    explicit DialogNoSelected(QWidget *parent = nullptr);
    ~DialogNoSelected();

private:
    Ui::DialogNoSelected *ui;
};

#endif // DIALOGNOSELECTED_H
