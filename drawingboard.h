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
    QString FilePath;           //文件路径，若不是从文件打开且未保存过则为空
    int selectedIndex = -1; // 当前选中的图层

    // 储存所有图形的链表
    QList<Graph*> AllGraphs;

    // 目前的操作模式
    SelectType selectType = CURSOR;

    // 选择图层的菜单栏
    QMenu *menu_layer;

protected:
    //      功能描述；重载鼠标移动事件，用于图像绘制和编辑
    //      参数描述：event为事件信息
    void mouseMoveEvent(QMouseEvent *event) override;

    //      功能描述；重载鼠标单击事件，用于更新编辑状态和图像绘制
    //      参数描述：event为事件信息
    void mousePressEvent(QMouseEvent *event) override;

    //      功能描述；重载鼠标释放事件，用于更新编辑状态和图像绘制
    //      参数描述：event为事件信息
    void mouseReleaseEvent(QMouseEvent *event) override;

    //      功能描述；重载按下键盘事件，检测shift键状态
    //      参数描述：event为事件信息
    void keyPressEvent(QKeyEvent *event) override;

    //      功能描述；重载释放键盘事件，检测shift键状态
    //      参数描述：event为事件信息
    void keyReleaseEvent(QKeyEvent *event) override;

    //      功能描述；重载paintEvent，按照自定义方式绘制Drawing Board
    //      函数算法描述：按照图层从小到大的方式绘制，体现图层的相互遮挡关系
    void paintEvent(QPaintEvent *) override;

public:

    //      功能描述；绘制Drawing Board所有图层信息
    //      参数描述：painter为设置好QPaintDevice的画笔，no_border若为true则不绘制选中边框，默认为false
    //      函数算法描述：按照图层从小到大的方式绘制，体现图层的相互遮挡关系
    void drawAll(QPainter &painter,bool no_border = false);

    //      功能描述；删除选中图层，并选中相邻图层
    bool deleteGraph();

    //      功能描述；保存信息
    //      参数描述：file为保存信息的位置
    void saveFile(QFile &file);

    //      功能描述；读取信息
    //      参数描述：file为读取信息的位置
    void readFile(QFile &file);

    //      功能描述；检查AllGraph中的图层信息和GraphList中的图层信息是否一致
    //      参数描述：GraphList为代比较的Graph类指针列表
    //      返回值描述：true为一致，false为不一致
    bool CheckEqual(const QList<Graph*> & GraphList);

    //      功能描述；确认当前Drawing Board是否存在未保存的修改
    //      参数描述：
    //      返回值描述：true为存在，false为不存在
    //      函数算法描述：若当前Drawing Board打开自.oop文件，则读取文件调用CheckEqual进行比较；
    //                  若为新建Drawing Board则由图层是否为零进行判断。
    bool UnsavedChange();

signals:
    //      功能描述；发送当前画板被修改的信号，主窗口收到之后进行updateStatus(),更新状态
    void ChangedSignal();
};

#endif // DRAWINGBOARD_H
