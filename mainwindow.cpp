#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    init();
    setupMenu();
}

MainWindow::~MainWindow()
{
    delete ui;
}

//void MainWindow::mouseMoveEvent(QMouseEvent *event)
//{
//    current_mouse = event->pos();
//    if (isClicking)
//    { // 移动鼠标时重绘图形
//        update();
//    }
//    else
//    {

//    }
//}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
//    current_mouse = event->pos();
//    if (!isClicking)
//    {
//        if (selectType == ELLIPSE)
//        { // 第一次单击, 创建椭圆
//            myEllipse *ellipse = new myEllipse(AllGraphs.size());
//            selectedIndex = AllGraphs.size(); // 更新选中图层
//            AllGraphs.push_back(ellipse); // 将椭圆放在最后一层
//            updateStatus();
//        }
//        if (selectType == RECTANGLE)
//        { // 第一次点击, 创建矩形
//            myRectangle *rectangle = new myRectangle(AllGraphs.size());
//            selectedIndex = AllGraphs.size(); // 更新选中图层
//            AllGraphs.push_back(rectangle); // 将矩形放在最后一层
//            updateStatus();
//        }
//        if (selectType == EDIT)
//        { // 编辑图形
//            if (selectedIndex >= 0 && selectedIndex < AllGraphs.size())
//            {
//                if (AllGraphs[selectedIndex]->contain(current_mouse))
//                { // 判断是否为有效的操作区域
//                    AllGraphs[selectedIndex]->current_mouse = AllGraphs[selectedIndex]->last_mouse = current_mouse;
//                    // 重新绘制图形
//                    update();
//                }
//            }
//        }
//    }

//    isClicking = true;
    updateStatus();
}

//void MainWindow::mouseReleaseEvent(QMouseEvent *event)
//{ // 释放鼠标后，isClicking为false
//    isClicking = false;

//    // 松开鼠标后，不再绘制图形，但是保持选中状态
//    if (selectedIndex >=0 && selectedIndex < AllGraphs.size())
//    {
//        if (AllGraphs[selectedIndex]->editType == DRAW)
//            AllGraphs[selectedIndex]->editType = SELECTED;

//        // 防止重新选中时图形已经处于激活状态
//        AllGraphs[selectedIndex]->last_mouse.setX(-1);
//    }
//}

void MainWindow::keyPressEvent(QKeyEvent *event)
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

void MainWindow::keyReleaseEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Shift)
    {
        onShift = false;
    }
}

void MainWindow::paintEvent(QPaintEvent *)
{
//    QPainter painter(this); // 构建画笔
//    drawAll(painter); // 绘制图形

    //debug:   check drawingboard updating
    ui->drawingboard->update();
}

//void MainWindow::drawAll(QPainter &painter)
//{
//    for (int i = 0;i < AllGraphs.size(); ++i)
//    {
//        if (selectedIndex == i && AllGraphs[i]->editType == DRAW)
//        { // 绘制图形，需要更新鼠标位置
//            AllGraphs[i]->current_mouse = current_mouse;
//            AllGraphs[i]->onShift = onShift;
//        }
//        else if (selectedIndex == i && AllGraphs[i]->editType == MOVE)
//        { // 移动图形
//            if (AllGraphs[i]->last_mouse.x() > 0)
//            { // 如果图形处于激活状态
//                AllGraphs[i]->last_mouse = AllGraphs[i]->current_mouse;
//                AllGraphs[i]->current_mouse = current_mouse;

//                AllGraphs[i]->onShift = onShift;
//                AllGraphs[i]->move();
//            }
//        }
//        else if (selectedIndex == i && AllGraphs[i]->editType == ROTATE)
//        { // 旋转图层
//            if (AllGraphs[i]->last_mouse.x() > 0)
//            { // 如果图形处于激活状态
//                AllGraphs[i]->last_mouse = AllGraphs[i]->current_mouse;
//                AllGraphs[i]->current_mouse = current_mouse;

