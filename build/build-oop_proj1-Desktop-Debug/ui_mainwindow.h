/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.14.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <drawingboard.h>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionEllipse;
    QAction *actionCursor;
    QAction *actionMove;
    QWidget *centralwidget;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label_6;
    QSlider *opacity_slider;
    QLabel *value_opacity;
    QPushButton *button_fill_color;
    QPushButton *button_stroke_color;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QSlider *stroke_width_slider;
    QLabel *value_stroke_width;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_2;
    QComboBox *index_list;
    QHBoxLayout *horizontalLayout_6;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_3;
    QSlider *scale_x;
    QLabel *value_scale_x;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_4;
    QSlider *scale_y;
    QLabel *value_scale_y;
    QRadioButton *scale_lock;
    DrawingBoard *drawingboard;
    QMenuBar *menubar;
    QMenu *edit;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1032, 678);
        actionEllipse = new QAction(MainWindow);
        actionEllipse->setObjectName(QString::fromUtf8("actionEllipse"));
        actionCursor = new QAction(MainWindow);
        actionCursor->setObjectName(QString::fromUtf8("actionCursor"));
        actionMove = new QAction(MainWindow);
        actionMove->setObjectName(QString::fromUtf8("actionMove"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        layoutWidget = new QWidget(centralwidget);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(0, 0, 431, 261));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label_6 = new QLabel(layoutWidget);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        horizontalLayout->addWidget(label_6);

        opacity_slider = new QSlider(layoutWidget);
        opacity_slider->setObjectName(QString::fromUtf8("opacity_slider"));
        opacity_slider->setOrientation(Qt::Horizontal);

        horizontalLayout->addWidget(opacity_slider);

        value_opacity = new QLabel(layoutWidget);
        value_opacity->setObjectName(QString::fromUtf8("value_opacity"));

        horizontalLayout->addWidget(value_opacity);


        verticalLayout->addLayout(horizontalLayout);

        button_fill_color = new QPushButton(layoutWidget);
        button_fill_color->setObjectName(QString::fromUtf8("button_fill_color"));

        verticalLayout->addWidget(button_fill_color);

        button_stroke_color = new QPushButton(layoutWidget);
        button_stroke_color->setObjectName(QString::fromUtf8("button_stroke_color"));

        verticalLayout->addWidget(button_stroke_color);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label = new QLabel(layoutWidget);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout_2->addWidget(label);

        stroke_width_slider = new QSlider(layoutWidget);
        stroke_width_slider->setObjectName(QString::fromUtf8("stroke_width_slider"));
        stroke_width_slider->setOrientation(Qt::Horizontal);

        horizontalLayout_2->addWidget(stroke_width_slider);

        value_stroke_width = new QLabel(layoutWidget);
        value_stroke_width->setObjectName(QString::fromUtf8("value_stroke_width"));

        horizontalLayout_2->addWidget(value_stroke_width);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_2 = new QLabel(layoutWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_3->addWidget(label_2);

        index_list = new QComboBox(layoutWidget);
        index_list->setObjectName(QString::fromUtf8("index_list"));

        horizontalLayout_3->addWidget(index_list);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        label_3 = new QLabel(layoutWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout_4->addWidget(label_3);

        scale_x = new QSlider(layoutWidget);
        scale_x->setObjectName(QString::fromUtf8("scale_x"));
        scale_x->setOrientation(Qt::Horizontal);

        horizontalLayout_4->addWidget(scale_x);


        horizontalLayout_6->addLayout(horizontalLayout_4);

        value_scale_x = new QLabel(layoutWidget);
        value_scale_x->setObjectName(QString::fromUtf8("value_scale_x"));

        horizontalLayout_6->addWidget(value_scale_x);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        label_4 = new QLabel(layoutWidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        horizontalLayout_5->addWidget(label_4);

        scale_y = new QSlider(layoutWidget);
        scale_y->setObjectName(QString::fromUtf8("scale_y"));
        scale_y->setOrientation(Qt::Horizontal);

        horizontalLayout_5->addWidget(scale_y);

        value_scale_y = new QLabel(layoutWidget);
        value_scale_y->setObjectName(QString::fromUtf8("value_scale_y"));

        horizontalLayout_5->addWidget(value_scale_y);


        horizontalLayout_6->addLayout(horizontalLayout_5);

        scale_lock = new QRadioButton(layoutWidget);
        scale_lock->setObjectName(QString::fromUtf8("scale_lock"));

        horizontalLayout_6->addWidget(scale_lock);


        verticalLayout->addLayout(horizontalLayout_6);

        drawingboard = new DrawingBoard(centralwidget);
        drawingboard->setObjectName(QString::fromUtf8("drawingboard"));
        drawingboard->setGeometry(QRect(440, 0, 581, 631));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1032, 22));
        edit = new QMenu(menubar);
        edit->setObjectName(QString::fromUtf8("edit"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(edit->menuAction());
        edit->addAction(actionEllipse);
        edit->addAction(actionCursor);
        edit->addAction(actionMove);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        actionEllipse->setText(QCoreApplication::translate("MainWindow", "Ellipse", nullptr));
        actionCursor->setText(QCoreApplication::translate("MainWindow", "Cursor", nullptr));
        actionMove->setText(QCoreApplication::translate("MainWindow", "Move", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "Opacity", nullptr));
        value_opacity->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        button_fill_color->setText(QCoreApplication::translate("MainWindow", "Change Fill Color", nullptr));
        button_stroke_color->setText(QCoreApplication::translate("MainWindow", "Change Stroke Color", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Stroke Width", nullptr));
        value_stroke_width->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "index", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "scale_x", nullptr));
        value_scale_x->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "scale_y", nullptr));
        value_scale_y->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        scale_lock->setText(QCoreApplication::translate("MainWindow", "Lock", nullptr));
        edit->setTitle(QCoreApplication::translate("MainWindow", "edit", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
