#ifndef MYIMAGE_H
#define MYIMAGE_H
#include <QImage>
#include <QPainter>
#include <QRgb>
#include <iostream>
#include <vector>
//#include <QCustomPlot>
#include "graph.h"

//the max value of r/g/b
#define MAX_VALUE_COLOR 256
class RGBHist
{
public:
    RGBHist(){};
    ~RGBHist(){};
//    QVector<int> r(256);
//    std::vector<int> r(256);
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
    myImage(int width,int height,QImage::Format);

    //load image from .png file
    myImage(int index,const QString & FliePath);

    //read from .oop file
    myImage(int index,QDataStream &in);
//    void draw(QPainter &painter) override;
public:
    virtual void draw(QPainter &painter) override; // 绘制
    virtual void showHist() override;
    virtual Graph *duplicate() override; // 复制
    virtual void read(QDataStream &in) override; // 文件的读
    virtual void write(QDataStream &out) override; // 文件的写
private:
    QImage img;

    int GetMax(int a[],int len);

protected:

};

#endif // MYIMAGE_H
