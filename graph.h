#ifndef GRAPH_H
#define GRAPH_H
#include <QPoint>
#include <QRect>
#include <QPainter>
#include <QColor>
#include <QPaintEvent>
#include <QtMath>
#include <QDebug>
#include <QPixmap>


enum EditType
{ // 图形被选中的状态
    SELECTED, // 被选中
    UNSELECTED, // 未被选中
    ROTATE, // 旋转中
    SCALE, // 放缩中
    CROP, // 裁剪中
    MOVE, // 移动中
    DRAW,// 首次绘制中
    CLOSING_POLYGON, // 特属于多边形的状态，按回车后封闭多边形
    HOVER_POLYGON, // 特属于多边形的状态，还在绘制但是鼠标处于放松的状态，会预览将要绘制的边
};


enum Shape
{ // 形状的颜色，用于规范储存、读取".oop"文件
    SHAPE_ELLIPSE, // 椭圆
    SHAPE_RECTANGLE, // 矩形
    SHAPE_POLYGON, // 多边形
    IMAGE,  //loaded image
    UNKOWN, // 未知
};

class Graph
{
public: // 公开的变量
    QPoint last_mouse; // 上一时刻鼠标的位置
    QPoint current_mouse; // 当前鼠标位置
    qreal angle; // 旋转的角度，角度制，如果按住shift，它在角度上只能为15的整数倍
    int Index; // 所处图层
    EditType editType; // 图形被选中的状态
    int Opacity; // 不透明度，取值范围是0到100
    bool isBorderVisible; // 辅助视图的边框是否呈现
    bool onShift; // 是否按着shift
    Shape shape; // 图形形状
    qreal scale_x; // x方向的放缩程度
    qreal scale_y; // y方向的放缩程度

protected: // 只能由自己和子类访问的变量
    qreal stored_angle = 0; // 角度制，"理应的"旋转角度，在按住shift时angle不等于这个值
    QPoint Center = QPoint(-1, -1); // 图形的中心点
    int graph_width; // 图形的宽度
    int graph_height; // 图形的高度
    QPoint border_tl; // 矩形辅助边框的左上角, top left, 未经过旋转和放缩
    QPoint border_br; // 矩形辅助边框的右下角, bottom right, 未经过旋转和放缩
    qreal *crop_ratios; // 四个方向的裁切比例，-1～1，-1表示把另一半也切完了，1表示没有裁切
    // crop_ratios[0]: 上
    // crop_ratios[1]: 右
    // crop_ratios[2]: 下
    // crop_ratios[3]: 左


public: // 基类的基础构造器
    Graph() : // 初始化成员列表
        last_mouse(-1, 1),
        current_mouse(-1, -1),
        angle(0),
        Index(-1),
        editType(UNSELECTED),
        Opacity(100),
        isBorderVisible(false),
        onShift(false),
        shape(UNKOWN),
        scale_x(1.0),
        scale_y(1.0)
        {
            crop_ratios = new qreal[4]();
            for (int i = 0;i <= 3; ++i)
                crop_ratios[i] = 1.0;
        }

public: // 必须由子类来实现的纯虚函数，外界通过这些函数与图形交互

    //      功能描述；绘制图形/图像
    //      参数描述：用于绘制的画笔painter
    virtual void draw(QPainter &painter) = 0; // 绘制
    //      功能描述；复制图形/图像
    //      返回值描述：复制生成的图形/图像
    virtual Graph *duplicate() = 0; // 复制
    //      功能描述；将数据流中的数据输入至图形/图像中
    //      参数描述：输入流in
    virtual void read(QDataStream &in) = 0; // 文件的读
    //      功能描述；将图形/图像中的数据输入至数据流中
    //      参数描述：输出流out
    virtual void write(QDataStream &out) = 0; // 文件的写

public: // 虚函数，对于某些子类置空，某些子类需要自己重新实现
    //      功能描述；显示图像的直方图，对图形无效
    virtual void showHist() { } // 显示直方图
    //      功能描述；设置图形的填充颜色，对图像无效
    //      参数描述：填充的颜色color
    virtual void setFill(QColor &color) { } // 设置填充颜色
    //      功能描述；设置图形的描边颜色，对图像无效
    //      参数描述：描边的颜色color
    virtual void setStroke(QColor &color) { } // 设置描边颜色
    //      功能描述；设置图形描边的粗细，对图像无效
    //      参数描述：描边宽度width
    virtual void setStroke(int width) { } // 设置描边宽度
    //      功能描述；判断多边形是否闭合，对其他类无效
    //      返回值描述：多边形是否闭合
    virtual bool isClosed_poly() {return true;}// 多边形是否为闭合
    //      功能描述；获取图形的描边，对图像无效
    virtual QPen getStroke() {return QPen();} // 获取描边的画笔
    //      功能描述；获取图形的填充，对图像无效
    virtual QBrush getBrush() {return QBrush();} // 获取填充的笔刷
public: // 所有以Graph为基类的图形/图像有相同实现方式的方法，直接在基类中实现

