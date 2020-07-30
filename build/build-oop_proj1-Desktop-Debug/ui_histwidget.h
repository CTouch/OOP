/********************************************************************************
** Form generated from reading UI file 'histwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.14.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_HISTWIDGET_H
#define UI_HISTWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_HistWidget
{
public:
    QGridLayout *gridLayout;
    QVBoxLayout *layoutHists;
    QLabel *R_hist;
    QLabel *G_hist;
    QLabel *B_hist;

    void setupUi(QWidget *HistWidget)
    {
        if (HistWidget->objectName().isEmpty())
            HistWidget->setObjectName(QString::fromUtf8("HistWidget"));
        HistWidget->resize(534, 693);
        gridLayout = new QGridLayout(HistWidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        layoutHists = new QVBoxLayout();
        layoutHists->setObjectName(QString::fromUtf8("layoutHists"));
        R_hist = new QLabel(HistWidget);
        R_hist->setObjectName(QString::fromUtf8("R_hist"));

        layoutHists->addWidget(R_hist);

        G_hist = new QLabel(HistWidget);
        G_hist->setObjectName(QString::fromUtf8("G_hist"));

        layoutHists->addWidget(G_hist);

        B_hist = new QLabel(HistWidget);
        B_hist->setObjectName(QString::fromUtf8("B_hist"));

        layoutHists->addWidget(B_hist);


        gridLayout->addLayout(layoutHists, 0, 0, 1, 1);


        retranslateUi(HistWidget);

        QMetaObject::connectSlotsByName(HistWidget);
    } // setupUi

    void retranslateUi(QWidget *HistWidget)
    {
        HistWidget->setWindowTitle(QCoreApplication::translate("HistWidget", "Form", nullptr));
        R_hist->setText(QString());
        G_hist->setText(QString());
        B_hist->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class HistWidget: public Ui_HistWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HISTWIDGET_H
