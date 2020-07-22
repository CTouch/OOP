#ifndef DRAWINGBOARD_H
#define DRAWINGBOARD_H

#include <QWidget>
#include <QMenu>

#include "graph.h"

enum SelectType
{ // 当前的操作模式
    CURSOR,
    ELLIPSE,
    RECTANGLE,
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

private:
    void drawAll(QPainter &painter); // 按图层顺序重新绘制链表中所有图形
    void setupMenu(); // 初始化菜单栏
    void init(); // 初始化界面
//    void updateStatus(); // 选中图层发生改变后，相应的状态显示也要改变
    void newFile(); // 新建文件，即清空

public:
    void deleteGraph(); // 删除选中的图层
    void saveFile(QFile &file); // 写文件
    void readFile(QFile &file); // 读文件

signals:
    void ChangedSignal();

};

#endif // DRAWINGBOARD_H
