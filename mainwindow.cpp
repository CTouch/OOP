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

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    updateStatus();
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    ui->drawingboard->resize(event->size());
}


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
    if (event->key() == Qt::Key_Enter || event->key() == Qt::Key_Return)
    { // 回车键，闭合当前正在绘制的多边形
        if (ui->drawingboard->selectedIndex >=0 && ui->drawingboard->selectedIndex < ui->drawingboard->AllGraphs.size())
        {
            if (ui->drawingboard->AllGraphs[ui->drawingboard->selectedIndex]->shape == SHAPE_POLYGON)
            {
                ui->drawingboard->AllGraphs[ui->drawingboard->selectedIndex]->editType = CLOSING_POLYGON;
                update();
            }
        }
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
//    ui->drawingboard->update();
}

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
    if (action->text() == "Polygon(P)")
    { // 创建多边形
        ui->drawingboard->selectType = POLYGON;
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
    QAction *export_image = new QAction("Export Image");



    QMenu *menu_edit = new QMenu("Edit"); // "编辑"菜单栏
    QAction *Cursor = new QAction("Cursor (V)", this);
    QAction *Ellipse = new QAction("Ellipse (E)", this);
    QAction *Rectangle = new QAction("Rectangle (Q)", this);
    QAction *Polygon = new QAction("Polygon(P)", this);
    QAction *Move = new QAction("Move (M)", this);
    QAction *Rotate = new QAction("Rotate (R)", this);
    QAction *Duplicate = new QAction("Duplicate");
    QAction *Unselect = new QAction("Unselect (U)", this); // 取消选择
    QAction *Crop = new QAction("Crop (C)", this);


    // 设置快捷键
    Cursor->setShortcut(Qt::Key_V);
    Ellipse->setShortcut(Qt::Key_E);
    Rectangle->setShortcut(Qt::Key_Q);
    Polygon->setShortcut(Qt::Key_P);
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
    menu_file->addAction(import_image);
    menu_file->addAction(export_image);

    menu_edit->addAction(Cursor);
    menu_edit->addAction(Ellipse);
    menu_edit->addAction(Rectangle);
    menu_edit->addAction(Polygon);
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
    connect(ui->drawingboard, &DrawingBoard::ChangedSignal, this, &MainWindow::updateStatus);
    connect(ui->buttonShowDraingBoardHist,&QPushButton::clicked,this,&MainWindow::ShowDrawingBoardHist);
    connect(ui->buttonShowCurrentlayerHist,&QPushButton::clicked,this,&MainWindow::ShowCurrentLayerHist);
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
    ui->drawingboard->selectedIndex = -1;
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
    if (ui->drawingboard->deleteGraph())
    {   // 成功删除了某个图形
        // 菜单和图层显示发生相应的删除
        menu_layer->removeAction(menu_layer->actions().back());
        ui->index_list->removeItem(ui->drawingboard->AllGraphs.size());
        ui->index_list->setCurrentIndex(ui->drawingboard->selectedIndex);
    }
}

void MainWindow::saveFile(QFile &file)
{
    ui->drawingboard->saveFile(file);
}

void MainWindow::readFile(QFile &file)
{
    ui->drawingboard->readFile(file);

    menu_layer->clear();
    ui->index_list->clear();
    for (int i = 0;i < ui->drawingboard->AllGraphs.size(); ++i)
    { // 图层数目更新
        menu_layer->addAction(new QAction(QString::number(i), this));
        ui->index_list->addItem(QString::number(i));
    }

    updateStatus();
}

