#include "myimage.h"

myImage::myImage()
{
}

myImage::myImage(int Index,const QString & FilePath):img(FilePath)
{
    this->Index = Index;
    editType = DRAW;
    shape = Shape::IMAGE;
    graph_width = img.width(); // width of image
    graph_height = img.height(); // height of image
    Center = QPoint(graph_width / 2, graph_height / 2); // 图形的中心点
    border_tl = QPoint(0,0); // 矩形辅助边框的左上角, top left, 未经过旋转和放缩
    border_br = QPoint(graph_width,graph_height); // 矩形辅助边框的右下角, bottom right, 未经过旋转和放缩

//    cv::Mat tp;
//    myImage2Mat(tp);
//    cv::imshow("testimshow",tp);
//    cv::waitKey(0);
    showHist();
}

myImage::myImage(int Index,QDataStream &in)
{
    this->Index = Index;
    editType = DRAW; // 新建时肯定是初次绘制
    shape = Shape::IMAGE;
    read(in);
}
void myImage::draw(QPainter &painter)
{
    // 当图形没被选择时，不显示边框，否则都处于被选择或被操作的状态
    if (editType == UNSELECTED) isBorderVisible = false;
    else isBorderVisible = true;

    // 储存原本的画笔
    QPen original_pen = painter.pen();

    // 储存原本的画布
    painter.save();
    // 移动、按中心旋转画布
    painter.translate(Center.x(), Center.y());
    painter.rotate(-angle);

    painter.setOpacity(Opacity/100.0); // 设置不透明度
    // 绘制
    QRect source = QRect(0,0,graph_width,graph_height);
    QRect target = QRect(-int(scale_x * graph_width/2), -int(scale_y * graph_height/2), int(scale_x * graph_width), int(scale_y * graph_height));
    painter.drawImage(target,img,source);

    painter.restore(); // 恢复画布
    painter.setPen(original_pen); // 恢复画笔

    if (isBorderVisible)
    { // 绘制边框
        drawBorder(painter);
    }

}

void myImage::write(QDataStream &out)
{
    out << last_mouse << current_mouse << angle << Index;
    out << editType << Opacity << isBorderVisible << (onShift = false);
    out << scale_x << scale_y << Center << graph_width << graph_height;
    out <<  border_tl << border_br;

    out << img;
}

Graph *myImage::duplicate()
{
    return nullptr;
}

void myImage::read(QDataStream &in)
{
    in >> last_mouse >> current_mouse >> angle >> Index;
    in >> editType >> Opacity >> isBorderVisible >> (onShift = false);
    in >> scale_x >> scale_y >> Center >> graph_width >> graph_height;
    in >> border_tl >> border_br;

    in >> img;
//    cv::Mat x;
//    cv::imshow("xx",x);
}
void myImage::showHist()
{
    cv::Mat tp;
    myImage2Mat(tp);
    int channels = 0;
    int histsize[] = {256};
    float midranges[] = {0,255};
    const float *ranges[]={midranges};
    cv::MatND ndHist;

    cv::calcHist(&tp,1,&channels,cv::Mat(),ndHist,1,histsize,ranges);

    cv::Mat b_drawImage = cv::Mat::zeros(cv::Size(256,256), CV_8UC4);
    double b_maxvalue;
    cv::minMaxLoc(ndHist,0,&b_maxvalue);
    for(int i = 0;i < 256;i++)
    {
        int value = round(256 * 0.9 * (ndHist.at<float>(i) / b_maxvalue));
        cv::line(b_drawImage,cv::Point(i,b_drawImage.rows - 1),cv::Point(i,b_drawImage.rows - 1 - value),cv::Scalar(255,0,0));
    }
    cv::imshow("Blue hist",b_drawImage);
    cv::waitKey(0);
}

void myImage::myImage2Mat(cv::Mat &target)
{
    if(img.format() == QImage::Format_ARGB32)
    {
        target = cv::Mat(img.height(),img.width(),CV_8UC4,(void*)img.constBits(),img.bytesPerLine());
    }
    else std::cout << "myImage2Mat: Unknow QImage::Formate!\n";
}