//                AllGraphs[i]->onShift = onShift;
//                AllGraphs[i]->rotate();
//            }
//        }
//        else if (selectedIndex == i && AllGraphs[i]->editType == SCALE)
//        { // 放缩图形
//            if (AllGraphs[i]->last_mouse.x() > 0)
//            {
//                AllGraphs[i]->last_mouse = AllGraphs[i]->current_mouse;
//                AllGraphs[i]->current_mouse = current_mouse;
//                AllGraphs[i]->onShift = onShift;
//            }
//        }
//        else if (selectedIndex == i && AllGraphs[i]->editType == CROP)
//        {
//            if (AllGraphs[i]->last_mouse.x() > 0)
//            {
//                AllGraphs[i]->last_mouse = AllGraphs[i]->current_mouse;
//                AllGraphs[i]->current_mouse = current_mouse;
//                AllGraphs[i]->onShift = onShift;
//                AllGraphs[i]->crop();
//            }
//        }
//        else if (selectedIndex == i)
//        {
//            AllGraphs[i]->editType = SELECTED;
//        }
//        else
//        { // 绘制不被选中的图形时，不会绘制边框
//            AllGraphs[i]->editType = UNSELECTED;
//        }
//        // 绘制
//        AllGraphs[i]->draw(painter);
//    }
//}

void MainWindow::menu_edit_triggered(QAction *action)
{ // 当"编辑"栏中内容被触发时(点击或快捷键)
    if (action->text() == "Ellipse (E)")
    { // 创建椭圆
        ui->drawingboard->selectType = ELLIPSE;
        // 更换鼠标样式
        ui->drawingboard->setCursor(Qt::ArrowCursor);
    }
    if (action->text() == "Rectangle (Q)")
    { // 创建矩形
        ui->drawingboard->selectType = RECTANGLE;
        // 更换鼠标样式
        ui->drawingboard->setCursor(Qt::ArrowCursor);
    }
    if (action->text() == "Cursor (V)")
    {
        ui->drawingboard->selectType = CURSOR;
        // 更换鼠标样式
        ui->drawingboard->setCursor(Qt::ArrowCursor);
//        if (selectedIndex >= 0 && selectedIndex < ui->drawingboard->AllGraphs.size())
        if (ui->drawingboard->selectedIndex >= 0 && ui->drawingboard->selectedIndex < ui->drawingboard->AllGraphs.size())
        {
            ui->drawingboard->AllGraphs[ui->drawingboard->selectedIndex]->editType = SELECTED;
        }
    }
    if (action->text() == "Move (M)")
    { // 移动图形
        ui->drawingboard->selectType = EDIT;
        // 更换鼠标样式
        ui->drawingboard->setCursor(Qt::SizeAllCursor);
        if (ui->drawingboard->selectedIndex >= 0 && ui->drawingboard->selectedIndex < ui->drawingboard->AllGraphs.size())
        {
            ui->drawingboard->AllGraphs[ui->drawingboard->selectedIndex]->editType = MOVE;
        }
    }
    if (action->text() == "Rotate (R)")
    { // 旋转图形
//        selectType = EDIT;
        ui->drawingboard->selectType = EDIT;
        QPixmap pixmap(":Resources/rotate_cursor.png");
        pixmap = pixmap.scaledToHeight(60);
        // 更换鼠标样式
        ui->drawingboard->setCursor(QCursor(pixmap, -1, -1));
        if (ui->drawingboard->selectedIndex >= 0 && ui->drawingboard->selectedIndex < ui->drawingboard->AllGraphs.size())
        {
            ui->drawingboard->AllGraphs[ui->drawingboard->selectedIndex]->editType = ROTATE;
        }
    }
    if (action->text() == "Unselect (U)")
    { // 不选中任何图形
        ui->drawingboard->selectedIndex = -1;

        // 更改鼠标样式
        ui->centralwidget->setCursor(Qt::ArrowCursor);
        update();
    }
    if (action->text() == "Duplicate")
    { // 复制
        ui->drawingboard->selectType = EDIT;
        if (ui->drawingboard->selectedIndex >= 0 && ui->drawingboard->selectedIndex < ui->drawingboard->AllGraphs.size())
        {
            ui->drawingboard->AllGraphs.push_back(ui->drawingboard->AllGraphs[ui->drawingboard->selectedIndex]->duplicate());
            ui->drawingboard->selectedIndex = ui->drawingboard->AllGraphs.size()-1;
            updateStatus();
        }
    }
    if (action->text() == "Crop (C)")
    {
        if (ui->drawingboard->selectedIndex >= 0 && ui->drawingboard->selectedIndex < ui->drawingboard->AllGraphs.size())
        {
            selectType = EDIT;
            ui->drawingboard->AllGraphs[ui->drawingboard->selectedIndex]->editType = CROP;
            ui->centralwidget->setCursor(Qt::ArrowCursor);
        }
    }
}




