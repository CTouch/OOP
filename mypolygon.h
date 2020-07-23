#ifndef MYPOLYGON_H
#define MYPOLYGON_H

#include "graph.h"
#include <QColor>
#include <QPoint>
#include <QDebug>
#include <QtMath>
#include <QList>
#include <qrandom.h>


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
    QBrush getBrush() override;
    QPen getStroke() override;
private: // 私有成员
    QList<QPoint> point_list; // 多边形点集，有序
    bool isClosed; // 是否闭合
    QBrush Fill; // 填充笔刷
    QPen Stroke; // 描边画笔
};

#endif // MYPOLYGON_H
