#ifndef MYPOLYGON_H
#define MYPOLYGON_H

#include "graph.h"
#include <QColor>
#include <QPoint>
#include <QDebug>
#include <QtMath>
#include <QList>
#include <qrandom.h>
#include <QSharedPointer>


class myPolygon : public Graph
{
public:
    // 构造器
    myPolygon(int Index);
public: // 基类纯虚函数的继承
    void draw(QPainter &painter) override;
    Graph *duplicate() override;
    void setFill(QColor &color) override;
    void setStroke(QColor &color) override;
    void setStroke(int width) override;
    void read(QDataStream &in) override;
    void write(QDataStream &out) override;
    bool isClosed_poly() override;
    QBrush getBrush() override;
    QPen getStroke() override;
private: // 私有成员
    QPolygon point_list; // 多边形点集，有序，记录相对中心的坐标
    bool isClosed; // 是否闭合
    QBrush Fill; // 填充笔刷
    QPen Stroke; // 描边画笔
    QPoint* hover_point; // 预览的点，未加入点集，记录绝对坐标
    int min_x; // 最小的x值
    int max_x; // 最大的x值
    int min_y; // 最小的y值
    int max_y; // 最大的y值
};

#endif // MYPOLYGON_H
