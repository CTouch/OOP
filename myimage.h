#ifndef MYIMAGE_H
#define MYIMAGE_H
#include <QImage>
#include <QPainter>
#include <opencv2/opencv.hpp>

#include "graph.h"
class myImage:public Graph
{
public:
    myImage();

    //load image from .png file
    myImage(int index,const QString & FliePath);

    //read from .oop file
    myImage(int index,QDataStream &in);
//    void draw(QPainter &painter) override;
public:
    virtual void draw(QPainter &painter) override; // 绘制
    virtual Graph *duplicate() override; // 复制
    virtual void read(QDataStream &in) override; // 文件的读
    virtual void write(QDataStream &out) override; // 文件的写
    virtual void showHist() override;
    virtual void myImage2Mat(cv::Mat &target);
private:
    QImage img;


protected:

};

#endif // MYIMAGE_H