void MainWindow::setupMenu()
{
    // 非常非常重要，否则mac端无法显示菜单栏
    ui->menubar->setNativeMenuBar(false);
    ui->menubar->clear();


    QMenu *menu_file = new QMenu("File"); // "文件"菜单栏
    QAction *new_file = new QAction("New"); // 新建文件
    QAction *open_file = new QAction("Open"); // 打开oop文件
    QAction *save_file = new QAction("Save"); // 保存oop文件
    QAction *import_image = new QAction("Import Image"); //import .png files 20200718

//    QAction *import_file = new QAction("Import"); // 导入oop文件或图像文件，不会覆盖现在的内容



    QMenu *menu_edit = new QMenu("Edit"); // "编辑"菜单栏
    QAction *Cursor = new QAction("Cursor (V)", this);
    QAction *Ellipse = new QAction("Ellipse (E)", this);
    QAction *Rectangle = new QAction("Rectangle (Q)", this);
    QAction *Move = new QAction("Move (M)", this);
    QAction *Rotate = new QAction("Rotate (R)", this);
    QAction *Duplicate = new QAction("Duplicate");
    QAction *Unselect = new QAction("Unselect (U)", this); // 取消选择
    QAction *Crop = new QAction("Crop (C)", this);


    // 设置快捷键
    Cursor->setShortcut(Qt::Key_V);
    Ellipse->setShortcut(Qt::Key_E);
    Rectangle->setShortcut(Qt::Key_Q);
    Move->setShortcut(Qt::Key_M);
    Rotate->setShortcut(Qt::Key_R);
    Unselect->setShortcut(Qt::Key_U);
    Crop->setShortcut(Qt::Key_C);

    // 不同平台不一样的通用组合键
    new_file->setShortcut(QKeySequence::New); // windows: control+N, mac: command+N
    open_file->setShortcut(QKeySequence::Open); // windwos: control+O, mac: command+O
    save_file->setShortcut(QKeySequence::Save); // windwos: control+S, mac: command+s
    import_image->setShortcut(QKeySequence(tr("Ctrl+I"))); // control + i
    Duplicate->setShortcut(QKeySequence::Copy); // windwos: control+C, mac: command+c


    // 把菜单栏的内容添加到菜单栏中
    menu_file->addAction(new_file);
    menu_file->addAction(open_file);
    menu_file->addAction(save_file);
    menu_file->addAction(import_image);         //add by touch 20200718

//    menu_edit->addAction(import_file);
    menu_edit->addAction(Cursor);
    menu_edit->addAction(Ellipse);
    menu_edit->addAction(Rectangle);
    menu_edit->addAction(Move);
    menu_edit->addAction(Rotate);
    menu_edit->addAction(Duplicate);
    menu_edit->addAction(Unselect);
    menu_edit->addAction(Crop);

    menu_layer = new QMenu("Layer");

    // 将菜单栏添加至总菜单
    ui->menubar->addMenu(menu_file);
    ui->menubar->addMenu(menu_edit);
    ui->menubar->addMenu(menu_layer);

    // 添加触发器
    connect(menu_file, SIGNAL(triggered(QAction *)), this, SLOT(action_file(QAction *)));
    connect(menu_edit, SIGNAL(triggered(QAction *)), this, SLOT(menu_edit_triggered(QAction *)));
    connect(menu_layer, SIGNAL(triggered(QAction *)), this, SLOT(changeIndex(QAction *)));
    connect(ui->drawingboard,&DrawingBoard::ChangedSignal,this,&MainWindow::updateStatus);

//    connect(ui->drawingboard,SIGNAL(ui->drawingboard->ChangedSignal()),this,SLOT(updateStatus()));
}

