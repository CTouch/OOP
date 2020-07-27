#ifndef DRAWINGBOARD_H
#define DRAWINGBOARD_H

#include <QWidget>
#include <QMenu>

#include "graph.h"

//#define DRAWINGBOARD_DEBUG_ON 1

enum SelectType
{ // 当前的操作模式
    CURSOR,
    ELLIPSE,
    RECTANGLE,
    POLYGON,
    EDIT
};

class DrawingBoard : public QWidget
{
    Q_OBJECT
public:
    explicit DrawingBoard(QWidget *parent = nullptr);

private:
    bool onShift = false; // 监测shift键是否按下
    QPoint current_mouse = QPoint(-1, -1); // 当前鼠标的位置
    bool isClicking = false; // 左键是否按着（释放后才变为false）
    QColor lastColor; // 选择色板前的颜色

public:
    bool UnsavedChange = false;          //是否有未保存的修改
    bool doneFirstPaintevent = false;    //第一次绘制是否已经完成

    int selectedIndex = -1; // 当前选中的图层

    // 储存所有图形的链表
    QList<Graph*> AllGraphs;

    // 目前的操作模式
    SelectType selectType = CURSOR;

    // 选择图层的菜单栏
    QMenu *menu_layer;


protected:
    // 监测鼠标移动
    void mouseMoveEvent(QMouseEvent *event) override;

    // 监测鼠标左键单击
    void mousePressEvent(QMouseEvent *event) override;

    // 监测鼠标左键释放
    void mouseReleaseEvent(QMouseEvent *event) override;

    // 监测键盘按下
    void keyPressEvent(QKeyEvent *event) override;

    // 监测键盘松开
    void keyReleaseEvent(QKeyEvent *event) override;

    // 监测整个图像的绘制（通过update()函数激活)
    void paintEvent(QPaintEvent *) override;

public:
    void drawAll(QPainter &painter,bool no_border = false); // 按图层顺序重新绘制链表中所有图形,maybe_border决定是否可能绘制graph的border，默认为true
    bool deleteGraph(); // 删除选中的图层
    void saveFile(QFile &file); // 写文件
    void readFile(QFile &file); // 读文件

signals:
    //如果drawingboard上发生修改，则向主窗口发送signal，进行updatestatus()
    void ChangedSignal();

};

#endif // DRAWINGBOARD_H
