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

void HistWidget::ShowOneHist(const int hist[],QLabel *label,const Qt::GlobalColor &color)
{
    int v_max = -1; //最大值，用于归一化处理
    for(int i = 0;i < MAX_VALUE_COLOR;i++)  //找到最大值
    {
        v_max = std::max(v_max,hist[i]);
    }
    QPixmap chart(MAX_VALUE_COLOR,label->height()); //建立宽度为MAX_VALUE_COLOR,高度为label高度的QPixmap，方便后续处理
    chart.fill(Qt::black);          //初始化为纯黑色
    QPainter painter(&chart);       //创建画笔
    painter.setPen(color);          //设置颜色为color
    for(int i = 0;i < MAX_VALUE_COLOR;i++)
    {
        //归一化数据之后绘制相应高度的线构成直方图
        painter.drawLine(QPoint(i,label->height() - 1),QPoint(i,label->height() - 1 - label->height() * hist[i] / v_max));
    }
    painter.end();
//    chart.save("~/testsave.png");
    label->setPixmap(chart);        //将图片展示在label上
    label->setScaledContents(true); //大小自适应
}


void HistWidget::ShowAllHist()
{
    RGBHist hist = image.GetHistArray();            //获得直方图数据
    ShowOneHist(hist.r,this->ui->R_hist,Qt::red);   //展示r直方图
    ShowOneHist(hist.g,this->ui->G_hist,Qt::green); //展示g直方图
    ShowOneHist(hist.b,this->ui->B_hist,Qt::blue);  //展示b直方图
}