void MainWindow::init()
{ // 初始化图形界面
    setMouseTracking(true); // 在鼠标不点击时也跟踪鼠标

    // 设置滑条的最大值和最小值
    ui->opacity_slider->setMinimum(0);
    ui->opacity_slider->setMaximum(100);
    ui->stroke_width_slider->setMinimum(0);
    ui->stroke_width_slider->setMaximum(15);
    ui->scale_x->setMinimum(1);
    ui->scale_x->setMaximum(300);
    ui->scale_y->setMinimum(1);
    ui->scale_y->setMaximum(300);
    ui->drawingboard->selectedIndex = 0;
//    selectedIndex = 0;

    // 更新界面
    updateStatus();
}

void MainWindow::updateStatus()
{
    if (ui->drawingboard->selectedIndex < 0 || ui->drawingboard->selectedIndex >= ui->drawingboard->AllGraphs.size())
    { // 没有选中图层，设置为默认值
        ui->opacity_slider->setValue(100);
        ui->stroke_width_slider->setValue(0);
        ui->scale_x->setValue(100);
        ui->scale_y->setValue(100);
        return ;
    }

    if (ui->drawingboard->selectedIndex >= ui->index_list->count())
    { // 图层数目增加
        menu_layer->addAction(new QAction(QString::number(ui->drawingboard->selectedIndex), this));
        ui->index_list->addItem(QString::number(ui->drawingboard->selectedIndex));
    }
    // 在界面中体现当前选中的图层
    ui->index_list->setCurrentIndex(ui->drawingboard->selectedIndex);

    // 不透明度滑条的值自适应（滑条和label）
    ui->opacity_slider->setValue(ui->drawingboard->AllGraphs[ui->drawingboard->selectedIndex]->Opacity);
    ui->value_opacity->setText(QString::number(ui->opacity_slider->value()));

    // 描边粗细的值自适应（滑条和label）
    QPen Stroke = ui->drawingboard->AllGraphs[ui->drawingboard->selectedIndex]->getStroke();
    ui->stroke_width_slider->setValue(Stroke.width());
    // 图形的缩放程度自适应（滑条和label）
    ui->scale_x->setValue(int(100 * ui->drawingboard->AllGraphs[ui->drawingboard->selectedIndex]->scale_x));
    ui->scale_y->setValue(int(100 * ui->drawingboard->AllGraphs[ui->drawingboard->selectedIndex]->scale_y));
}

void MainWindow::deleteGraph()
{ // 删除选中图形
//    if (selectedIndex >=0 && selectedIndex < AllGraphs.size())
//    { // 确实选中了图形
//        // 记录原本的操作模式
//        EditType editType = AllGraphs[selectedIndex]->editType;
//        AllGraphs.removeAt(selectedIndex);
//        // 移动后面的图层
//        for (int i = selectedIndex; i < AllGraphs.size(); ++i)
//        {
//            AllGraphs[i]->changeIndex(i);
//        }

//        if (selectedIndex == AllGraphs.size()) selectedIndex--;

        ui->drawingboard->deleteGraph();
        // 菜单和图层显示发生相应的删除
        menu_layer->removeAction(menu_layer->actions().back());
        ui->index_list->removeItem(ui->drawingboard->AllGraphs.size());
        ui->index_list->setCurrentIndex(ui->drawingboard->selectedIndex);


//        if (selectedIndex >= 0 && selectedIndex < AllGraphs.size())
//        {
//            AllGraphs[selectedIndex]->editType = editType;
//            AllGraphs[selectedIndex]->isBorderVisible = true;
//        }
//        // 重新绘图
//        update();
//    }
}

void MainWindow::saveFile(QFile &file)
{
//    QDataStream out(&file);

//     先储存mainwindow中的数据
//    out << (onShift = false) << current_mouse << (isClicking = false) << selectedIndex;
//    out << selectType << AllGraphs.size();

//     再储存链表中的图形
//    for (int i = 0;i < AllGraphs.size(); ++i)
//    {
//        out << AllGraphs[i]->shape;
//        AllGraphs[i]->write(out);
//    }
//    file.close();
    ui->drawingboard->saveFile(file);

}

