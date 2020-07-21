#include "drawingboard.h"
#include "myellipse.h"
#include "myrectangle.h"
#include "myimage.h"


DrawingBoard::DrawingBoard(QWidget *parent) : QWidget(parent)
{

}


void DrawingBoard::mouseMoveEvent(QMouseEvent *event)
{
    current_mouse = event->pos();
    if (isClicking)
    { // 移动鼠标时重绘图形
        update();
    }
    else
    {

    }
}

void DrawingBoard::mousePressEvent(QMouseEvent *event)
{
    current_mouse = event->pos();
    if (!isClicking)
    {
        if (selectType == ELLIPSE)
        { // 第一次单击, 创建椭圆
            myEllipse *ellipse = new myEllipse(AllGraphs.size());
            selectedIndex = AllGraphs.size(); // 更新选中图层
            AllGraphs.push_back(ellipse); // 将椭圆放在最后一层
            updateStatus();
        }
        if (selectType == RECTANGLE)
        { // 第一次点击, 创建矩形
            myRectangle *rectangle = new myRectangle(AllGraphs.size());
            selectedIndex = AllGraphs.size(); // 更新选中图层
            AllGraphs.push_back(rectangle); // 将矩形放在最后一层
            updateStatus();
        }
        if (selectType == EDIT)
        { // 编辑图形
            if (selectedIndex >= 0 && selectedIndex < AllGraphs.size())
            {
                if (AllGraphs[selectedIndex]->contain(current_mouse))
                { // 判断是否为有效的操作区域
                    AllGraphs[selectedIndex]->current_mouse = AllGraphs[selectedIndex]->last_mouse = current_mouse;
                    // 重新绘制图形
                    update();
                }
            }
        }
    }

    isClicking = true;
}

void DrawingBoard::mouseReleaseEvent(QMouseEvent *event)
{ // 释放鼠标后，isClicking为false
    isClicking = false;

    // 松开鼠标后，不再绘制图形，但是保持选中状态
    if (selectedIndex >=0 && selectedIndex < AllGraphs.size())
    {
        if (AllGraphs[selectedIndex]->editType == DRAW)
            AllGraphs[selectedIndex]->editType = SELECTED;

        // 防止重新选中时图形已经处于激活状态
        AllGraphs[selectedIndex]->last_mouse.setX(-1);
    }
}

void DrawingBoard::keyPressEvent(QKeyEvent *event)
{
    if (event->modifiers() == Qt::ShiftModifier)
    {
        onShift = true;
    }
    if (event->key() == Qt::Key_Backspace)
    { // 删除图层
        deleteGraph();
    }
}
void DrawingBoard::keyReleaseEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Shift)
    {
        onShift = false;
    }
}

void DrawingBoard::paintEvent(QPaintEvent *)
{
    QPainter painter(this); // 构建画笔
    drawAll(painter); // 绘制图形
//    painter.drawImage()
}

void DrawingBoard::drawAll(QPainter &painter)
{
    for (int i = 0;i < AllGraphs.size(); ++i)
    {
        if (selectedIndex == i && AllGraphs[i]->editType == DRAW)
        { // 绘制图形，需要更新鼠标位置
            AllGraphs[i]->current_mouse = current_mouse;
            AllGraphs[i]->onShift = onShift;
        }
        else if (selectedIndex == i && AllGraphs[i]->editType == MOVE)
        { // 移动图形
            if (AllGraphs[i]->last_mouse.x() > 0)
            { // 如果图形处于激活状态
                AllGraphs[i]->last_mouse = AllGraphs[i]->current_mouse;
                AllGraphs[i]->current_mouse = current_mouse;

                AllGraphs[i]->onShift = onShift;
                AllGraphs[i]->move();
            }
        }
        else if (selectedIndex == i && AllGraphs[i]->editType == ROTATE)
        { // 旋转图层
            if (AllGraphs[i]->last_mouse.x() > 0)
            { // 如果图形处于激活状态
                AllGraphs[i]->last_mouse = AllGraphs[i]->current_mouse;
                AllGraphs[i]->current_mouse = current_mouse;

                AllGraphs[i]->onShift = onShift;
                AllGraphs[i]->rotate();
            }
        }
        else if (selectedIndex == i && AllGraphs[i]->editType == SCALE)
        { // 放缩图形
            if (AllGraphs[i]->last_mouse.x() > 0)
            {
                AllGraphs[i]->last_mouse = AllGraphs[i]->current_mouse;
                AllGraphs[i]->current_mouse = current_mouse;
                AllGraphs[i]->onShift = onShift;
            }
        }
        else if (selectedIndex == i && AllGraphs[i]->editType == CROP)
        {
            if (AllGraphs[i]->last_mouse.x() > 0)
            {
                AllGraphs[i]->last_mouse = AllGraphs[i]->current_mouse;
                AllGraphs[i]->current_mouse = current_mouse;
                AllGraphs[i]->onShift = onShift;
                AllGraphs[i]->crop();
            }
        }
        else if (selectedIndex == i)
        {
            AllGraphs[i]->editType = SELECTED;
        }
        else
        { // 绘制不被选中的图形时，不会绘制边框
            AllGraphs[i]->editType = UNSELECTED;
        }
        // 绘制
        AllGraphs[i]->draw(painter);
    }
}
