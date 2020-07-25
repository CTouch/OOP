#ifndef MYIMAGE_H
#define MYIMAGE_H
#include <QImage>
#include <QPainter>
#include <QRgb>
#include <QtCharts>
#include <iostream>
#include <vector>
//#include <QCustomPlot>
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
    //initial a (width * height) image filled with black
    myImage(int width,int height,Qt::GlobalColor color = Qt::black,QImage::Format = QImage::Format_ARGB32);

    //load image from .png file
    myImage(int index,const QString & FliePath);

    //read from .oop file
    myImage(int index,QDataStream &in);

public:
    virtual void draw(QPainter &painter) override; // 绘制

    //get the rgb histogram in 3 arrays
    virtual RGBHist GetHistArray();

    virtual Graph *duplicate() override; // 复制
    virtual void read(QDataStream &in) override; // 文件的读
    virtual void write(QDataStream &out) override; // 文件的写

public:
    QImage img;     //图像信息

private:
    //在长度为len的数组a中找到最大值并返回
    int GetMax(int a[],int len);

protected:

};

#endif // MYIMAGE_H