    //      功能描述；绘制图形/图像辅助边框
    //      参数描述：用于绘制的画笔painter
    inline void drawBorder(QPainter &painter); // 绘制辅助边框
    //      功能描述；移动图形/图像
    inline void move(); // 移动
    //      功能描述；旋转图形/图像
    inline void rotate(); // 旋转
    //      功能描述；判断鼠标是否点击到有效区域
    //      参数描述：鼠标点击位置pos
    //      返回值描述：鼠标是否点击到辅助边框内部
    inline bool contain(QPoint &pos); // 判断（鼠标点击位置）是否在矩形框内部
    //      功能描述；更改图形/图像的图层位置（即变换图层覆盖关系）
    //      参数描述：新的图层位置index
    inline void changeIndex(int index); // 更换图层
    //      功能描述；裁剪图形/图像，本质上是调整边框，绘制时把边框作为遮罩
    inline void crop(); // 裁剪
    //      功能描述；判断图形/图像在基类共有的内容是否相同
    //      参数描述：需要比较的图形/图像graph
    //      返回值描述：二者在基类共有的成员变量是否相同
    inline bool base_equal(const Graph& graph); // 判断基类包含属性是否相同，用于简化bool operator==

protected:
    //      功能描述；根据裁切比例确定边框
    inline void updateBorder(); // 根据裁切比例确定边框
    //      功能描述；根据当前边框修正裁切比例
    inline void updateCropRatios(); // 根据边框确定裁切比例
};


inline void Graph::move()
{
    static bool lock_x = false; // 限定x方向移动
    static bool lock_y = false; // 限定y方向移动
    if (onShift)
    {
        if (!lock_x && !lock_y)
        { // 还没限定移动方向
            if (qAbs(current_mouse.x() - last_mouse.x()) >= qAbs(current_mouse.y() - last_mouse.y()))
            {
                lock_x = true;
            }
            else
            {
                lock_y = true;
            }
        }
    }
    else
    {
        lock_x = lock_y = false;
    }
    if (!lock_y)
    { // 没有限定在y方向，则x方向移动
        Center += QPoint(current_mouse.x() - last_mouse.x(), 0);
    }
    if (!lock_x)
    { // 没有限定在x方向，则y方向移动
        Center += QPoint(0, current_mouse.y() - last_mouse.y());
    }
}

inline bool Graph::contain(QPoint &pos)
{ // 判断（鼠标点击时）是否在边框内
    QLineF temp = QLineF(Center, pos); // 构造中心到鼠标的向量
    qreal current_angle = temp.angle(); // 获取temp和x轴的夹角，角度制
    qreal length = temp.length(); // 获取temp的长度

    // 将位置向量temp反向旋转角度angle，
    // 相当于将图形转正，
    // 再利用正的边框矩形判断这个向量temp是否落在边框内

    length *= 0.92; // 缩小被旋转向量的长度，相当于允许稍微超出边框
    // 构造旋转后的向量，并按照图形的缩放程度反向拉伸

    qreal delta_angle = qDegreesToRadians(current_angle - angle);
    // qt计算三角函数需要输入弧度制
    QPoint Vec = QPoint(length * qCos(delta_angle), -length * qSin(delta_angle));

    // 构造辅助边框矩形
    QRect border = QRect(border_tl, border_br);

    // 调用QRect的函数判断旋转向量是否落在边框内
    return border.contains(Vec); // 可以直接通过计算分量长度，用if语句判断，但这样比较酷
}

void Graph::changeIndex(int index)
{ // 更换图层即可
    this->Index = index;
}

inline void Graph::rotate()
{
    // 利用QlineF计算前后时刻鼠标和中心的夹角
    // 以此夹角之差作为旋转角度
    qreal angle1 = QLineF(last_mouse, Center).angle();
    qreal angle2 = QLineF(current_mouse, Center).angle();

    const int unit = 15;
    stored_angle += angle2 - angle1; // 实际旋转的角度一定改变
    // 按住shift时，以15度为单位旋转
    if (onShift)
    { // 此时展现出的旋转角度一定以15为单位
        angle = unit * qFloor(stored_angle / unit);
    }
    else
    { // 没有shift约束，展现的角度即为实际的角度
        angle = stored_angle;
    }
}


inline void Graph::drawBorder(QPainter &painter)
{ // 绘制的方法：并不是旋转边框的矩形，
  //           而是反方向旋转画笔，
  //           直接按照矩形为正的情形绘制

    QPen original_pen = painter.pen(); // 储存原来的画笔

    // 设置绘制边框的画笔
    QPen assist_pen = QPen();
    assist_pen.setColor(Qt::cyan);
    assist_pen.setWidth(2);
    assist_pen.setStyle(Qt::DashLine);
    painter.setPen(assist_pen);


    painter.save(); // 储存原来的画布

    painter.translate(Center.x(), Center.y()); // 将画笔移至当前图形中心
    painter.rotate(-angle); // 反方向旋转画笔，实现图形的"伪"旋转

    updateBorder();
    // 按辅助边框的宽和高绘制辅助矩形边框
    painter.drawRect(QRect(border_tl, border_br));

    // 恢复画布
    painter.restore();
    // 恢复画笔
    painter.setPen(original_pen);
}


