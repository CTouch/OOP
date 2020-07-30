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
#include <QResizeEvent>

#include "myimage.h"
#include "graph.h"
#include "myellipse.h"
#include "myrectangle.h"
#include "histwidget.h"
#include "drawingboard.h"
#include "dialognoselected.h"
#include "dialogchecktosave.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    // 目前的操作模式
    SelectType selectType = CURSOR;

    // 选择图层的菜单栏
    QMenu *menu_layer;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    // 监测鼠标左键单击
    void mousePressEvent(QMouseEvent *event) override;

    // 检测窗口大小变换
    void resizeEvent(QResizeEvent *event) override;

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
    QColor lastColor; // 选择色板前的颜色

private:
    //      功能描述；按图层顺序重新绘制链表中所有图形
    //      参数描述：画笔painter
    void drawAll(QPainter &painter);

    //      功能描述；初始化菜单栏
    void setupMenu();

    //      功能描述；初始化界面
    void init();

    //      功能描述；删除当前选中的图层
    void deleteGraph();

    //      功能描述；储存文件信息
    //      参数描述：待写入的文件file
    void saveFile(QFile &file);

    // 保存为.oop的入口，true为保存，false为未保存
    bool ActionSave();

    //      功能描述；读取文件信息
    //      参数描述：待读取的文件file
    void readFile(QFile &file);

    // 读取.oop的入口
    void ActionRead();

    //      功能描述；新建文件，即清空
    void newFile();

    //      功能描述；导出为图像文件
    //      参数描述：文件名称FileName
    void ExportImageFile(const QString & FileName);

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

    //      功能描述；锁定图层x、y方向的大小比例，之后只能等比例缩放
    void on_scale_lock_clicked();

    //      功能描述；选中图层发生改变后，改变相应的状态显示
    void updateStatus();

    //      功能描述；在新的窗口显示当前图层的直方图
    void ShowImageHist(const QString & name, const myImage &image);

    //      功能描述；显示整个画板的直方图
    void ShowDrawingBoardHist();

    //      功能描述；展示当前图层的直方图
    void ShowCurrentLayerHist();

    //      功能描述；保存修改并创建新文件
    void SaveChangeAndNew();

    //      功能描述；不保存修改并创建新文件
    void NottoSaveChangeAndNew();

    //      功能描述；取消新建文件的操作
    void CancelDialogChecktoSave();

    //      功能描述；保存修改并打开oop文件
    void SaveChangeAndOpen();

    //      功能描述；不保存修改并创建新文件
    void NottoSaveChangeAndOpen();
private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
