#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <iostream>
#include <QMainWindow>
#include <QDockWidget>
#include <QWidget>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QPoint>
#include <QRect>
#include <QPaintEvent>
#include <QPainter>
#include <QDebug>
#include <QToolButton>
#include <QMenu>
#include <QAction>
#include <QObject>
#include <QToolBar>
#include <QMenuBar>
#include <QStatusBar>
#include <QColorDialog>
#include <QFileDialog>
#include <QMessageBox>

#include "myimage.h"
#include "graph.h"
#include "myellipse.h"
#include "myrectangle.h"

enum SelectType
{ // 当前的操作模式
    CURSOR,
    ELLIPSE,
    RECTANGLE,
    EDIT
};

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    // 储存所有图形的链表
    QList<Graph*> AllGraphs;

    // 目前的操作模式
    SelectType selectType = CURSOR;

    // 选择图层的菜单栏
    QMenu *menu_layer;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

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
    bool onShift = false; // 监测shift键是否按下
    QPoint current_mouse = QPoint(-1, -1); // 当前鼠标的位置
    bool isClicking = false; // 左键是否按着（释放后才变为false）
    int selectedIndex = -1; // 当前选中的图层
    QColor lastColor; // 选择色板前的颜色

private:
    void drawAll(QPainter &painter); // 按图层顺序重新绘制链表中所有图形
    void setupMenu(); // 初始化菜单栏
    void init(); // 初始化界面
    void updateStatus(); // 选中图层发生改变后，相应的状态显示也要改变
    void deleteGraph(); // 删除选中的图层
    void saveFile(QFile &file); // 写文件
    void readFile(QFile &file); // 读文件
    void newFile(); // 新建文件，即清空

private slots: // 槽函数，当某个信号被触发后会被调用
    void menu_edit_triggered(QAction *action); // 当"编辑"菜单栏的内容被触发时，更新编辑模式
    void changeIndex(QAction *action); // 图层关系发生变化时，实时更新
    void action_file(QAction *action); // "文件"菜单被触发时，新建、储存、打开".oop"文件
    void on_opacity_slider_valueChanged(int value); // 不透明度滑条被移动时
    void on_button_fill_color_clicked(); // 更改 填充 颜色的按钮被点击时
    void on_button_stroke_color_clicked(); // 更改 描边 颜色的按钮被点击时
    void on_stroke_width_slider_valueChanged(int value); // 描边粗细的滑条被移动时
    void on_index_list_currentIndexChanged(int index); // 更改当前选中图形的图层（不同于menu_layer）
    void on_scale_x_valueChanged(int value); // x方向的放缩
    void on_scale_y_valueChanged(int value); // y方向的放缩
    void on_scale_lock_clicked(); // 锁定y、x方向的大小比例
    void setColor_fill(QColor color); // 在调色卡选择填充颜色时
    void setColor_stroke(QColor color); // 在调色卡选择描边颜色时
    void recoverColor_fill(); // 在调色卡选择填充颜色后没有选择"OK"，则不更换颜色，恢复原来的颜色
    void recoverColor_stroke(); // 在调色卡选择描边颜色后没有选择"OK"，则不更换颜色，恢复原来的颜色

//    void LoadImage();   //load image file
private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