void MainWindow::readFile(QFile &file)
{
//    QDataStream in(&file);
//    in >> (onShift) >> current_mouse >> isClicking >> selectedIndex;
//    int size = 0;
//    in >> selectType >> size;
//    AllGraphs.clear();
//    for (int i = 0;i < size; ++i)
//    {
//        Shape shape;
//        in >> shape;
//        if (shape == Shape::SHAPE_ELLIPSE)
//        {
//            myEllipse *ellipse = new myEllipse(i);
//            ellipse->read(in);
//            AllGraphs.push_back(ellipse);
//        }
//        else if (shape == Shape::SHAPE_RECTANGLE)
//        {
//            myRectangle *rectangle = new myRectangle(i);
//            rectangle->read(in);
//            AllGraphs.push_back(rectangle);
//        }
//        else if (shape == Shape::IMAGE)
//        {
//            myImage *image = new myImage(i,in);
//            AllGraphs.push_back(image);
//        }
//    }
//    file.close(); // 关闭文件
    ui->drawingboard->readFile(file);

    menu_layer->clear();
    ui->index_list->clear();
    for (int i = 0;i < ui->drawingboard->AllGraphs.size(); ++i)
    { // 图层数目更新
        menu_layer->addAction(new QAction(QString::number(i), this));
        ui->index_list->addItem(QString::number(i));
    }

    updateStatus();
//    update();               //add by Touch20200717
}

void MainWindow::newFile()
{
    while (!(ui->drawingboard->AllGraphs.empty()))
    {
        ui->drawingboard->selectedIndex = 0;
        deleteGraph();
    }
}

void MainWindow::changeIndex(QAction *action)
{
    int nextIndex = action->text().toInt();
    if (nextIndex == ui->drawingboard->selectedIndex)
    { // 并没有更新图层
        return ;
    }

    EditType editType = SELECTED;
    if (ui->drawingboard->selectedIndex >= 0 && ui->drawingboard->selectedIndex < ui->drawingboard->AllGraphs.size())
    {
        // 记录原本的编辑状态
        editType = ui->drawingboard->AllGraphs[ui->drawingboard->selectedIndex]->editType;
        // 取消原有图形的选择
        ui->drawingboard->AllGraphs[ui->drawingboard->selectedIndex]->editType = UNSELECTED;
    }
    ui->drawingboard->selectedIndex = nextIndex;
    if (ui->drawingboard->AllGraphs[ui->drawingboard->selectedIndex]->editType == UNSELECTED)
    { // 更新新选择图形的编辑状态
        ui->drawingboard->AllGraphs[ui->drawingboard->selectedIndex]->editType = editType;
    }
    updateStatus(); // 更新状态
    ui->drawingboard->update(); // 重绘图形
}

void MainWindow::action_file(QAction *action)
{
    if (action->text() == "New")
    {
        newFile();
        updateStatus();
    }
    if (action->text() == "Open")
    {
        QFileDialog *fileDialog = new QFileDialog(this); // 弹出窗口，用户选择文件
        fileDialog->setFileMode(QFileDialog::ExistingFile); // 只能选择已经存在的文件
        fileDialog->setViewMode(QFileDialog::Detail);

        QList<QUrl> urls;

        fileDialog->setSidebarUrls(urls);
        QString fileName = QFileDialog::getOpenFileName(this, tr("Read Files"),
                                                        "",
                                                        tr("*.oop") // 后缀必须为oop
                                                        );
        if (!fileName.isEmpty())
        { // 文件有效
            QFile file(fileName);
            file.open(QIODevice::ReadOnly); // 只读文件
            readFile(file); // 读取文件
        }
    }
    if (action->text() == "Save")
    {
        QFileDialog *fileDialog = new QFileDialog(this);
        fileDialog->setFileMode(QFileDialog::AnyFile); // 选择任意的文件，存在或自定义
        fileDialog->setViewMode(QFileDialog::Detail);

        QList<QUrl> urls;

        fileDialog->setSidebarUrls(urls);
        QString fileName = QFileDialog::getSaveFileName(this, tr("Save Files"),
                                                        "",
                                                        tr("*.oop")
                                                        );
        if (!fileName.isEmpty())
        {
            QFile file(fileName);
            file.open(QIODevice::WriteOnly); // 只写
            saveFile(file);
        }
    }
    if (action->text() == "Import Image")
    {
        QFileDialog *fileDialog = new QFileDialog(this); // 弹出窗口，用户选择文件
        fileDialog->setFileMode(QFileDialog::ExistingFile); // 只能选择已经存在的文件
        fileDialog->setViewMode(QFileDialog::Detail);

        QList<QUrl> urls;

        fileDialog->setSidebarUrls(urls);
        QString fileName = QFileDialog::getOpenFileName(this, tr("Read Files"),
                                                        "",
                                                        tr("*.png") // 后缀必须为.png
                                                        );
        if (!fileName.isEmpty())
        { // 文件有效
            myImage *img = new myImage(ui->drawingboard->AllGraphs.size(),fileName);
            ui->drawingboard->selectedIndex = ui->drawingboard->AllGraphs.size(); // 更新选中图层
            ui->drawingboard->AllGraphs.push_back(img); // 将image放在最后一层
            updateStatus();
            ui->drawingboard->update();

            ShowImageHist(*img);
        }
    }
}