void MainWindow::newFile()
{
    while (!(ui->drawingboard->AllGraphs.empty()))
    {
        ui->drawingboard->selectedIndex = 0;
        deleteGraph();
    }
    //第一次修改未完成，不存在未保存的修改
    ui->drawingboard->doneFirstPaintevent = false;
    ui->drawingboard->UnsavedChange = false;
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
        //如果存在未保存的修改
        if(ui->drawingboard->UnsavedChange)
        {
            //弹出窗口
            DialogChecktoSave *dialog = new DialogChecktoSave(this);
            dialog->setAttribute(Qt::WA_DeleteOnClose,true);        //关闭时delete
            connect(dialog,&DialogChecktoSave::signalButtonSaveClicked,this,&MainWindow::SaveChangeAndNew);
            connect(dialog,&DialogChecktoSave::signalButtonNottoSaveClicked,this,&MainWindow::NottoSaveChangeAndNew);
            connect(dialog,&DialogChecktoSave::signalButtonSaveClicked,this,&MainWindow::CancelDialogChecktoSave);
            dialog->exec();
        }
        else
        {
            newFile();
            updateStatus();
        }
    }
    if (action->text() == "Open")
    {
        //如果存在未保存的修改
        if(ui->drawingboard->UnsavedChange)
        {
            //弹出窗口
            DialogChecktoSave *dialog = new DialogChecktoSave(this);
            connect(dialog,&DialogChecktoSave::signalButtonSaveClicked,this,&MainWindow::SaveChangeAndOpen);
            connect(dialog,&DialogChecktoSave::signalButtonNottoSaveClicked,this,&MainWindow::NottoSaveChangeAndOpen);
            connect(dialog,&DialogChecktoSave::signalButtonSaveClicked,this,&MainWindow::CancelDialogChecktoSave);
            dialog->exec();
        }
        else
        {
            ActionRead();
        }
    }
    if (action->text() == "Save")
    {
        if(ActionSave())
        {
            ui->drawingboard->doneFirstPaintevent = false;        //保存后，将第一次paintevent视为未完成
            ui->drawingboard->UnsavedChange = false;              //不存在未保存的修改
        }
    }
    if (action->text() == "Import Image")
    {
//        QFileDialog *fileDialog = new QFileDialog(this); // 弹出窗口，用户选择文件
//        fileDialog->setFileMode(QFileDialog::ExistingFile); // 只能选择已经存在的文件
//        fileDialog->setViewMode(QFileDialog::Detail);

//        QList<QUrl> urls;

//        fileDialog->setSidebarUrls(urls);
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

            ShowImageHist(fileName,*img);
        }
    }
    if(action->text() == "Export Image")
    {
//        QFileDialog *fileDialog = new QFileDialog(this);
//        fileDialog->setFileMode(QFileDialog::AnyFile); // 选择任意的文件，存在或自定义
//        fileDialog->setViewMode(QFileDialog::Detail);

//        QList<QUrl> urls;

//        fileDialog->setSidebarUrls(urls);
        QString fileName = QFileDialog::getSaveFileName(this, tr("Save Files"),
                                                        "",
                                                        tr("*.png")
                                                        );
        if (!fileName.isEmpty())
        {
            ExportImageFile(fileName);
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

void MainWindow::ShowImageHist(const QString & name,const myImage & image)
{
    HistWidget *histwidget = new HistWidget(image);
    histwidget->setAttribute(Qt::WA_DeleteOnClose,true);    //关闭时delete
    histwidget->setWindowTitle(name);
    histwidget->show();
    histwidget->ShowAllHist();
}

void MainWindow::ShowDrawingBoardHist()
{
    myImage tp(this->ui->drawingboard->width(),this->ui->drawingboard->height());   //设置画布大小为drawingborad大小
    QPainter painter(&(tp.img));                    //构建画笔
    this->ui->drawingboard->drawAll(painter,true);  //将所有图层绘制在画布上

    HistWidget *histwidget = new HistWidget(tp);    //new直方图展示窗口
    histwidget->setAttribute(Qt::WA_DeleteOnClose,true);    //关闭时delete
    histwidget->setWindowTitle("Drawing Board");    //设置标题
    histwidget->show();                             //打开直方图展示窗口
    histwidget->ShowAllHist();                      //展示drawingborad的直方图
}

void MainWindow::ShowCurrentLayerHist()
{
    if (!(ui->drawingboard->selectedIndex >= 0 && ui->drawingboard->selectedIndex < ui->drawingboard->AllGraphs.size()))    //如果未选择
    {
        //弹出对话窗口提示并未选择任何图层
        DialogNoSelected *dialog = new DialogNoSelected(this);
        dialog->show();
        return;
    }
    int currentIndex = this->ui->drawingboard->selectedIndex;
    this->ui->drawingboard->AllGraphs[currentIndex]->isBorderVisible = false;       //不绘制边框

    myImage tp(this->ui->drawingboard->width(),this->ui->drawingboard->height());   //设置画布大小为drawingborad大小
    QPainter painter(&(tp.img));                    //构建画笔
    this->ui->drawingboard->AllGraphs[currentIndex]->draw(painter);                 //将当前图层绘制在画布上

    HistWidget *histwidget = new HistWidget(tp);    //new直方图展示窗口
    histwidget->setAttribute(Qt::WA_DeleteOnClose,true);    //关闭时delete
    histwidget->setWindowTitle("Layer " + QString::number(currentIndex));           //设置标题
    histwidget->show();                             //打开直方图展示窗口
    histwidget->ShowAllHist();                      //展示当前图层的直方图
}

void MainWindow::ExportImageFile(const QString & FileName)
{
    myImage tp(this->ui->drawingboard->width(),this->ui->drawingboard->height(),Qt::white);   //设置画布大小为drawingborad大小,且背景为白色
    QPainter painter(&(tp.img));                    //构建画笔
    this->ui->drawingboard->drawAll(painter,true);  //将所有图层绘制在画布上
//    FileName.
    tp.img.save(FileName);
}

bool MainWindow::ActionSave()
{
//    QFileDialog *fileDialog = new QFileDialog(this);
//    fileDialog->setFileMode(QFileDialog::AnyFile); // 选择任意的文件，存在或自定义
//    fileDialog->setViewMode(QFileDialog::Detail);

//    QList<QUrl> urls;

//    fileDialog->setSidebarUrls(urls);
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save Files"),
                                                    "",
                                                    tr("*.oop")
                                                    );
    if (!fileName.isEmpty())
    {
        QFile file(fileName);
        file.open(QIODevice::WriteOnly); // 只写
        saveFile(file);
        ui->drawingboard->doneFirstPaintevent = false;        //保存后，将第一次paintevent视为未完成
        ui->drawingboard->UnsavedChange = false;              //不存在未保存的修改
        return true;
    }
    return false;
}

void MainWindow::ActionRead()
{
//    QFileDialog *fileDialog = new QFileDialog(this); // 弹出窗口，用户选择文件
//    fileDialog->setFileMode(QFileDialog::ExistingFile); // 只能选择已经存在的文件
//    fileDialog->setViewMode(QFileDialog::Detail);

//    QList<QUrl> urls;

//    fileDialog->setSidebarUrls(urls);
    QString fileName = QFileDialog::getOpenFileName(this, tr("Read Files"),
                                                    "",
                                                    tr("*.oop") // 后缀必须为oop
                                                    );
    if (!fileName.isEmpty())
    { // 文件有效
        QFile file(fileName);
        file.open(QIODevice::ReadOnly); // 只读文件
        readFile(file); // 读取文件
        ui->drawingboard->doneFirstPaintevent = false;        //读取后，将第一次paintevent视为未完成
        ui->drawingboard->UnsavedChange = false;              //不存在未保存的修改
    }
}


void MainWindow::SaveChangeAndNew()
{
    if(ActionSave())        //如果成功保存
    {
        newFile();
        updateStatus();
    }
    else return;
}

void MainWindow::NottoSaveChangeAndNew()
{
    newFile();
    updateStatus();
}

void MainWindow::SaveChangeAndOpen()
{
    if(ActionSave())
    {
        ActionRead();
        updateStatus();
    }
    else return;
}

void MainWindow::NottoSaveChangeAndOpen()
{
    ActionRead();
    updateStatus();
}

void MainWindow::CancelDialogChecktoSave()
{
    return;
}

