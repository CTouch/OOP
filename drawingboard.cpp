#include "drawingboard.h"
#include "myellipse.h"
#include "myrectangle.h"
#include "myimage.h"
#include <QDebug>


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
//            updateStatus();
        }
        if (selectType == RECTANGLE)
        { // 第一次点击, 创建矩形
            myRectangle *rectangle = new myRectangle(AllGraphs.size());
            selectedIndex = AllGraphs.size(); // 更新选中图层
            AllGraphs.push_back(rectangle); // 将矩形放在最后一层
//            updateStatus();
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
    emit ChangedSignal();
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
//    painter.fillRect(Qt::white);
    QBrush tpbrush(Qt::white);
    painter.fillRect(0,0,this->width(),this->height(),tpbrush);
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

void DrawingBoard::deleteGraph()
{ // 删除选中图形
    if (selectedIndex >=0 && selectedIndex < AllGraphs.size())
    { // 确实选中了图形
        // 记录原本的操作模式
        EditType editType = AllGraphs[selectedIndex]->editType;
        AllGraphs.removeAt(selectedIndex);
        // 移动后面的图层
        for (int i = selectedIndex; i < AllGraphs.size(); ++i)
        {
            AllGraphs[i]->changeIndex(i);
        }

        if (selectedIndex == AllGraphs.size()) selectedIndex--;

        // 菜单和图层显示发生相应的删除
//        menu_layer->removeAction(menu_layer->actions().back());
//        ui->index_list->removeItem(AllGraphs.size());
//        ui->index_list->setCurrentIndex(selectedIndex);


        if (selectedIndex >= 0 && selectedIndex < AllGraphs.size())
        {
            AllGraphs[selectedIndex]->editType = editType;
            AllGraphs[selectedIndex]->isBorderVisible = true;
        }
        // 重新绘图
        update();
    }
}

void DrawingBoard::saveFile(QFile &file)
{
    QDataStream out(&file);

    // 先储存mainwindow中的数据
    out << (onShift = false) << current_mouse << (isClicking = false) << selectedIndex;
    out << selectType << AllGraphs.size();

    // 再储存链表中的图形
    for (int i = 0;i < AllGraphs.size(); ++i)
    {
        out << AllGraphs[i]->shape;
        AllGraphs[i]->write(out);
    }
    file.close();
}

void DrawingBoard::readFile(QFile &file)
{
    QDataStream in(&file);
    in >> (onShift) >> current_mouse >> isClicking >> selectedIndex;
    int size = 0;
    in >> selectType >> size;
    AllGraphs.clear();
    for (int i = 0;i < size; ++i)
    {
        Shape shape;
        in >> shape;
        if (shape == Shape::SHAPE_ELLIPSE)
        {
            myEllipse *ellipse = new myEllipse(i);
            ellipse->read(in);
            AllGraphs.push_back(ellipse);
        }
        else if (shape == Shape::SHAPE_RECTANGLE)
        {
            myRectangle *rectangle = new myRectangle(i);
            rectangle->read(in);
            AllGraphs.push_back(rectangle);
        }
        else if (shape == Shape::IMAGE)
        {
            myImage *image = new myImage(i,in);
            AllGraphs.push_back(image);
        }
    }
    file.close(); // 关闭文件
    update();               //add by Touch20200717
}

