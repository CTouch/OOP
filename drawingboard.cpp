#include "drawingboard.h"
#include "myellipse.h"
#include "myrectangle.h"
#include "mypolygon.h"
#include "myimage.h"
#include <QDebug>


#ifdef DRAWINGBOARD_DEBUG_ON
int count_paint_event = 0;
#endif

DrawingBoard::DrawingBoard(QWidget *parent) : QWidget(parent),
    selectedIndex(-1)
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
        if (event->button() == Qt::LeftButton)
        { // 第一次按左键
            if (selectType == ELLIPSE)
            { // 第一次单击, 创建椭圆
                myEllipse *ellipse = new myEllipse(AllGraphs.size());
                selectedIndex = AllGraphs.size(); // 更新选中图层
                AllGraphs.push_back(ellipse); // 将椭圆放在最后一层
            }
            if (selectType == RECTANGLE)
            { // 第一次点击, 创建矩形
                myRectangle *rectangle = new myRectangle(AllGraphs.size());
                selectedIndex = AllGraphs.size(); // 更新选中图层
                AllGraphs.push_back(rectangle); // 将矩形放在最后一层
            }
            if (selectType == POLYGON)
            { // 第一次点击，创建多边形或是继续绘制多边形
                if (selectedIndex >= 0 && selectedIndex < AllGraphs.size() && AllGraphs[selectedIndex]->shape == SHAPE_POLYGON && !AllGraphs[selectedIndex]->isClosed_poly())
                { // 继续绘制这个多边形
                    AllGraphs[selectedIndex]->editType = DRAW; // 修改多边形的状态为绘制，便于多边形添加一点
                }
                else
                { // 创建新的多边形
                    myPolygon *polygon = new myPolygon(AllGraphs.size());
                    selectedIndex = AllGraphs.size(); // 更新选中图层
                    AllGraphs.push_back(polygon); // 将矩形放在最后一层
                }
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
    }
    //向主窗口发送需要更新的信号
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
        if (AllGraphs[selectedIndex]->editType == HOVER_POLYGON)
        { // 取消多边形的预览
            AllGraphs[selectedIndex]->editType = SELECTED;
        }
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
    #ifdef DRAWINGBOARD_DEBUG_ON
        std::cout << "DrawingBoard PaintEvent Count: " << count_paint_event << std::endl;
        count_paint_event++;
    #endif

    QPainter painter(this); // 构建画笔
    QBrush tpbrush(Qt::white);
    painter.fillRect(0,0,this->width(),this->height(),tpbrush);//绘制白色背景
    drawAll(painter); // 绘制图形
}

void DrawingBoard::drawAll(QPainter &painter,bool no_border)
{
    //若不是绘制在drawing board上，则不需要绘制边框
    if(no_border)
    {
        selectedIndex = -1;     //实现方法为取消选择
    }
    for (int i = 0;i < AllGraphs.size(); ++i)
    {
        if (selectedIndex == i && AllGraphs[i]->editType == DRAW)
        { // 绘制图形，需要更新鼠标位置
            AllGraphs[i]->current_mouse = current_mouse;
            AllGraphs[i]->onShift = onShift;
        }
        else if (selectedIndex == i && AllGraphs[i]->editType == HOVER_POLYGON)
        { // 多边形绘制的预览
            AllGraphs[i]->current_mouse = current_mouse;
            AllGraphs[i]->onShift = onShift;
        }
        else if (selectedIndex == i && AllGraphs[i]->editType == CLOSING_POLYGON)
        { // 多边形绘制的预览
          // do nothing
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

bool DrawingBoard::deleteGraph()
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

        // 删除了图形
        return true;
    }
    return false;
}

void DrawingBoard::saveFile(QFile &file)
{
    FilePath = file.fileName();

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
    FilePath = file.fileName();
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
        else if (shape == Shape::SHAPE_POLYGON)
        {
            myPolygon *polygon = new myPolygon(i);
            polygon->read(in);
            AllGraphs.push_back(polygon);
        }
    }
    file.close(); // 关闭文件
    update();
}

bool DrawingBoard::CheckEqual(const QList<Graph*> & GraphList)
{
    if(AllGraphs.size() != GraphList.size()) return false;      //图层数量不同则不相同
    for(int i = 0;i < AllGraphs.size();i++)                     //顺序检查每个图层是否不同
    {
        if(AllGraphs[i]->base_equal(*GraphList[i]))
        {
            if(AllGraphs[i]->shape == Shape::SHAPE_ELLIPSE && !(*dynamic_cast<myEllipse*>(AllGraphs[i]) == *dynamic_cast<myEllipse*>(GraphList[i]))) return false;              //椭圆形
            else if(AllGraphs[i]->shape == Shape::SHAPE_ELLIPSE && !(*dynamic_cast<myRectangle*>(AllGraphs[i]) == *dynamic_cast<myRectangle*>(GraphList[i]))) return false;     //矩形
            else if(AllGraphs[i]->shape == Shape::SHAPE_ELLIPSE && !(*dynamic_cast<myImage*>(AllGraphs[i]) == *dynamic_cast<myImage*>(GraphList[i]))) return false;             //导入图像类型
            else if(AllGraphs[i]->shape == Shape::SHAPE_ELLIPSE && !(*dynamic_cast<myPolygon*>(AllGraphs[i]) == *dynamic_cast<myPolygon*>(GraphList[i]))) return false;         //多边形
        }
    }
    return true;
}
bool DrawingBoard::UnsavedChange()
{
    if(FilePath.length() > 0)               //读取自文件
    {
        DrawingBoard tp;                    //临时变量
        QFile file(FilePath);               //读取文件
        file.open(QIODevice::ReadOnly);
        tp.readFile(file);
        return (!CheckEqual(tp.AllGraphs)); //检测是否存在不同
    }
    else            //不是读取自文件
    {
        if(AllGraphs.size() > 0) return true;   //存在图层则存在未保存的修改
        else return false;
    }
}
