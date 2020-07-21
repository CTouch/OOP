#include "histwidget.h"
#include "ui_histwidget.h"
HistWidget::HistWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HistWidget)
{
    ui->setupUi(this);
}

HistWidget::HistWidget(const myImage &image,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HistWidget),
    image(image)
{
    ui->setupUi(this);
}

HistWidget::~HistWidget()
{
    delete ui;
}

void HistWidget::paintEvent(QPaintEvent *)
{

}

void HistWidget::ShowOneHist(const int hist[],QLabel *label,const Qt::GlobalColor &color)
{
    int v_max = -1;
    for(int i = 0;i < MAX_VALUE_COLOR;i++)
    {
        std::cout << hist[i] << " ";
        v_max = std::max(v_max,hist[i]);
    }
    std::cout << std::endl;
    QPixmap chart(MAX_VALUE_COLOR,label->height());
    chart.fill(Qt::black);
    QPainter painter(&chart);
    painter.setPen(color);
    for(int i = 0;i < MAX_VALUE_COLOR;i++)
    {
//        painter.drawLine(QPoint(i,0),QPoint(i,label->height() * hist[i] / v_max));
        painter.drawLine(QPoint(i,label->height() - 1),QPoint(i,label->height() - 1 - label->height() * hist[i] / v_max));
//        painter.drawLine(QPoint(i,0),QPoint(i,i));
    }
    painter.end();
    chart.save("~/testsave.png");
//    chart = chart.scaled(label->width(),label->height());
    label->setPixmap(chart);
    label->setScaledContents(true);
}


void HistWidget::ShowAllHist()
{
    RGBHist hist = image.GetHistArray();
    ShowOneHist(hist.r,this->ui->R_hist,Qt::red);
    ShowOneHist(hist.g,this->ui->G_hist,Qt::green);
    ShowOneHist(hist.b,this->ui->B_hist,Qt::blue);
}