void MainWindow::on_opacity_slider_valueChanged(int value)
{
    if (ui->drawingboard->selectedIndex >= 0 && ui->drawingboard->selectedIndex < ui->drawingboard->AllGraphs.size())
    {
        ui->drawingboard->AllGraphs[ui->drawingboard->selectedIndex]->Opacity = value;
        ui->value_opacity->setText(QString::number(ui->opacity_slider->value()));
        ui->drawingboard->update();
    }
    ui->value_opacity->setText(QString::number(value));
}

void MainWindow::on_button_fill_color_clicked()
{
    if (ui->drawingboard->selectedIndex >= 0 && ui->drawingboard->selectedIndex < ui->drawingboard->AllGraphs.size())
    {
        QColorDialog *color = new QColorDialog(this);
        color->setOption(QColorDialog::ShowAlphaChannel); // 允许用户选择alpha值，为0时即为透明色

        // 储存原有的颜色
        lastColor = ui->drawingboard->AllGraphs[ui->drawingboard->selectedIndex]->getBrush().color();
        color->setCurrentColor(lastColor);
        color->show(); // 显示取色器

        // 选择的颜色发生更换，实时预览
        connect(color, SIGNAL(currentColorChanged(QColor)), this, SLOT(setColor_fill(QColor)));

        // 取消选色，颜色返回原来的值
        connect(color, SIGNAL(rejected()), this, SLOT(recoverColor_fill()));

        // 重新绘制图形
        ui->drawingboard->update();
    }
}

void MainWindow::on_button_stroke_color_clicked()
{
    if (ui->drawingboard->selectedIndex >= 0 && ui->drawingboard->selectedIndex < ui->drawingboard->AllGraphs.size())
    {
        QColorDialog *color = new QColorDialog(this);
        color->setOption(QColorDialog::ShowAlphaChannel);

        // 储存原有的颜色
        lastColor = ui->drawingboard->AllGraphs[ui->drawingboard->selectedIndex]->getStroke().color();
        color->setCurrentColor(lastColor);

        color->show();


        // 选择颜色，但没确定
        connect(color, SIGNAL(currentColorChanged(QColor)), this, SLOT(setColor_stroke(QColor)));

        // 取消选色，颜色返回原来的值
        connect(color, SIGNAL(rejected()), this, SLOT(recoverColor_stroke()));

        ui->drawingboard->update();
    }
}


void MainWindow::on_stroke_width_slider_valueChanged(int value)
{ // 调整描边粗细
    if (ui->drawingboard->selectedIndex >= 0 && ui->drawingboard->selectedIndex < ui->drawingboard->AllGraphs.size())
    {
        ui->drawingboard->AllGraphs[ui->drawingboard->selectedIndex]->setStroke(value);
        ui->value_stroke_width->setText(QString::number(ui->stroke_width_slider->value()));
        ui->drawingboard->update();
    }
    ui->value_stroke_width->setText(QString::number(value));
}


