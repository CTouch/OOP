#include "mypolygon.h"

myPolygon::myPolygon(int Index)
    : isClosed(false), min_x(100000), max_x(-1), min_y(100000), max_y(-1)
    , hover_point(nullptr)
{
    this->Index = Index;
    Stroke.setColor(Qt::black);
    Stroke.setWidth(3);
    Stroke.setStyle(Qt::SolidLine);
    Fill.setColor(Qt::gray);
    Fill.setStyle(Qt::SolidPattern);
    editType = EditType::DRAW; // 新建时肯定是初次绘制
    shape = Shape::SHAPE_POLYGON;
}

void myPolygon::draw(QPainter &painter)
{
    if (editType == UNSELECTED)
    {
        isBorderVisible = false;
    }
    else isBorderVisible = true;

    if (editType == CLOSING_POLYGON)
    { // 闭合多边形
        isClosed = true;
        if (hover_point)
        { // 删除此时的预览点
            point_list.pop_back();
            delete hover_point;
            hover_point = nullptr;

            // 重新计算中心
            min_y = min_x = 100000;
            max_y = max_x = -1;
            QPoint old_center = Center; // 记录旧的中心
            for (QPoint& point : point_list)
            {
                if (point.x() + old_center.x() < min_x) min_x = point.x() + old_center.x();
                if (point.x() + old_center.x() > max_x) max_x = point.x() + old_center.x();
                if (point.y() + old_center.y() < min_y) min_y = point.y() + old_center.y();
                if (point.y() + old_center.y() > max_y) max_y = point.y() + old_center.y();
            }
            graph_width = 1.1*(max_x - min_x);
            graph_height = 1.1*(max_y - min_y);
            // 更新中心
            Center.setX(int((min_x + max_x) / 2.0));
            Center.setY(int((min_y + max_y) / 2.0));

            // 更新原有点的相对坐标
            for (QPoint& point : point_list)
            {
                point.setX(point.x() + old_center.x() - Center.x());
                point.setY(point.y() + old_center.y() - Center.y());
            }
        }
    }
    if ((editType == DRAW || editType == HOVER_POLYGON) && !isClosed)
    { // 新增一点
        // 更新边框的四个边位置
        min_x = max_x = current_mouse.x();
        min_y = max_y = current_mouse.y();
        QPoint old_center = Center; // 记录旧的中心

        if (editType == HOVER_POLYGON)
        {
            if (hover_point)
            {
                point_list.pop_back(); // 弹出刚才的预览点
                *hover_point = current_mouse - Center;
            }
            else
            {
                hover_point = new QPoint(current_mouse - Center);
            }
        }
        else
        {
            if (hover_point)
            {
                delete hover_point;
                hover_point = nullptr;
            }
        }

        for (QPoint& point : point_list)
        {
            if (point.x() + old_center.x() < min_x) min_x = point.x() + old_center.x();
            if (point.x() + old_center.x() > max_x) max_x = point.x() + old_center.x();
            if (point.y() + old_center.y() < min_y) min_y = point.y() + old_center.y();
            if (point.y() + old_center.y() > max_y) max_y = point.y() + old_center.y();
        }
        graph_width = 1.1*(max_x - min_x);
        graph_height = 1.1*(max_y - min_y);
        // 更新中心
        Center.setX(int((min_x + max_x) / 2.0));
        Center.setY(int((min_y + max_y) / 2.0));

        // 更新原有点的相对坐标
        for (QPoint& point : point_list)
        {
            point.setX(point.x() + old_center.x() - Center.x());
            point.setY(point.y() + old_center.y() - Center.y());
        }

        point_list << current_mouse - Center;

        // 更新操作模式
        editType = HOVER_POLYGON;
    }
    else
    {
        if (hover_point)
        {
            point_list.pop_back();
            delete hover_point;
            hover_point = nullptr;
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

    if (isClosed)
    { // 这时候可能又缩放
        QPolygonF scaled_point_list;
        for (QPoint& point : point_list)
        {
            scaled_point_list << QPointF(scale_x * point.x(), scale_y * point.y());
        }
        painter.drawPolygon(scaled_point_list);
    }
    else
    {
        painter.drawPolygon(point_list);
    }

    // 绘制边
//    for (int i = 0; i < point_list.size()-1; ++i)
//    {
//        painter.drawLine(scale_x * point_list[i].x(), scale_y * point_list[i].y(), scale_x * point_list[i+1].x(), scale_y * point_list[i+1].y());
//    }
////    qDebug() << point_list;

//    painter.restore(); // 恢复画布
//    if (hover_point != nullptr)
//    { // 还在绘制状态，但是鼠标放松，只是预览将要绘制的边
//        QPen assist_pen = QPen();
//        assist_pen.setColor(Qt::red);
//        assist_pen.setStyle(Qt::DashLine);
//        painter.setPen(assist_pen);
//        // 这是在绘制，肯定不用考虑缩放问题
//        painter.drawLine(point_list.back() + Center, *hover_point);
//    }

    painter.restore();
    painter.setPen(original_pen); // 恢复画笔

    if (isBorderVisible)
    { // 绘制边框
        drawBorder(painter);
    }
}

Graph *myPolygon::duplicate()
{
    QPoint Offset = QPoint(qrand()%15, qrand()%15); // 复制图形中心的偏移
    // 默认拷贝构造函数
    myPolygon *polygon = new myPolygon(*this); // 新建复制的图形
    polygon->Center += Offset;
    polygon->isBorderVisible = true;
    this->editType = UNSELECTED;
    return polygon;
}

void myPolygon::setFill(QColor &color)
{
    Fill.setColor(color);
}

void myPolygon::setStroke(QColor &color)
{
    Stroke.setColor(color);
}

void myPolygon::setStroke(int width)
{
    if (width >= 0)
    {
        Stroke.setWidth(width);
    }
}

void myPolygon::read(QDataStream &in)
{
    hover_point = nullptr;
    in >> last_mouse >> current_mouse >> angle >> Index;
    in >> editType >> Opacity >> isBorderVisible >> onShift;
    in >> scale_x >> scale_y >> Center >> graph_width >> graph_height;
    in >> Fill >> Stroke >> border_tl >> border_br;
    in >> point_list >> isClosed >> Stroke;
    in >> min_x >> max_x >> min_y >> max_y;
}

void myPolygon::write(QDataStream &out)
{
    out << last_mouse << current_mouse << angle << Index;
    out << editType << Opacity << isBorderVisible << (onShift = false);
    out << scale_x << scale_y << Center << graph_width << graph_height;
    out << Fill << Stroke << border_tl << border_br;
    out << point_list << (isClosed = true) << Stroke;
    out << min_x << max_x << min_y << max_y;
}

bool myPolygon::isClosed_poly()
{
    return isClosed;
}

QBrush myPolygon::getBrush()
{
    return Fill;
}

QPen myPolygon::getStroke()
{
    return Stroke;
}