inline void Graph::crop()
{
    int min_index = 0;
    const int threshold = 100;
    // 首先将鼠标相对位置的向量旋转到平的（抵消图形本身的旋转）
    QLineF temp = QLineF(Center, current_mouse);
    qreal length = temp.length(); // 角度值
    qreal delta_angle = qDegreesToRadians(temp.angle() - angle);
    // qt计算三角函数时需要输入弧度制
    QPoint vec = QPoint(length * qCos(delta_angle), -length * qSin(delta_angle));
    updateBorder();
    // 判断鼠标和边框四个顶点哪个最接近
    int *dist = new int[4]();
    dist[0] = QLineF(vec, border_tl).length();
    dist[1] = QLineF(vec, QPoint(border_br.x(), border_tl.y())).length();
    dist[2] = QLineF(vec, border_br).length();
    dist[3] = QLineF(vec, QPoint(border_tl.x(), border_br.y())).length();

    for (int i = 1; i <= 3; ++i)
    {
        if (dist[i] < dist[min_index]) min_index = i;
    }

    if (dist[min_index] >= threshold)
    { // 离得太远不能裁剪, 这次点击无效
        qDebug() << dist[min_index];
        min_index = 0;
        return ;
    }

    if (min_index == 0 || min_index == 3)
    {
        border_tl.setX(vec.x());
    }
    else
    {
        border_br.setX(vec.x());
    }

    if (min_index == 0 || min_index == 1)
    {
        border_tl.setY(vec.y());
    }
    else
    {
        border_br.setY(vec.y());
    }

    updateCropRatios();
}

inline void Graph::updateBorder()
{
    border_tl.setY(-graph_height * scale_y * crop_ratios[0] / 2.0);
    border_br.setX(graph_width * scale_x * crop_ratios[1] / 2.0);
    border_br.setY(graph_height * scale_y * crop_ratios[2] / 2.0);
    border_tl.setX(-graph_width * scale_x * crop_ratios[3] / 2.0);

    // 保证左上角和右上角的位置关系
    if (border_br.x() < border_tl.x())
    {
        int temp = border_tl.x();
        border_tl.setX(border_br.x());
        border_br.setX(temp);
    }
    if (border_br.y() < border_tl.y())
    {
        int temp = border_br.y();
        border_br.setY(border_tl.y());
        border_tl.setY(temp);
    }
}

inline void Graph::updateCropRatios()
{
    crop_ratios[0] = -(border_tl.y() * 2.0 / (graph_height * scale_y));
    crop_ratios[1] = (border_br.x() * 2.0 / (graph_width * scale_x));
    crop_ratios[2] = (border_br.y() * 2.0 / (graph_height * scale_y));
    crop_ratios[3] = -(border_tl.x() * 2.0 / (graph_width * scale_x));
    for (int i = 0;i <= 3; ++i)
    {
        if (crop_ratios[i] >= 1.0) crop_ratios[i] = 1.0;
        if (crop_ratios[i] <= -1.0) crop_ratios[i] = -1.0;
    }
}

inline bool Graph::base_equal(const Graph &graph)
{
    return (last_mouse == graph.last_mouse) &&
           (current_mouse == graph.current_mouse) &&
           (angle == graph.angle) &&
           (Index == graph.Index) &&
//           (editType == graph.editType) &&
           (Opacity == graph.Opacity) &&
//           (isBorderVisible == graph.isBorderVisible) &&
//           (onShift == graph.onShift) &&
           (shape == graph.shape) &&
           qFuzzyCompare(scale_x, graph.scale_x) && // 等价于(scale_x == graph.scale_x)的功能 ，用于浮点数判断相等
           qFuzzyCompare(scale_y, graph.scale_y) &&
           qFuzzyCompare(stored_angle, graph.stored_angle) &&
           (Center == graph.Center) &&
           (graph_width == graph.graph_width) &&
           (graph_height == graph.graph_height) &&
           (border_tl == graph.border_tl) &&
           (border_br == graph.border_br) &&
           (crop_ratios == nullptr) ? (graph.crop_ratios == nullptr) : (graph.crop_ratios != nullptr
                                        && qFuzzyCompare(crop_ratios[0], graph.crop_ratios[0])
                                        && qFuzzyCompare(crop_ratios[1], graph.crop_ratios[1])
                                        && qFuzzyCompare(crop_ratios[2], graph.crop_ratios[2])
                                        && qFuzzyCompare(crop_ratios[3], graph.crop_ratios[13]));
}

//inline bool Graph::operator == (const Graph & graph)
//{
//    if(base_equal(graph))
//    {
//        if(shape == Shape::SHAPE_ELLIPSE)
//        {
//            return dynamic_cast<myEllipse*>()
//        }
//    }
//}
#endif // GRAPH_H
