#ifndef MYIMAGE_H
#define MYIMAGE_H
#include <QImage>
#include <QPainter>
#include <QRgb>
//#include <QtCharts>
#include "graph.h"

//the max value of r/g/b
const int MAX_VALUE_COLOR = 256;

class RGBHist
{
public:
    RGBHist(){};
    ~RGBHist(){};
    //三种颜色的直方图数据
    int r[MAX_VALUE_COLOR] = {0};
    int g[MAX_VALUE_COLOR] = {0};
    int b[MAX_VALUE_COLOR] = {0};
private:
};

class myImage:public Graph
{
public:
    myImage();


    //      功能描述；构造一个myImage
    //      参数描述：宽度为width，高度为height，填充颜色默认为黑色，格式默认为Format_ARGB32
    myImage(int width,int height,Qt::GlobalColor color = Qt::black,QImage::Format = QImage::Format_ARGB32);


    //      功能描述；构造一个myImage
    //      参数描述：读取自文件FilePath，所在图层编号为index
    myImage(int index,const QString & FliePath);

    //      功能描述；构造一个myImage，在读取.oop文件重建Drawing Board时使用
    //      参数描述：所在图层编号为index,数据流为in
    myImage(int index,QDataStream &in);

public:

    //      功能描述；绘制自身
    //      参数描述：painter为设置好QPainterDevice的画笔，
    //      返回值描述：void
    virtual void draw(QPainter &painter) override; // 绘制

    //      功能描述；获得自身的RGB信息
    //      返回值描述：RGBHist类，包括三个数组r,g,b分别储存三个颜色的直方图数据
    virtual RGBHist GetHistArray();

    //      功能描述；复制自身，并选中新增图层
    //      返回值描述：Graph类指针，成员信息除偏移量外和当前信息相同，
    virtual Graph *duplicate() override; // 复制

    //      功能描述；读取基本信息，如偏移量旋转角度等，读取图像信息
    //      参数描述：数据流为in
    //      函数算法描述：按照输出格式读取信息
    virtual void read(QDataStream &in) override; // 文件的读

    //      功能描述；输出基本信息，如偏移量旋转角度等，输出图像信息
    //      参数描述：数据流为out
    //      函数算法描述：按照格式输出信息
    virtual void write(QDataStream &out) override; // 文件的写

    //      功能描述；重载==运算符，所有信息相等时返回true
    //      参数描述：a为进行比较的对象
    //      返回值描述：true表示相同，false表示不同
    bool operator ==(const myImage & a);
public:
    QImage img;     //图像信息

private:
    //在长度为len的数组a中找到最大值并返回
    int GetMax(int a[],int len);
};

#endif // MYIMAGE_H
