#ifndef MYRECTANGLE_H
#define MYRECTANGLE_H
#include "graph.h"
#include <QColor>
#include <QPoint>
#include <QDebug>
#include <QtMath>
#include <qrandom.h>

class myRectangle : public Graph
{
public:
    // 构造器
    myRectangle(int Index);

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
    bool operator == (const myRectangle& rectangle) const;

private: // 私有成员
    QBrush Fill; // 填充笔刷
    QPen Stroke; // 描边画笔
};

#endif // MYRECTANGLE_H
