#include "myellipse.h"


myEllipse::myEllipse(int Index)
{
    this->Index = Index;
    Stroke.setColor(Qt::black);
    Stroke.setWidth(0);
    Stroke.setStyle(Qt::SolidLine);
    Fill.setColor(Qt::gray);
    Fill.setStyle(Qt::SolidPattern);
    editType = EditType::DRAW; // 新建时肯定是初次绘制
    shape = Shape::SHAPE_ELLIPSE;
}


void myEllipse::draw(QPainter &painter)
{
    // 当图形没被选择时，不显示边框，否则都处于被选择或被操作的状态
    if (editType == UNSELECTED) isBorderVisible = false;
    else isBorderVisible = true;

    if (editType == DRAW)
    { // 初次绘制
        if (Center.x() < 0)
        { // 第一次点击，确定图形中心
            Center = current_mouse;
        }
        else
        {
            if (!onShift)
            {
                graph_width = 2*(current_mouse.x() - Center.x());
                graph_height = 2*(current_mouse.y() - Center.y());
            }
            else // 按住shift时，需要锁定比例
            {
                qreal ratio = 1.0 * graph_height / graph_width; // 记录上一时刻的比例
                graph_width = 2*(current_mouse.x() - Center.x()); // 宽度优先，设置椭圆的宽度
                graph_height = static_cast<int>(ratio * graph_width); // 按照比例设置椭圆的高度
            }
        }
    }

    // 根据裁剪比例确定边框
    updateBorder();

    // 储存原本的画笔
    QPen original_pen = painter.pen();

    // 储存原本的画布
    painter.save();

    // 移动画布到中心
    painter.translate(Center.x(), Center.y());

    // 按中心旋转画布
    painter.rotate(-angle);


    // 裁剪画布
    painter.setClipRect(QRect(border_tl, border_br));


    // 以椭圆本身的填充笔刷、描边画笔更新painter
    painter.setPen(Stroke);
    painter.setBrush(Fill);

    painter.setOpacity(Opacity/100.0); // 设置不透明度
    // 绘制
    painter.drawEllipse(QPoint(0, 0), int(scale_x * graph_width/2), int(scale_y * graph_height/2));

    painter.restore(); // 恢复画布
    painter.setPen(original_pen); // 恢复画笔

    if (isBorderVisible)
    { // 绘制边框
        drawBorder(painter);
    }
}



Graph *myEllipse::duplicate()
{
    QPoint Offset = QPoint(qrand()%15, qrand()%15); // 复制图形中心的偏移
    // 默认拷贝构造函数
    myEllipse *ellipse = new myEllipse(*this); // 新建复制的图形
    ellipse->Center += Offset;
    ellipse->isBorderVisible = true;
    this->editType = UNSELECTED;
    return ellipse;
}

void myEllipse::setFill(QColor &color)
{ // 更改填充笔刷的颜色
    Fill.setColor(color);
}

void myEllipse::setStroke(QColor &color)
{ // 更改描边画笔的颜色
    Stroke.setColor(color);
}


void myEllipse::setStroke(int width)
{
    if (width >= 0) // 画笔宽度有效时，设置画笔宽度
        Stroke.setWidth(width);
}

void myEllipse::write(QDataStream &out)
{ // 将所有数据以一定格式传入输出流out
    out << last_mouse << current_mouse << angle << Index;
    out << editType << Opacity << isBorderVisible << (onShift = false);
    out << scale_x << scale_y << Center << graph_width << graph_height;
    out << Fill << Stroke << border_tl << border_br;
}


QBrush myEllipse::getBrush()
{ // 返回填充笔刷
    return Fill;
}

void myEllipse::read(QDataStream &in)
{ // 以和write相同的格式读入输入流in
    in >> last_mouse >> current_mouse >> angle >> Index;
    in >> editType >> Opacity >> isBorderVisible >> onShift;
    in >> scale_x >> scale_y >> Center >> graph_width >> graph_height;
    in >> Fill >> Stroke >> border_tl >> border_br;
}



QPen myEllipse::getStroke()
{ // 返回描边画笔
    return Stroke;
}
