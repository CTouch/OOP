#ifndef HISTWIDGET_H
#define HISTWIDGET_H

#include <QWidget>
#include <QPoint>
//#include <algorithm>
#include "myimage.h"


//const QPoint TopLeft(10,10);
namespace Ui {
class HistWidget;
}

class HistWidget : public QWidget
{
    Q_OBJECT

public:
    explicit HistWidget(QWidget *parent = nullptr);
    HistWidget(const myImage &image, QWidget *parent = nullptr);
    ~HistWidget();


public:

    //show all histograms
    void ShowAllHist();
protected:
    void paintEvent(QPaintEvent *) override;

private:
    //show one histogram on a qlabel
    void ShowOneHist(const int hist[],QLabel *label,const Qt::GlobalColor & color);
private:
    Ui::HistWidget *ui;
    myImage image;
//    const QPoint TopLeft;
//    const QRect HistSize;
//    const int Interval = 5;
};

#endif // HISTWIDGET_H
