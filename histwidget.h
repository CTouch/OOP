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

    //根据image得到直方图
    HistWidget(const myImage &image, QWidget *parent = nullptr);

    ~HistWidget();


public:
    //show all histograms
    void ShowAllHist();

private:
    //将直方图数据hist[]用颜色color展示在label上
    void ShowOneHist(const int hist[],QLabel *label,const Qt::GlobalColor & color);
private:
    Ui::HistWidget *ui;
    myImage image;//将根据image获得直方图
};

#endif // HISTWIDGET_H