void MainWindow::on_index_list_currentIndexChanged(int index)
{ // 改变选中图形的图层
    if (ui->drawingboard->selectedIndex >= 0 && ui->drawingboard->selectedIndex < ui->drawingboard->AllGraphs.size() && index >= 0 && index < ui->drawingboard->AllGraphs.size())
    {
        int old_index = ui->drawingboard->selectedIndex;
        // 更新其他图形的图层
        if (index > old_index)
        {
            for (int i = old_index; i < index; ++i)
            {
                qSwap(ui->drawingboard->AllGraphs[i], ui->drawingboard->AllGraphs[i+1]); // 交换指针
                ui->drawingboard->AllGraphs[i]->changeIndex(i);
                ui->drawingboard->AllGraphs[i+1]->changeIndex(i+1);
            }
        }
        else
        {
            for (int i = old_index; i > index; --i)
            {
                qSwap(ui->drawingboard->AllGraphs[i], ui->drawingboard->AllGraphs[i-1]); // 交换指针
                ui->drawingboard->AllGraphs[i-1]->changeIndex(i-1);
                ui->drawingboard->AllGraphs[i]->changeIndex(i);
            }
        }

        ui->drawingboard->selectedIndex = index;
        ui->drawingboard->update();
    }
}

void MainWindow::on_scale_x_valueChanged(int value)
{
    if (ui->drawingboard->selectedIndex >= 0 && ui->drawingboard->selectedIndex < ui->drawingboard->AllGraphs.size())
    {
        qreal ratio = ui->drawingboard->AllGraphs[ui->drawingboard->selectedIndex]->scale_y / ui->drawingboard->AllGraphs[ui->drawingboard->selectedIndex]->scale_x;
        if (ui->scale_lock->isChecked())
        { // 大小锁定被勾选
            ui->scale_y->setValue(int(value * ratio));
        }
        ui->drawingboard->AllGraphs[ui->drawingboard->selectedIndex]->scale_x = value / 100.0;
        ui->drawingboard->update();
    }
    ui->value_scale_x->setText(QString::number(value));
}

void MainWindow::on_scale_y_valueChanged(int value)
{
    if (ui->drawingboard->selectedIndex >= 0 && ui->drawingboard->selectedIndex < ui->drawingboard->AllGraphs.size())
    {
        ui->drawingboard->AllGraphs[ui->drawingboard->selectedIndex]->scale_y = value / 100.0;
        ui->drawingboard->update();
    }
    ui->value_scale_y->setText(QString::number(value));
}

void MainWindow::on_scale_lock_clicked()
{
    if (ui->scale_lock->isChecked())
    {
        ui->scale_y->setDisabled(true);
    }
    else
    {
        ui->scale_y->setDisabled(false);
    }
}

void MainWindow::setColor_fill(QColor color)
{
    if (ui->drawingboard->selectedIndex >= 0 && ui->drawingboard->selectedIndex < ui->drawingboard->AllGraphs.size())
    {
        ui->drawingboard->AllGraphs[ui->drawingboard->selectedIndex]->setFill(color);
        ui->drawingboard->update();
    }
}

void MainWindow::recoverColor_fill()
{
    if (ui->drawingboard->selectedIndex >= 0 && ui->drawingboard->selectedIndex < ui->drawingboard->AllGraphs.size())
    {
        ui->drawingboard->AllGraphs[ui->drawingboard->selectedIndex]->setFill(lastColor);
        ui->drawingboard->update();
    }
}


void MainWindow::setColor_stroke(QColor color)
{
    if (ui->drawingboard->selectedIndex >= 0 && ui->drawingboard->selectedIndex < ui->drawingboard->AllGraphs.size())
    {
        ui->drawingboard->AllGraphs[ui->drawingboard->selectedIndex]->setStroke(color);
        ui->drawingboard->update();
    }
}

void MainWindow::recoverColor_stroke()
{
    if (ui->drawingboard->selectedIndex >= 0 && ui->drawingboard->selectedIndex < ui->drawingboard->AllGraphs.size())
    {
        ui->drawingboard->AllGraphs[ui->drawingboard->selectedIndex]->setStroke(lastColor);
        ui->drawingboard->update();
    }
}

void MainWindow::ShowImageHist(const myImage & image)
{
    HistWidget *histwidget = new HistWidget(image);
    histwidget->show();
    histwidget->ShowAllHist();
}
