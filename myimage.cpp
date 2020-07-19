#include "myimage.h"


myImage::myImage()
{
}

myImage::myImage(int width,int height,QImage::Format format)
    :img(width,height,format)
{
    img.fill(Qt::black);
    shape = Shape::IMAGE;
    graph_width = img.width();
    graph_height = img.height();
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

    std::cout << "begin show hist!\n";
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
}

int myImage::GetMax(int a[],int len)
{
    int result = a[0];
    for(int i = 1;i < len;i++)
    {
        if(result < a[i]) result = a[i];
    }
    return result;
}

//void myImage::
void myImage::showHist()
{
    RGBHist res;
    for(int i = 0;i < img.width();i++)
    {
        for(int j = 0;j < img.height();j++)
        {
            QRgb tp = img.pixel(i,j);
            int red = qRed(tp);
            int green = qGreen(tp);
            int blue = qBlue(tp);
            res.r[red]++;
            res.g[green]++;
            res.b[blue]++;
        }
    }
    int max_red = GetMax(res.r,MAX_VALUE_COLOR);

    myImage tp(256,256,QImage::Format_ARGB32);
//    QImage tp(256,256,QImage::Format_ARGB32);
//    tp.fill(Qt::black);
    QPainter painter(&(tp.img));
    painter.setPen(Qt::red);
    for(int i = 0;i < 256;i++)
    {
        painter.drawLine(i,0,i,256.0 * res.r[i] / max_red);
//        std::cout << res.r[i] << "\t";
//        if(i%10 == 0)  std::cout << std::endl;
    }
//    std::cout << "try save hist!\n";
//    if (tp.img.save("~/testhist.bmp","BMP"))
//        std::cout << "Save hist!\n";
//    else std::cout <<"failed to save hist!\n";
    painter.end();

}
